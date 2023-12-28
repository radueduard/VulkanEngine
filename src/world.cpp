//
// Created by radue on 12/27/2023.
//

#include <iostream>
#include "world.hpp"

namespace ve {

    World* World::instance = nullptr;

    void World::instantiate(Window &window) {
        if (instance != nullptr) {
            throw std::runtime_error("World instance already exists");
        }
        instance = new World(window);
    }

    World* World::getInstance() {
        if (instance == nullptr) {
            throw std::runtime_error("World instance is null");
        }
        return instance;
    }

    // World

    World::World(Window& window) : App(window) {
        std::cout << "World created" << std::endl;
    }

    std::unique_ptr<Model> createCubeModel(Device &device, glm::vec3 offset) {
        Model::Builder builder{};

        builder.vertices = {
                {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}, {}, {0.0f, 0.0f}},
                {{1.0f, -1.0f, -1.0f},  {1.0f, 0.0f, 0.0f}, {}, {1.0f, 0.0f}},
                {{1.0f, 1.0f, -1.0f},   {1.0f, 1.0f, 0.0f}, {}, {1.0f, 1.0f}},
                {{-1.0f, 1.0f, -1.0f},  {0.0f, 1.0f, 0.0f}, {}, {0.0f, 1.0f}},
                {{-1.0f, -1.0f, 1.0f},  {0.0f, 0.0f, 1.0f}, {}, {0.0f, 0.0f}},
                {{1.0f, -1.0f, 1.0f},   {1.0f, 0.0f, 1.0f}, {}, {1.0f, 0.0f}},
                {{1.0f, 1.0f, 1.0f},    {1.0f, 1.0f, 1.0f}, {}, {1.0f, 1.0f}},
                {{-1.0f, 1.0f, 1.0f},   {0.0f, 1.0f, 1.0f}, {}, {0.0f, 1.0f}},
        };

        builder.indices = {
                0, 1, 2, 2, 3, 0, // front
                4, 5, 6, 6, 7, 4, // back
                4, 5, 1, 1, 0, 4, // bottom
                3, 2, 6, 6, 7, 3, // top
                1, 2, 6, 6, 5, 1, // right
                0, 3, 7, 7, 4, 0, // left
        };

        return std::make_unique<Model>(device, builder);
    }

    void World::init() {
        std::shared_ptr<Model> cubeModel = createCubeModel(device, glm::vec3(0.0f));

        GameObject cubeObject = GameObject::createGameObject();
        cubeObject.model = cubeModel;
        cubeObject.transform.translate = glm::vec3(0.0f, 0.0f, 2.5f);
        cubeObject.transform.scale = glm::vec3(.5f);

        gameObjects.push_back(std::move(cubeObject));
    }

    void World::update(float deltaTime) {

    }

    // InputController

    void World::onInputUpdate(float deltaTime, int mods) {

    }

    void World::onKeyPress(int key, int mods) {

    }

    void World::onKeyRelease(int key, int mods) {

    }

    void World::onMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {

    }

    void World::onMouseBtnPress(int mouseX, int mouseY, int button, int mods) {

    }

    void World::onMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {

    }

    void World::onScroll(int mouseX, int mouseY, int offsetX, int offsetY) {

    }
}