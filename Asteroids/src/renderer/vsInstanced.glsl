#version 330 core
layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in float inAlpha;
layout(location = 3) in mat4 inModel;

out vec3 vColor;
out float vAlpha;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * inModel * vec4(inPos, 1.0);
	vColor = inColor;
	vAlpha = inAlpha;
}
