#version 150

#define M_PI 3.1415926535897932384626433832795

uniform vec2 offset;
uniform vec2 scale;
uniform float rotAngle;

in vec2 vPosition;
in vec4 vColor;

out vec4 outColor;

void main() {
	// rotation
    float sinRotAng = sin(rotAngle);
    float cosRotAng = cos(rotAngle);
    mat2 rotMatrix;
    rotMatrix[0][0] = cosRotAng, rotMatrix[0][1] = -sinRotAng,
    rotMatrix[1][0] = sinRotAng, rotMatrix[1][1] =  cosRotAng;

	vec2 pos = (rotMatrix * vPosition) * scale - offset;

    gl_Position = vec4(pos.xy, 0.0, 1.0);
    outColor = vColor;
}