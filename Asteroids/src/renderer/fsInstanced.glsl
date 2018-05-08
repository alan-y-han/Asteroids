#version 330 core
out vec4 fColor;

in vec3 vColor;
in float vAlpha;

void main()
{
	vec3 mixColor = mix(vec3(0.0f), vColor, vAlpha);
    fColor = vec4(mixColor, 1.0f);
}
