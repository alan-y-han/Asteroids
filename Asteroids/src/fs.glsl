#version 330 core
out vec4 fColor;

in vec3 vColor;

void main()
{
    fColor = vec4(vColor, 1.0);
}
