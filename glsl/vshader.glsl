#version 330 core

#define M_PI 3.1415926535897932384626433832795

uniform mat4 model, view, proj;
uniform vec3 light_pos;

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec4 vCol;

out vec3 fPos;
out vec3 fN, fL, fE;
out vec4 fColor;

void main() {
    mat4 modelView = view * model;
    mat4 normal = inverse(transpose(modelView));

	fPos = (modelView * vec4(vPos, 1.f)).xyz;

    fN = (normal * vec4(vNormal, 0)).xyz;
    fL = (view * vec4(light_pos, 1)).xyz;
    //fE = -vec3(fPos.x, fPos.y, -fPos.z);
    fE = -fPos;

    fColor = vCol;

    gl_Position = proj * vec4(fPos, 1);
}