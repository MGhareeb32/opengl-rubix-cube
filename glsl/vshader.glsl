#version 150

uniform vec2 offset;
uniform vec2 scale;

in vec2 vPosition;
in vec4 vColor;

out vec4 outColor;

void main() {
    gl_Position = vec4(vPosition.x * scale.x - offset.x,
                       vPosition.y * scale.y - offset.y, 0.0, 1.0);
    outColor = vColor;
}