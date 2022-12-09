#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 uProjViewModelMat;
uniform mat4 uTransform;

void main()
{
   gl_Position = uProjViewModelMat * uTransform * vec4(position, 1);
   //gl_Position = u_viewProjectionMatrix * vec4(position, 1);
};