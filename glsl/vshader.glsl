#version 330 core

#define M_PI 3.1415926535897932384626433832795

uniform mat4 model, view;
uniform vec3 light_pos;
uniform float light_ambient;

in vec3 vPos;
in vec4 vCol;
in vec3 vNormal;

out vec3 fPos;
out vec4 fColor;
out vec3 fNormal;

void main() {
    mat4 modelView = view * model;

    // position
	vec4 modelPos = modelView * vec4(vPos.xyz, 1.f);
	fPos = modelPos.xyz;
    gl_Position = modelPos;

    // blend
    fColor = vCol;

    // light

    fNormal = normalize(vNormal);
    vec3 E = normalize(-fPos);
    vec3 L = (view * vec4(light_pos, 1)).xyz;
    vec3 H = normalize(L + E); // halfway vector
    vec3 N = normalize(modelView * vec4(vNormal, 0.0)).xyz;

    //vec4 ambient = vec4(light_ambient);

    //float Kd = max(dot(L, N), 0.0);
    //vec4 diffuse = Kd * DiffuseProduct;

    //float Ks = pow(max(dot(N, H), 0.0), Shininess);
    //vec4 specular = Ks * SpecularProduct;
}