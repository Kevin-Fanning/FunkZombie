#version 120
uniform vec4 Color;
uniform sampler2D gSampler;
varying vec2 TexCoord0;
varying vec3 Color0;

void main()
{
	gl_FragColor = vec4(Color0, texture2D(gSampler, TexCoord0.st).w);
}