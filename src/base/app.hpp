#pragma once

#include "engine/device.hpp"
#include "window/window.hpp"
#include "engine/gameObject.hpp"
#include "engine/renderer.hpp"
#include <engine/descriptors.hpp>

#include <unordered_map>
#include <memory>
#include <vector>

namespace ve {

    class App : public InputController {
    private:
        Window& window;
    protected:
        Device device;
    private:
        Renderer renderer;
    protected:
        std::unique_ptr<DescriptorPool> globalPool{};
        std::unordered_map<size_t, GameObject> gameObjects;

    public:
        explicit App(Window & window);
        App(const App&) = delete;
        App& operator=(const App&) = delete;
        ~App() override;

        void run();

    protected:
        virtual void init() {};
        virtual void update(float deltaTime) {}

        Camera camera;
    };

} // ve
