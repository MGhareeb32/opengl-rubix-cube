#version 330 core

uniform mat4 model, view;

uniform float scene_fog;
uniform vec3 scene_color;

uniform vec3 light_pos;
uniform vec3 light_ambient, light_diffuse, light_specular;

uniform vec3 ka, kd, ks;
uniform float ns, tr;

uniform vec4 blend_color;
uniform vec4 blend_factor;

in vec3 fPos;
in vec3 fN, fL, fE;

vec3 rgb2hsv(vec3 c) {
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main() {
    // LIGHT
    vec3 N = normalize(fN);
    vec3 E = vec3(0, 0, 1);
    if (dot(N, E) < 0)
        discard;
    vec3 L = normalize(fL);
    vec3 H = normalize(L + E);
 
    vec3 ambient = light_ambient * ka;
    vec3 diffuse = light_diffuse * kd * max(dot(L, N), 0);
    vec3 specular = light_specular * ks * pow(max(dot(N, H), 0), 0.1 * ns);

    vec3 afterLight = (scene_color + ambient + diffuse + specular);

    // FOG
    vec3 afterFog = mix(afterLight, scene_color,
                        clamp(0 * -scene_fog * fPos.z, 0, 1));

    gl_FragColor = vec4(afterFog, tr * blend_color.a);
}