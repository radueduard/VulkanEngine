#pragma once

#include "base/app.hpp"

#include <memory>

namespace ve {

    class World : public App {
    public:
        static World* getInstance();
        static void instantiate(Window &window);

    private:
        static World* instance;

        explicit World(Window& window);
        ~World() override = default;

        void init() override;
        void update(float deltaTime) override;

        void onInputUpdate(float deltaTime, int mods) override;
        void onKeyPress(int key, int mods) override;
        void onKeyRelease(int key, int mods) override;
        void onMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void onMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void onMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void onScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

        GameObjectManager gameObjectManager;
    };

}
