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
        std::vector<Model::Vertex> vertices{

                // left face (white)
                {{-.5f, -.5f, -.5f},  {.9f, .9f, .9f}},
                {{-.5f, .5f,  .5f},   {.9f, .9f, .9f}},
                {{-.5f, -.5f, .5f},   {.9f, .9f, .9f}},
                {{-.5f, -.5f, -.5f},  {.9f, .9f, .9f}},
                {{-.5f, .5f,  -.5f},  {.9f, .9f, .9f}},
                {{-.5f, .5f,  .5f},   {.9f, .9f, .9f}},

                // right face (yellow)
                {{.5f,  -.5f, -.5f},  {.8f, .8f, .1f}},
                {{.5f,  .5f,  .5f},   {.8f, .8f, .1f}},
                {{.5f,  -.5f, .5f},   {.8f, .8f, .1f}},
                {{.5f,  -.5f, -.5f},  {.8f, .8f, .1f}},
                {{.5f,  .5f,  -.5f},  {.8f, .8f, .1f}},
                {{.5f,  .5f,  .5f},   {.8f, .8f, .1f}},

                // top face (orange, remember y axis points down)
                {{-.5f, -.5f, -.5f},  {.9f, .6f, .1f}},
                {{.5f,  -.5f, .5f},   {.9f, .6f, .1f}},
                {{-.5f, -.5f, .5f},   {.9f, .6f, .1f}},
                {{-.5f, -.5f, -.5f},  {.9f, .6f, .1f}},
                {{.5f,  -.5f, -.5f},  {.9f, .6f, .1f}},
                {{.5f,  -.5f, .5f},   {.9f, .6f, .1f}},

                // bottom face (red)
                {{-.5f, .5f,  -.5f},  {.8f, .1f, .1f}},
                {{.5f,  .5f,  .5f},   {.8f, .1f, .1f}},
                {{-.5f, .5f,  .5f},   {.8f, .1f, .1f}},
                {{-.5f, .5f,  -.5f},  {.8f, .1f, .1f}},
                {{.5f,  .5f,  -.5f},  {.8f, .1f, .1f}},
                {{.5f,  .5f,  .5f},   {.8f, .1f, .1f}},

                // nose face (blue)
                {{-.5f, -.5f, 0.5f},  {.1f, .1f, .8f}},
                {{.5f,  .5f,  0.5f},  {.1f, .1f, .8f}},
                {{-.5f, .5f,  0.5f},  {.1f, .1f, .8f}},
                {{-.5f, -.5f, 0.5f},  {.1f, .1f, .8f}},
                {{.5f,  -.5f, 0.5f},  {.1f, .1f, .8f}},
                {{.5f,  .5f,  0.5f},  {.1f, .1f, .8f}},

                // tail face (green)
                {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
                {{.5f,  .5f,  -0.5f}, {.1f, .8f, .1f}},
                {{-.5f, .5f,  -0.5f}, {.1f, .8f, .1f}},
                {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
                {{.5f,  -.5f, -0.5f}, {.1f, .8f, .1f}},
                {{.5f,  .5f,  -0.5f}, {.1f, .8f, .1f}},

        };
        for (auto &v: vertices) {
            v.position += offset;
        }
        return std::make_unique<Model>(device, vertices);
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