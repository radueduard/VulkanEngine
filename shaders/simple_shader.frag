#version 450 core

layout (location = 0) in vec3 color;
layout (location = 1) in vec3 position;
layout (location = 2) in vec3 normal;

layout (location = 0) out vec4 fragColor;

layout (set = 0, binding = 1) uniform Material
{
    float ambient;
    float diffuse;
    float specular;
    int shininess;
} material;

layout (set = 0, binding = 2) uniform Light
{
    vec3 position;
    vec3 eyePosition;
    vec3 color;
} light;



void main()
{
    vec3 N = normalize(normal);
    vec3 L = normalize(light.position - position);
    vec3 V = normalize(light.eyePosition - position);
    vec3 R = reflect(-L, N);

    float ambient = material.ambient * material.diffuse;
    float diffuse = material.diffuse * max(dot(N, L), 0.0);

    float specular = 0.0f;
    if (diffuse > 0.0)
    {
        specular = material.specular * pow(max(dot(V, R), 0.0), material.shininess);
    }

    float att = 1.0 / dot(light.position - position, light.position - position);

    fragColor = vec4((ambient + diffuse + specular) * att * light.color, 1.0);
}