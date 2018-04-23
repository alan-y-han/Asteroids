#version 330 core
layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;

out vec3 vColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    //gl_Position = projection * view * model * vec4(inPos, 1.0);
	vColor = inColor; // vec3(1.0f, 0.0f, 0.5f);
	gl_Position = vec4(inPos, 1.0);
}
