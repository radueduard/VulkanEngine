#pragma once

#include "engine/device.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>

namespace ve {
    class Model {
    public:
        struct Vertex {
            glm::vec3 position;
            glm::vec3 color;

            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

            Vertex(glm::vec3 position, glm::vec3 color = glm::vec3(62.f, 114.f, 199.f) / 255.f);
        };

        Model(Device& device, const std::vector<Vertex>& vertices);
        Model(const Model&) = delete;
        Model& operator=(const Model&) = delete;
        ~Model();

        void bind(VkCommandBuffer commandBuffer);
        void draw(VkCommandBuffer commandBuffer) const;

    private:
        void createVertexBuffers(const std::vector<Vertex>& vertices);

        Device& device;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        uint32_t vertexCount;
    };
}
