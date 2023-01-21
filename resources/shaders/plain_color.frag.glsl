#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 prop_Color;

void main()
{
   color = vec4(prop_Color, 1);
};