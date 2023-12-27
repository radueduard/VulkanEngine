#include "camera.hpp"

#include <cassert>
#include <limits>

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace ve {

    void Camera::setPerspectiveProjection(float fov, float aspect, float zNear, float zFar) {
        assert(glm::abs(aspect - std::numeric_limits<float>::epsilon()) > 0.0f);
        const float tanHalfFovy = glm::tan(fov / 2.f);
        projectionMatrix = glm::mat4{0.0f};
        projectionMatrix[0][0] = 1.f / (aspect * tanHalfFovy);
        projectionMatrix[1][1] = 1.f / (tanHalfFovy);
        projectionMatrix[2][2] = zFar / (zFar - zNear);
        projectionMatrix[2][3] = 1.f;
        projectionMatrix[3][2] = -(zFar * zNear) / (zFar - zNear);
    }

    void Camera::setOrthographicProjection(float left, float right, float bottom, float top, float near, float far) {
        projectionMatrix = glm::mat4{1.0f};
        projectionMatrix[0][0] = 2.f / (right - left);
        projectionMatrix[1][1] = 2.f / (bottom - top);
        projectionMatrix[2][2] = 1.f / (far - near);
        projectionMatrix[3][0] = -(right + left) / (right - left);
        projectionMatrix[3][1] = -(bottom + top) / (bottom - top);
        projectionMatrix[3][2] = -near / (far - near);
    }

    void Camera::setViewDirection(const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &up) {
        const glm::vec3 w{glm::normalize(direction)};
        const glm::vec3 u{glm::normalize(glm::cross(w, up))};
        const glm::vec3 v{glm::cross(w, u)};

        viewMatrix = glm::mat4{1.f};
        viewMatrix[0][0] = u.x;
        viewMatrix[1][0] = u.y;
        viewMatrix[2][0] = u.z;
        viewMatrix[0][1] = v.x;
        viewMatrix[1][1] = v.y;
        viewMatrix[2][1] = v.z;
        viewMatrix[0][2] = w.x;
        viewMatrix[1][2] = w.y;
        viewMatrix[2][2] = w.z;
        viewMatrix[3][0] = -glm::dot(u, position);
        viewMatrix[3][1] = -glm::dot(v, position);
        viewMatrix[3][2] = -glm::dot(w, position);
    }

    void Camera::setViewTarget(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &up) {
        setViewDirection(position, target - position, up);
    }

    void Camera::setViewYZX(const glm::vec3& position, glm::vec3 rotation) {
        const float c3 = glm::cos(rotation.z);
        const float s3 = glm::sin(rotation.z);
        const float c2 = glm::cos(rotation.x);
        const float s2 = glm::sin(rotation.x);
        const float c1 = glm::cos(rotation.y);
        const float s1 = glm::sin(rotation.y);
        const glm::vec3 u{(c1 * c3 + s1 * s2 * s3), (c2 * s3), (c1 * s2 * s3 - c3 * s1)};
        const glm::vec3 v{(c3 * s1 * s2 - c1 * s3), (c2 * c3), (c1 * c3 * s2 + s1 * s3)};
        const glm::vec3 w{(c2 * s1), (-s2), (c1 * c2)};
        viewMatrix = glm::mat4{1.f};
        viewMatrix[0][0] = u.x;
        viewMatrix[1][0] = u.y;
        viewMatrix[2][0] = u.z;
        viewMatrix[0][1] = v.x;
        viewMatrix[1][1] = v.y;
        viewMatrix[2][1] = v.z;
        viewMatrix[0][2] = w.x;
        viewMatrix[1][2] = w.y;
        viewMatrix[2][2] = w.z;
        viewMatrix[3][0] = -glm::dot(u, position);
        viewMatrix[3][1] = -glm::dot(v, position);
        viewMatrix[3][2] = -glm::dot(w, position);
    }

    void Camera::moveForward(float distance) {
        auto dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
        position += distance * dir;
    }

    void Camera::moveRight(float distance) {
        auto dir = glm::normalize(glm::vec3(right.x, 0, right.z));
        position += distance * dir;
    }

    void Camera::moveUp(float distance) {
        position += distance * glm::vec3(0, -1, 0);
    }

    void Camera::updateSpeed(float speed) {
        this->speed += speed;
    }

    void Camera::rotateOX(float angle) {
        forward = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, right)) * forward;
        right = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, right)) * right;
        up = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, right)) * up;
    }

    void Camera::rotateOY(float angle) {
        forward = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0))) * forward;
        right = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0))) * right;
        up = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0))) * up;
    }

    void Camera::rotateOZ(float angle) {
        forward = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, forward)) * forward;
        right = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, forward)) * right;
        up = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, forward)) * up;
    }

    void Camera::update() {
        setViewDirection(position, forward, up);
    }
}