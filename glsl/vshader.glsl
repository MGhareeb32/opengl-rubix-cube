#version 330 core

#define M_PI 3.1415926535897932384626433832795

uniform mat4 model, view, proj;
uniform vec3 light_pos;

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;

out vec3 fPos;
out vec3 fN, fL, fE;

void main() {
    mat4 modelView = view * model;
    mat4 normal = inverse(transpose(modelView));

	fPos = (modelView * vec4(vPos, 1.f)).xyz;

    fN = (modelView * vec4(vNormal, 0)).xyz;
    fL = (view * vec4(light_pos, 0)).xyz;
    //fE = -vec3(fPos.x, fPos.y, -fPos.z);
    fE = -fPos;

    gl_Position = proj * vec4(fPos, 1);
}