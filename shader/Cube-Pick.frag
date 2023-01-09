#version 460 core
out vec4 FragColor;

void main()
{
   FragColor = vec4(0.0008, 0, gl_PrimitiveID / 10000.0 , 1.0);
}
