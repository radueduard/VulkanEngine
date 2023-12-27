#include "world.hpp"

#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main() {

    ve::Window window(1920, 1080, "Test window");
    ve::World::instantiate(window);

    try {
        ve::World::getInstance()->run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
