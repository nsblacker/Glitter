#version 330 core
in vec2 texelCoord;
uniform sampler2D inputImageTexture;
uniform sampler2D inputImageTexture2;
out vec4 FragColor;
void main()
{
    vec4 texelColor = texture(inputImageTexture, texelCoord);
    vec4 texelColor2 = texture(inputImageTexture2, texelCoord);
    FragColor = mix(texelColor, texelColor2, 0.2);
}
