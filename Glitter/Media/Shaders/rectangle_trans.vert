#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexelCoord;
uniform mat4 transform;
out vec3 colour;
out vec2 texelCoord;
void main()
{
    gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    colour = aColor;
    texelCoord = vec2(1.0-aTexelCoord.x, 1.0 - aTexelCoord.y); ;
}
