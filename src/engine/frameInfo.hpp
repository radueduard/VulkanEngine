#pragma once

#include <vulkan/vulkan.h>
#include <unordered_map>

#include "window/camera.hpp"
#include "engine/gameObject.hpp"
#include "engine/descriptors.hpp"

namespace ve {
    struct FrameInfo {
        int frameIndex;
        float deltaTime;
        VkCommandBuffer commandBuffer;
        Camera& camera;
        VkDescriptorSet globalDescriptorSet;
        DescriptorPool &frameDescriptorPool;
        std::unordered_map<size_t, GameObject>& gameObjects;
    };
}
