#version 450 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 6) out;

layout(location = 0) in vec3 vertPosition[3];
layout(location = 1) in vec3 vertNormal[3];
layout(location = 2) in vec2 vertTexCoords[3];

layout(location = 0) out vec3 fragPosition;
layout(location = 1) out vec3 fragNormal;
layout(location = 2) out vec2 fragTexCoords;

void main() {
    for(int i = 0; i < 3; i++) {
        fragPosition = vertPosition[i];
        fragNormal = vertNormal[i];
        fragTexCoords = vertTexCoords[i];

        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();

    for(int i = 0; i < 3; i++) {
        fragPosition = vertPosition[i] + vec3(0.0, 0.0, 10.0);
        fragNormal = vertNormal[i];
        fragTexCoords = vertTexCoords[i];

        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}