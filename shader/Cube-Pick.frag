#version 460 core
out vec3 FragColor;

void main()
{
   FragColor = vec3(8, 0, gl_PrimitiveID);
}
