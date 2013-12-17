#version 330 core

#define M_PI 3.1415926535897932384626433832795

uniform mat4 model, view;
uniform vec3 light_pos;

in vec3 vPos;
in vec3 vNormal;
in vec4 vCol;

out vec4 fPos;
out vec4 fColor;
out vec3 fNormal;

void main() {
    mat4 modelView = view * model;

    vec4 normal = model * (vec4(vNormal.xyz, 1) + vec4(vPos.xyz, 1.f));
                - vec4(vPos.xyz, 1.f);
    fNormal = normal.xyz;


	vec4 modelPos = modelView * vec4(vPos.xyz, 1.f);
	fPos = modelPos;
    gl_Position = modelPos;

    fColor = vCol;
}