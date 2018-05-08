#version 330 core
in vec3 vColor;

out vec4 fColor;

uniform float alpha;

void main()
{
    fColor = vec4(mix(vec3(0.0f), vColor, alpha), 1.0f);
}
