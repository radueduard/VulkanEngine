#pragma once

#include "window/camera.hpp"
#include "device.hpp"
#include "gameObject.hpp"
#include "pipeline.hpp"
#include "frameInfo.hpp"

#include <memory>
#include <vector>

namespace ve {

    struct SimplePushConstantData {
        glm::mat4 model{1.0};
    };

    class RenderSystem {
    public:
        RenderSystem(Device &device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
        RenderSystem(const RenderSystem &) = delete;
        RenderSystem &operator=(const RenderSystem &) = delete;
        ~RenderSystem();

        void renderGameObjects(const FrameInfo&);

    private:
        void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
        void createPipeline(VkRenderPass renderPass);

        Device &device;
        std::unique_ptr<Pipeline> pipeline;
        VkPipelineLayout pipelineLayout;
    };
}
