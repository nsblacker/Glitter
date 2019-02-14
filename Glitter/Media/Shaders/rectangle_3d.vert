#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexelCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec2 texelCoord;
void main()
{
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    texelCoord = vec2(1.0-aTexelCoord.x, 1.0 - aTexelCoord.y); ;
}
