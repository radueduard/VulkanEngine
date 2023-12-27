#pragma once

#include "window/camera.hpp"
#include "device.hpp"
#include "gameObject.hpp"
#include "pipeline.hpp"

#include <memory>
#include <vector>

namespace ve {

    struct SimplePushConstantData {
        glm::mat4 model{1.0};
        glm::mat4 view{1.0};
        glm::mat4 proj{1.0};
    };

    class RenderSystem {
    public:
        RenderSystem(Device &device, VkRenderPass renderPass);
        RenderSystem(const RenderSystem &) = delete;
        RenderSystem &operator=(const RenderSystem &) = delete;
        ~RenderSystem();

        void renderGameObjects(VkCommandBuffer commandBuffer, std::vector<GameObject> &gameObjects, const Camera &camera);

    private:
        void createPipelineLayout();
        void createPipeline(VkRenderPass renderPass);

        Device &device;
        std::unique_ptr<Pipeline> pipeline;
        VkPipelineLayout pipelineLayout;
    };
}
