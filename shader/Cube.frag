#version 460 core

in vec4 color;
out vec4 FragColor;

void main()
{
   FragColor = vec4(color.xyz, 1.0f);
}
