#version 460 core
layout (location = 0) in vec3 aPos;
out vec4 color;
uniform mat4 MVP;

void main()
{
   color = MVP * vec4(aPos, 1.0);
   gl_Position = MVP * vec4(aPos, 1.0);
}
