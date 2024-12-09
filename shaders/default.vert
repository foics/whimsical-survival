#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_texCoords;

out vec2 texCoords;

uniform mat4 projection;
uniform mat4 model;

void main() {
    texCoords = a_texCoords;
    gl_Position = projection * model * vec4(a_pos, 1.0);
}
