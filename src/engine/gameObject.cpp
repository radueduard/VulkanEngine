#include <numeric>
#include "gameObject.hpp"

namespace ve {

    GameObjectManager::GameObjectManager(Device& device) {
        // including nonCoherentAtomSize allows us to flush a specific index at once
        int alignment = std::lcm(
                device.properties.limits.nonCoherentAtomSize,
                device.properties.limits.minUniformBufferOffsetAlignment);
        for (auto & uboBuffer : uboBuffers) {
            uboBuffer = std::make_unique<Buffer>(
                    device,
                    sizeof(GameObjectBufferData),
                    GameObjectManager::MAX_GAME_OBJECTS,
                    VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
                    alignment);
            uboBuffer->map();
        }

        textureDefault = Texture::createTextureFromFile(device, "../textures/missing.png");
    }

    void GameObjectManager::updateBuffer(int frameIndex) {
        // copy model matrix and normal matrix for each gameObj into
        // buffer for this frame
        for (auto &[index, obj]: gameObjects) {
            GameObjectBufferData data{};
            data.model = obj.transform.model();
            uboBuffers[frameIndex]->writeToIndex(&data, index);
        }
        uboBuffers[frameIndex]->flush();
    }

    VkDescriptorBufferInfo GameObject::getBufferInfo(int frameIndex) {
        return gameObjectManger.getBufferInfoForGameObject(frameIndex, id);
    }

    GameObject::GameObject(size_t objId, const GameObjectManager &manager)
            : id(objId), gameObjectManger(manager) {}
}