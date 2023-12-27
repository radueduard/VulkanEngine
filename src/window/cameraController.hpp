#pragma once

#include "window/inputController.hpp"
#include "window/window.hpp"
#include "camera.hpp"

namespace ve {
    class CameraController : public InputController {
    public:
        explicit CameraController(Camera &camera, Window &window);
        void onInputUpdate(float deltaTime, int mods) override;
        void onMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void onMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void onMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;

    private:
        Camera& camera;
        Window& window;
    };
}
