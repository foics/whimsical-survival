#version 330 core
out vec4 fragColor;

in vec2 texCoords;

uniform vec4 color;
uniform sampler2D texImage;

void main() {
    vec4 texColor = color * texture(texImage, texCoords);

    if (texColor.a < 0.1)
        discard;

    fragColor = texColor;
}
