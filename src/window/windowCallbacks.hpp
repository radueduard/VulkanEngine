#pragma once

#include <GLFW/glfw3.h>

namespace ve {
    class WindowCallbacks {
    public:
        static void resizeCallback(GLFWwindow* window, int width, int height);
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    };
}
