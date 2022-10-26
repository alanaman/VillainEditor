#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 uProjViewModelMat;

void main()
{
   gl_Position = uProjViewModelMat * vec4(position, 1);
   //gl_Position = u_viewProjectionMatrix * vec4(position, 1);
};