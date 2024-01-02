#include "cameraController.hpp"

namespace ve {
    CameraController::CameraController(Camera &camera, Window &window) : camera(camera), window(window) {}

    void CameraController::onInputUpdate(float deltaTime, int mods) {
        if (!window.mouseHold(GLFW_MOUSE_BUTTON_RIGHT)) return;

        if (window.getSpecialKeyState() & GLFW_MOD_SHIFT) deltaTime *= 2;

        if (window.keyHold(GLFW_KEY_W)) camera.moveForward(-deltaTime);
        if (window.keyHold(GLFW_KEY_S)) camera.moveForward(deltaTime);
        if (window.keyHold(GLFW_KEY_A)) camera.moveRight(deltaTime);
        if (window.keyHold(GLFW_KEY_D)) camera.moveRight(-deltaTime);
        if (window.keyHold(GLFW_KEY_Q)) camera.moveUp(deltaTime);
        if (window.keyHold(GLFW_KEY_E)) camera.moveUp(-deltaTime);

        if (window.keyHold(GLFW_KEY_KP_MULTIPLY)) camera.updateSpeed(.2f);
        if (window.keyHold(GLFW_KEY_KP_DIVIDE)) camera.updateSpeed(-.2f);

        if (window.keyHold(GLFW_KEY_KP_2)) camera.rotateOX(-deltaTime);
        if (window.keyHold(GLFW_KEY_KP_4)) camera.rotateOY(-deltaTime);
        if (window.keyHold(GLFW_KEY_KP_6)) camera.rotateOY(deltaTime);
        if (window.keyHold(GLFW_KEY_KP_8)) camera.rotateOX(deltaTime);

        camera.update();
    }

    void CameraController::onMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {

        static constexpr float sensitivity = 0.002f;

        if (window.mouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
            camera.rotateOY(static_cast<float>(deltaX * sensitivity));
            camera.rotateOX(-static_cast<float>(deltaY * sensitivity));
            camera.update();
        }
    }

    void CameraController::onMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
        if ((button | 1 << GLFW_MOUSE_BUTTON_RIGHT) == button) {
            window.disablePointer();
        }
    }

    void CameraController::onMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
        if ((button | 1 << GLFW_MOUSE_BUTTON_RIGHT) == button) {
            window.enablePointer();
        }
    }


}