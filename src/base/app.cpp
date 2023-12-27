#include "app.hpp"

#include "engine/renderSystem.hpp"
#include "window/cameraController.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <stdexcept>
namespace ve {
    App::App(Window &window) : window(window), device(window), renderer(window,device)
    {
        camera.setPerspectiveProjection(glm::radians(60.f), renderer.getAspectRatio(), .01f, 200);
//        camera.setOrthographicProjection(-renderer.getAspectRatio(), renderer.getAspectRatio(), -1, 1, -1, 1);

        window.setDefaultInputController(this);
        window.setCameraInputController(new CameraController(camera, window));
    }

    App::~App() {}

    void App::run() {

        init();

        RenderSystem renderSystem(device, renderer.getSwapChainRenderPass());

        while (!window.shouldClose()) {
            window.pollEvents();
            window.computeDeltaTime();
            window.updateInputs();

            float aspect = renderer.getAspectRatio();
            camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 10.0f);

            update(window.getDeltaTime());

            if (auto commandBuffer = renderer.beginFrame()) {
                renderer.beginSwapChainRenderPass(commandBuffer);
                renderSystem.renderGameObjects(commandBuffer, gameObjects, camera);
                renderer.endSwapChainRenderPass(commandBuffer);
                renderer.endFrame();
            }
        }
        vkDeviceWaitIdle(device.device());
    }
}