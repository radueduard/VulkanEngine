#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 uv;

layout (location = 0) out vec3 fragColor;
layout (location = 1) out vec3 fragPosition;
layout (location = 2) out vec3 fragNormal;
layout (location = 3) out vec2 fragUV;

layout (set = 0, binding = 0) uniform Camera {
    mat4 view;
    mat4 proj;
} camera;

layout(set = 1, binding = 0) uniform Object {
    mat4 model;
} object;

void main()
{
    fragColor = color;
    fragPosition = (object.model * vec4(position, 1)).xyz;
    fragNormal = normalize(mat3(object.model) * normal);
    fragUV = uv;
    gl_Position = camera.proj * camera.view * object.model * vec4(position, 1.0);
}