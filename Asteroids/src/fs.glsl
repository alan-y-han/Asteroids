#version 330 core
out vec4 fColor;

in vec3 vColor;

uniform float alpha;

void main()
{
    fColor = vec4(mix(vec3(0.0f), vColor, alpha), 1.0f);
}
