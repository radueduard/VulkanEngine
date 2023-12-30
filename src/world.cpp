#include <stdexcept>
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

    World::World(Window& window) : App(window) {}

    void World::init() {
        auto apple = Model::loadModelsFromFile(device, "../models/apple.obj");
        auto sphere = Model::loadModelsFromFile(device, "../models/sphere.obj");


        for (auto& model : apple) {
            GameObject appleObject = GameObject::createGameObject();
            appleObject.model = model;
            appleObject.transform.translate = glm::vec3(0.0f, 0.0f, 2.5f);
            appleObject.transform.scale = glm::vec3(.01f);

            gameObjects.emplace(appleObject.getId(), std::move(appleObject));
        }

        for (auto& model : sphere) {
            GameObject sphereObject = GameObject::createGameObject();
            sphereObject.model = model;
            sphereObject.transform.translate = glm::vec3(1, -5, 3);

            gameObjects.emplace(sphereObject.getId(), std::move(sphereObject));
        }
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