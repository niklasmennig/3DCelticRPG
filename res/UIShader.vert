#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aUv;
out vec3 VertexColor;
out vec2 TexCoords;

void main()
{
   gl_Position = vec4(aPos.x, aPos.z, aPos.x, 1.0);
   VertexColor = aCol;
   TexCoords = aUv;
};