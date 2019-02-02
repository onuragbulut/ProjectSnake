#version 330 core

in vec2 TexCoord;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform sampler2D colorTexture;

void main()
{
	FragColor = vec4(texture(colorTexture, TexCoord).rgb, 1.0);
    BrightColor = FragColor;
}
