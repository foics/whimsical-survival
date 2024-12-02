#version 330 core
out vec4 fragColor;

// in vec2 texCoords;

uniform vec4 color;

void main() {
    fragColor = color;
}
