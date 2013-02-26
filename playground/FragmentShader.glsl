#version 330
uniform vec4 Color;
uniform sampler2D gSampler;
in vec2 TexCoord0;
out vec4 FragColor;

void main()
{
	FragColor = texture2D(gSampler, TexCoord0.st);
	if (FragColor.a > 0)
	{
		FragColor = FragColor * Color;
	}
}