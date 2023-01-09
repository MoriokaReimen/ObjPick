#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in int aselect;
out vec4 color;
uniform mat4 MVP;

void main()
{
   gl_Position = MVP * vec4(aPos, 1.0);
   if(aselect == 1)
   {
     color = vec4(1.0, 0, 0.0, 1.0);
   } else {
     color = vec4(0.0, 0, 0.5, 1.0);
   }
}
