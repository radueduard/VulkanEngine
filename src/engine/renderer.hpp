#pragma once

#include <memory>
#include <cassert>
#include <vector>

#include "window/window.hpp"
#include "device.hpp"
#include "swapChain.hpp"

namespace ve {
    class Renderer {
    public:
        Renderer(Window &window, Device &device);
        Renderer(const Renderer &) = delete;
        Renderer &operator=(const Renderer &) = delete;
        ~Renderer();

        VkRenderPass getSwapChainRenderPass() const { return swapChain->getRenderPass(); }
        bool isFrameInProgress() const { return isFrameStarted; }

        VkCommandBuffer getCurrentCommandBuffer() const {
            assert(isFrameStarted && "Cannot get command buffer when frame not in progress");
            return commandBuffers[currentFrameIndex];
        }

        int getFrameIndex() const {
            assert(isFrameStarted && "Cannot get frame index when frame not in progress");
            return currentFrameIndex;
        }

        VkCommandBuffer beginFrame();
        void endFrame();

        void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
        void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

        float getAspectRatio() const { return swapChain->extentAspectRatio(); }

    private:
        void createCommandBuffers();
        void freeCommandBuffers();
        void recreateSwapChain();

        Window &window;
        Device &device;
        std::unique_ptr<SwapChain> swapChain;
        std::vector<VkCommandBuffer> commandBuffers{};

        int currentImageIndex = 0;
        int currentFrameIndex = 0;
        bool isFrameStarted = false;
    };
}
