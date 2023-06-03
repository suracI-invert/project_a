#version 330 core
out vec4 Color;

in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
	Color = texture(texture1, TexCoord);
}