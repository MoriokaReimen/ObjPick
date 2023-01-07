#version 460 core
uniform mat4 MVP;
layout(location=0) in vec3 vPos;
out vec3 color;

void main()
{
    gl_Position = vec4(vPos, 1.0);
}
