#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aUv;
out vec3 VertexColor;
out vec2 TexCoords;
uniform mat4 projection;
uniform mat4 view;

void main()
{
   gl_Position = projection * view * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   VertexColor = aCol;
   TexCoords = aUv;
};