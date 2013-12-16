#version 330 core

#define M_PI 3.1415926535897932384626433832795

uniform mat4 model, view;


in vec3 pos;
in vec4 col;

out vec4 outPos;
out vec4 outColor;

void main() {
	vec4 modelPos = view * model * vec4(pos.xyz, 1.f);
	outPos = modelPos;
    gl_Position = modelPos;

    outColor = col;
}