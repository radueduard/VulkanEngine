#include <stdexcept>

#include "window.hpp"
#include "windowCallbacks.hpp"

namespace ve {
    Window::Window(const int width, const int height, const std::string &&name)
            : width(width), height(height), name(name), window(nullptr),
            customInputController(nullptr), cameraInputController(nullptr) {
        initWindow();
    }

    Window::~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        setWindowCallbacks();
    }

    bool Window::shouldClose() {
        return glfwWindowShouldClose(window);
    }

    void Window::pollEvents() {
        glfwPollEvents();
    }

    float Window::computeDeltaTime() {
        time newTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
        currentTime = newTime;
        return deltaTime;
    }

    void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
        if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    void Window::updateInputs() {
        if (customInputController == nullptr) {
            throw std::runtime_error("Cannot update inputs: no customInputController provided!");
        }

        if (inputStates.mouseMove != std::nullopt) {
            auto [x, y] = inputStates.mousePosition;
            auto [dx, dy] = inputStates.mouseMove.value();

            customInputController->onMouseMove(x, y, dx, dy);
            cameraInputController->onMouseMove(x, y, dx, dy);

            inputStates.mouseMove = std::nullopt;
        }

        auto pressEvent = inputStates.mouseButtons.mouseButtonAction &
                          inputStates.mouseButtons.mouseButtonStates;

        if (pressEvent != 0) {
            auto [x, y] = inputStates.mousePosition;
            auto keyMods = inputStates.keyMods;

            customInputController->onMouseBtnPress(x, y, pressEvent, keyMods);
            cameraInputController->onMouseBtnPress(x, y, pressEvent, keyMods);
        }

        auto releaseEvent = inputStates.mouseButtons.mouseButtonAction &
                            ~inputStates.mouseButtons.mouseButtonStates;

        if (releaseEvent != 0) {
            auto [x, y] = inputStates.mousePosition;
            auto keyMods = inputStates.keyMods;

            customInputController->onMouseBtnRelease(x, y, releaseEvent, keyMods);
            cameraInputController->onMouseBtnRelease(x, y, releaseEvent, keyMods);
        }

        inputStates.mouseButtons.mouseButtonAction = 0;

        if (inputStates.mouseScroll != std::nullopt) {
            auto [x, y] = inputStates.mousePosition;
            auto [dx, dy] = inputStates.mouseScroll.value();

            customInputController->onScroll(x, y, dx, dy);
            cameraInputController->onScroll(x, y, dx, dy);

            inputStates.mouseScroll = std::nullopt;
        }

        while (!inputStates.keyEvents.empty()) {
            int key = inputStates.keyEvents.front();
            inputStates.keyEvents.pop();

            if (inputStates.keyStates[key]) {
                customInputController->onKeyPress(key, inputStates.keyMods);
                cameraInputController->onKeyPress(key, inputStates.keyMods);
            } else {
                customInputController->onKeyRelease(key, inputStates.keyMods);
                cameraInputController->onKeyRelease(key, inputStates.keyMods);
            }
        }
        customInputController->onInputUpdate(deltaTime, inputStates.keyMods);
        cameraInputController->onInputUpdate(deltaTime, inputStates.keyMods);
    }

    void Window::setDefaultInputController(InputController *inputController) {
        this->customInputController = inputController;
    }

    void Window::setCameraInputController(InputController *inputController) {
        this->cameraInputController = inputController;
    }

    void Window::enablePointer() {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void Window::disablePointer() {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    bool Window::mouseHold(int button) {
        return inputStates.mouseButtons.mouseButtonStates & (1 << button) != 0;
    }

    bool Window::keyHold(int key) {
        return inputStates.keyStates[key];
    }

    int Window::getSpecialKeyState() {
        return inputStates.keyMods;
    }

    void Window::resizeCallback(int width, int height) {
        framebufferResized = true;
        width = width;
        height = height;
    }

    void Window::keyCallback(int key, int scancode, int action, int mods) {
        inputStates.keyMods = mods;
        if (inputStates.keyStates[key] == (action != GLFW_RELEASE)) return;
        inputStates.keyStates[key] = action != GLFW_RELEASE;
        inputStates.keyEvents.push(key);
    }

    void Window::mouseMoveCallback(double mouseX, double mouseY) {
        if (inputStates.mouseMove == std::nullopt)
            inputStates.mouseMove = MouseMove{0, 0};
        auto& [x, y] = inputStates.mousePosition;
        auto& [dx, dy] = inputStates.mouseMove.value();
        dx = static_cast<int>(mouseX) - x;
        dy = static_cast<int>(mouseY) - y;
        x = static_cast<int>(mouseX);
        y = static_cast<int>(mouseY);
    }

    void Window::mouseButtonCallback(int button, int action, int mods) {
        inputStates.keyMods = mods;
        inputStates.mouseButtons.mouseButtonAction |= (1 << button);
        if (action == GLFW_PRESS) {
            inputStates.mouseButtons.mouseButtonStates |= (1 << button);
        } else {
            inputStates.mouseButtons.mouseButtonStates &= ~(1 << button);
        }
    }

    void Window::scrollCallback(double offsetX, double offsetY) {
        inputStates.mouseScroll = MouseScroll{static_cast<int>(offsetX), static_cast<int>(offsetY)};
    }

    void Window::setWindowCallbacks() const {
        glfwSetKeyCallback(window, WindowCallbacks::keyCallback);
        glfwSetCursorPosCallback(window, WindowCallbacks::mouseMoveCallback);
        glfwSetMouseButtonCallback(window, WindowCallbacks::mouseButtonCallback);
        glfwSetScrollCallback(window, WindowCallbacks::scrollCallback);
    }

    float Window::getDeltaTime() { return deltaTime; }
}