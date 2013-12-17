#version 330 core

uniform mat4 model, view;
uniform vec3 light_pos;
uniform float light_ambient;

uniform vec3 ka, kd, ks;
uniform float ns, tr;

uniform vec4 fog_color;
uniform float fog_mag;

uniform vec4 blend_color;
uniform vec4 blend_factor;

in vec3 fPos;
in vec4 fColor;
in vec3 fN, fE, fL;

void main() {
    // light
    vec3 N = normalize(fN);
    vec3 E = normalize(fE);
    vec3 L = normalize(fL);
    vec3 H = normalize(L + E);

    vec3 ambient = ka + light_ambient;
    vec3 diffuse =  max(dot(L, N), 0) * kd;
    vec3 specular = 0 * pow(dot(N, H), ns) * ks;
    if (dot(N, H) < 0)
        specular = vec3(0, 0, 0);

    vec4 afterLight = vec4(ambient + diffuse + specular, tr);
    
    // fog
    vec4 afterFog = mix(afterLight, fog_color, clamp(fog_mag * fPos.z, 0, 1));

    gl_FragColor = afterFog;
}