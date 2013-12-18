#version 330 core

#define M_PI 3.1415926535897932384626433832795

uniform mat4 model, view, proj;
uniform vec3 light_pos;

in vec3 vPos, vNormal;
in vec4 vCol;

out vec3 fPos;
out vec3 fN, fE, fL;
out vec4 fColor;

void main() {
    mat4 modelView = view * model;

	fPos = (modelView * vec4(vPos, 1.f)).xyz;
    gl_Position = proj * vec4(fPos, 1);
    
    fE = -vec3(fPos.x, fPos.z, fPos.y);
    //fE = -fPos;
    fL = (view * vec4(light_pos, 0)).xyz;
    fN = (modelView * vec4(vNormal, 0)).xyz;

    fColor = vCol;
}