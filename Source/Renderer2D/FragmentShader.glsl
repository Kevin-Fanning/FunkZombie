#version 330
uniform vec4 Color;
uniform sampler2D gSampler;
in vec2 TexCoord0;
in vec3 Color0;
out vec4 FragColor;

void main()
{
	//FragColor = texture2D(gSampler, TexCoord0.st);
	FragColor = (FragColor.r, 1.0, 1.0, 1.0);
	if (FragColor.a > 0)
	{
		//FragColor = FragColor * Color;
	}
}