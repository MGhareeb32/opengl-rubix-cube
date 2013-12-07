#version 330 core

uniform vec4 blend_color;
uniform vec4 blend_factor;

in vec4 outColor;

void main() {
    gl_FragColor
        = vec4(outColor.x * (1 - blend_factor.x)
               + blend_color.x * blend_factor.x,

               outColor.y * (1 - blend_factor.y)
               + blend_color.y * blend_factor.y,

               outColor.z * (1 - blend_factor.z)
               + blend_color.z * blend_factor.z,

               outColor.w * (1 - blend_factor.w)
               + blend_color.w * blend_factor.w);
}