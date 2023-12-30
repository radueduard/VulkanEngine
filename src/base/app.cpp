#include "app.hpp"

#include "engine/renderSystem.hpp"
#include "window/cameraController.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <stdexcept>
#include <numeric>

namespace ve {

    struct CameraTransformations {
        glm::mat4 view{};
        glm::mat4 proj{};
    };

    struct MaterialProperties {
        float ambient{};
        float diffuse{};
        float specular{};
        int shininess{};
    };

    struct LightProperties {
        alignas(16) glm::vec3 position{};
        alignas(16) glm::vec3 eyePosition{};
        alignas(16) glm::vec3 color{};
    };

    App::App(Window &window) : window(window), device(window), renderer(window,device)
    {
        camera.setPerspectiveProjection(glm::radians(60.f), renderer.getAspectRatio(), .01f, 1000);

        window.setDefaultInputController(this);
        window.setCameraInputController(new CameraController(camera, window));

        globalPool = DescriptorPool::Builder(device)
                .setMaxSets(SwapChain::MAX_FRAMES_IN_FLIGHT)
                .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, SwapChain::MAX_FRAMES_IN_FLIGHT)
                .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, SwapChain::MAX_FRAMES_IN_FLIGHT)
                .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, SwapChain::MAX_FRAMES_IN_FLIGHT)
                .addPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, SwapChain::MAX_FRAMES_IN_FLIGHT)
                .build();

        framePools.resize(SwapChain::MAX_FRAMES_IN_FLIGHT);
        auto framePoolBuilder = DescriptorPool::Builder(device)
                .setMaxSets(1000)
                .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000)
                .addPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000);

        for (auto& framePool : framePools) {
            framePool = framePoolBuilder.build();
        }
    }

    App::~App() {}

    void App::run() {
        std::vector<std::unique_ptr<Buffer>> uniformBuffers(SwapChain::MAX_FRAMES_IN_FLIGHT);
        const auto minOffsetAlignment = std::lcm(
                device.properties.limits.minUniformBufferOffsetAlignment,
                device.properties.limits.nonCoherentAtomSize);
        for (auto& buffer : uniformBuffers) {
            buffer = std::make_unique<Buffer>(
                    device,
                    sizeof(CameraTransformations),
                    3,
                    VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
                    minOffsetAlignment);
            buffer->map();
        }

        auto globalSetLayout = DescriptorSetLayout::Builder(device)
                .addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT)
                .addBinding(1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT)
                .addBinding(2, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT)
                .build();

        std::vector<VkDescriptorSet> globalDescriptorSets(SwapChain::MAX_FRAMES_IN_FLIGHT);
        for (size_t i = 0; i < globalDescriptorSets.size(); i++) {
            auto cameraTransformationsInfo = uniformBuffers[i]->descriptorInfoForIndex(0);
            auto materialPropertiesInfo = uniformBuffers[i]->descriptorInfoForIndex(1);
            auto lightPropertiesInfo = uniformBuffers[i]->descriptorInfoForIndex(2);

            DescriptorWriter(*globalSetLayout, *globalPool)
                    .writeBuffer(0, &cameraTransformationsInfo)
                    .writeBuffer(1, &materialPropertiesInfo)
                    .writeBuffer(2, &lightPropertiesInfo)
                    .build(globalDescriptorSets[i]);
        }

        init();

        RenderSystem renderSystem(device, renderer.getSwapChainRenderPass(), globalSetLayout->getDescriptorSetLayout());

        while (!window.shouldClose()) {
            window.pollEvents();
            window.computeDeltaTime();
            window.updateInputs();

            float aspect = renderer.getAspectRatio();
            camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 1000.0f);

            if (auto commandBuffer = renderer.beginFrame()) {
                int frameIndex = renderer.getFrameIndex();
                framePools[frameIndex]->resetPool();
                update(window.getDeltaTime());

                FrameInfo frameInfo{
                        frameIndex,
                        window.getDeltaTime(),
                        commandBuffer,
                        camera,
                        globalDescriptorSets[frameIndex],
                        *framePools[frameIndex],
                        gameObjects};

                CameraTransformations cameraTransformations {
                    camera.view(),
                    camera.projection(),
                };

                MaterialProperties materialProperties {
                    0.1f,
                    0.5f,
                    0.5f,
                    30,
                };

                LightProperties lightProperties {
                    glm::vec3(1, -5, 3),
                    camera.getPosition(),
                    glm::vec3(1),
                };

                uniformBuffers[frameIndex]->writeToIndex(&cameraTransformations, 0);
                uniformBuffers[frameIndex]->writeToIndex(&materialProperties, 1);
                uniformBuffers[frameIndex]->writeToIndex(&lightProperties, 2);



                uniformBuffers[frameIndex]->flushIndex(0);
                uniformBuffers[frameIndex]->flushIndex(1);
                uniformBuffers[frameIndex]->flushIndex(2);

                renderer.beginSwapChainRenderPass(commandBuffer);
                renderSystem.renderGameObjects(frameInfo);
                renderer.endSwapChainRenderPass(commandBuffer);
                renderer.endFrame();
            }
        }
        vkDeviceWaitIdle(device.device());
    }
}