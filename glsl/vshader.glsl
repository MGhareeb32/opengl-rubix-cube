#version 330 core

#define M_PI 3.1415926535897932384626433832795

uniform mat4 model, view, proj;

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;

out mat4 modelView;
out vec3 fPos;
out vec3 fNormal;

void main() {
    modelView = view * model;
    mat4 normal = inverse(transpose(modelView));

	fPos = (modelView * vec4(vPos, 1.f)).xyz;
	fNormal = vNormal;

    gl_Position = proj * vec4(fPos, 1);
}