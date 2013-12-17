#version 330 core

#define M_PI 3.1415926535897932384626433832795

uniform mat4 model, view;
uniform vec3 light_pos;
uniform float light_ambient;

uniform vec3 ka, kd, ks;
uniform float ns, tr;

in vec3 vPos;
in vec4 vCol;
in vec3 vNormal;

out vec3 fPos;
out vec4 fColor;
out vec3 fN, fE, fL;

void main() {
    mat4 modelView = view * model;

    // position
	vec4 modelPos = modelView * vec4(vPos.xyz, 1.f);
    gl_Position = modelPos;
	fPos = modelPos.xyz;

    // blend
    fColor = vCol;

    // light
    fE = -fPos;
    fL = (view * vec4(light_pos, 1)).xyz - fPos;
    fN = (modelView * vec4(vNormal, 0)).xyz;
}