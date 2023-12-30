#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 uv;

layout (location = 0) out vec3 fragColor;
layout (location = 1) out vec3 fragPosition;
layout (location = 2) out vec3 fragNormal;

layout(push_constant) uniform Push {
    mat4 model;
} push;

layout (set = 0, binding = 0) uniform Camera {
    mat4 view;
    mat4 proj;
} camera;

void main()
{
    fragColor = color;
    fragPosition = (push.model * vec4(position, 1)).xyz;
    fragNormal = normalize(mat3(push.model) * normal);
    gl_Position = camera.proj * camera.view * push.model * vec4(position, 1.0);
}