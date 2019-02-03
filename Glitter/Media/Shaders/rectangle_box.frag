#version 330 core
in vec3 colour;
in vec2 texelCoord;
uniform sampler2D inputImageTexture;
out vec4 FragColor;
void main()
{
    vec4 texelColor = texture(inputImageTexture, texelCoord);
    FragColor = texelColor * vec4(colour,1.0f);
}

