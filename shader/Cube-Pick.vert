#version 460 core
layout (location = 0) in vec3 aPos;
uniform mat4 MVP;
flat out int face_id;

void main()
{
   gl_Position = MVP * vec4(aPos, 1.0);
   face_id = gl_VertexID / 3;
}
