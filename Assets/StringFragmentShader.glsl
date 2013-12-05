#version 120
uniform sampler2D gSampler;
varying vec2 TexCoord0;
varying vec3 Color0;

void main()
{
	vec4 color = vec4(Color0, texture2D(gSampler, TexCoord0.st).w);
	//color = vec4(color.r, 1.0, 1.0, 1.0);
	if (color.a == 0.0)
	{
		discard;
	}
	gl_FragColor = color;
}