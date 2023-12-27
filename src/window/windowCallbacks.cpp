#include "windowCallbacks.hpp"
#include "window.hpp"

namespace ve {
    void WindowCallbacks::resizeCallback(GLFWwindow *window, int width, int height) {
        auto app = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
        app->resizeCallback(width, height);
    }

    void WindowCallbacks::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        auto app = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
        app->keyCallback(key, scancode, action, mods);
    }

    void WindowCallbacks::mouseMoveCallback(GLFWwindow *window, double xpos, double ypos) {
        auto app = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
        app->mouseMoveCallback(xpos, ypos);
    }

    void WindowCallbacks::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
        auto app = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
        app->mouseButtonCallback(button, action, mods);
    }

    void WindowCallbacks::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
        auto app = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
        app->scrollCallback(xoffset, yoffset);
    }
}