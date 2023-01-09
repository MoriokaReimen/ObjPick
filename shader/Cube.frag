#version 460 core

in vec4 color;
out vec4 FragColor;

void main()
{
   // FragColor = vec4(color.xyz, 1.0);
   FragColor = vec4(0.0008, 0, gl_PrimitiveID / 12.0, 1.0);
   if(gl_PrimitiveID == 3)
   FragColor = vec4(1.0, 0, gl_PrimitiveID / 12.0, 1.0);
}
