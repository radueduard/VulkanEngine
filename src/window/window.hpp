#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <string>
#include <optional>
#include <queue>
#include <chrono>

#include "inputController.hpp"
#include "camera.hpp"

namespace ve {

    using time = std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<long long, std::ratio<1, 1000000000>>>;

    class Window {
        friend class WindowCallbacks;

    private:
        GLFWwindow* window;
        InputController* customInputController;
        InputController* cameraInputController;

        int width;
        int height;
        std::string name;
        bool framebufferResized = false;

        double currentTime = 0.0f;
        float deltaTime = 0.0f;


        void initWindow();

    public:
        Window(int, int, const std::string&&);
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        ~Window();

        bool shouldClose();
        void pollEvents();
        void createWindowSurface(VkInstance, VkSurfaceKHR*);

        GLFWwindow* handle() const { return window; }

        VkExtent2D getExtent() const {
            return {
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)
            };
        }

        bool wasWindowResized() const {
            return framebufferResized;
        }

        void resetWindowResizedFlag() {
            framebufferResized = false;
        }

        void updateInputs();

        void setDefaultInputController(InputController *inputController);
        void setCameraInputController(InputController *inputController);

        void enablePointer();
        void disablePointer();

        bool mouseHold(int button);
        bool keyHold(int key);
        int getSpecialKeyState();

    private:
        void resizeCallback(int width, int height);
        void keyCallback(int key, int scancode, int action, int mods);
        void mouseMoveCallback(double mouseX, double mouseY);
        void mouseButtonCallback(int button, int action, int mods);
        void scrollCallback(double offsetX, double offsetY);


        struct MousePosition {
            int x;
            int y;
        };

        struct MouseMove {
            int deltaX;
            int deltaY;
        };

        struct MouseButtons {
            int mouseButtonAction;
            int mouseButtonStates;
        };

        struct MouseScroll {
            int scrollDeltaX;
            int scrollDeltaY;
        };

        struct InputStates {
            MousePosition mousePosition{};
            std::optional<MouseMove> mouseMove = std::nullopt;
            MouseButtons mouseButtons{};
            std::optional<MouseScroll> mouseScroll = std::nullopt;
            int keyMods = 0;
            std::queue<int> keyEvents = std::queue<int>();
            bool keyStates[384] = {false};
            bool keyScanCode[512] = {false};
        };
    public:
        InputStates inputStates;

        void setWindowCallbacks() const;

        float computeDeltaTime();

        float getDeltaTime();
    };

} // ve
