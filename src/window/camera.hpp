#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace ve {
    class Camera {
    public:
        Camera() = default;
        Camera(const Camera&) = delete;
        Camera& operator=(const Camera&) = delete;
        ~Camera() = default;

        void setPerspectiveProjection(float fov, float aspect, float zNear, float zFar);
        void setOrthographicProjection(float left, float right, float bottom, float top, float zNear, float zFar);

        void setViewDirection(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up = {0.0f, -1.0f, 0.0f});
        void setViewTarget(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up = {0.0f, -1.0f, 0.0f});
        void setViewYZX(const glm::vec3& position, glm::vec3 rotation);

        const glm::mat4& projection() const { return projectionMatrix; }
        const glm::mat4& view() const { return viewMatrix; }

        void moveForward(float distance);
        void moveRight(float distance);
        void moveUp(float distance);

        void updateSpeed(float speed);

        void rotateOX(float angle);
        void rotateOY(float angle);

        void update();

        glm::vec3 getPosition() const { return position; }

    private:
        glm::mat4 projectionMatrix{1.0f};
        glm::mat4 viewMatrix{1.0f};

        float distanceToTarget = 10.0f;

        glm::vec3 position{0.0f};
        glm::vec3 forward {0, 0, 1};
        glm::vec3 up {0, -1, 0};
        glm::vec3 right {1, 0, 0};

        float speed = 1.f;

        void rotateOZ(float angle);
    };
}
