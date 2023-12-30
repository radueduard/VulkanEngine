#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/gtc/matrix_transform.hpp>

#include <cstdlib>
#include <memory>
#include <unordered_map>

#include "model.hpp"
#include "texture.hpp"
#include "swapChain.hpp"

namespace ve {

    struct Transform {
        glm::vec3 translate{0.0f};
        glm::vec3 scale{1.0f};
        glm::vec3 rotate{0.0f};

        glm::mat4 model() const {
            const float c3 = glm::cos(rotate.z);
            const float s3 = glm::sin(rotate.z);
            const float c2 = glm::cos(rotate.x);
            const float s2 = glm::sin(rotate.x);
            const float c1 = glm::cos(rotate.y);
            const float s1 = glm::sin(rotate.y);
            return glm::mat4{
                    {
                            scale.x * (c1 * c3 + s1 * s2 * s3),
                            scale.x * (c2 * s3),
                            scale.x * (c1 * s2 * s3 - c3 * s1),
                            0.0f,
                    },
                    {
                            scale.y * (c3 * s1 * s2 - c1 * s3),
                            scale.y * (c2 * c3),
                            scale.y * (c1 * c3 * s2 + s1 * s3),
                            0.0f,
                    },
                    {
                            scale.z * (c2 * s1),
                            scale.z * (-s2),
                            scale.z * (c1 * c2),
                            0.0f,
                    },
                    {
                            translate.x,
                            translate.y,
                            translate.z,
                            1.0f
                    }
            };
        }
    };

    struct GameObjectBufferData {
        glm::mat4 model;
    };

    class GameObjectManager;

    class GameObject {
    public:
        size_t getId() const { return id; }

        VkDescriptorBufferInfo getBufferInfo(int frameIndex);

        std::shared_ptr<Model> model = nullptr;
        std::shared_ptr<Texture> texture = nullptr;
        Transform transform{};
        glm::vec3 color{};

        GameObject(const GameObject&) = delete;

        GameObject &operator=(const GameObject &) = delete;

        GameObject(GameObject &&) = default;

        GameObject &operator=(GameObject &&) = default;

    private:
        size_t id;
        GameObject(size_t objId, const GameObjectManager &manager);
        const GameObjectManager &gameObjectManger;

        friend class GameObjectManager;
    };


    class GameObjectManager {
    public:
        static constexpr int MAX_GAME_OBJECTS = 1000;

        GameObjectManager(Device &device);
        GameObjectManager(const GameObjectManager &) = delete;
        GameObjectManager &operator=(const GameObjectManager &) = delete;
        GameObjectManager(GameObjectManager &&) = delete;
        GameObjectManager &operator=(GameObjectManager &&) = delete;

        GameObject &createGameObject() {
            assert(currentId < MAX_GAME_OBJECTS && "Max game object count exceeded!");
            auto gameObject = GameObject{currentId++, *this};
            auto gameObjectId = gameObject.getId();
            gameObject.texture = textureDefault;
            gameObjects.emplace(gameObjectId, std::move(gameObject));
            return gameObjects.at(gameObjectId);
        }

        VkDescriptorBufferInfo getBufferInfoForGameObject(
                int frameIndex, size_t gameObjectId) const {
            return uboBuffers[frameIndex]->descriptorInfoForIndex(gameObjectId);
        }

        void updateBuffer(int frameIndex);

        std::unordered_map<size_t, GameObject> gameObjects{};
        std::vector<std::unique_ptr<Buffer>> uboBuffers{SwapChain::MAX_FRAMES_IN_FLIGHT};

    private:
        size_t currentId = 0;
        std::shared_ptr<Texture> textureDefault;
    };
}
