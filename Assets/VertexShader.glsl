#version 120
attribute vec3 Position;
attribute vec3 Color;
attribute vec2 TexCoord;
varying vec2 TexCoord0;
varying vec3 Color0;
uniform mat4 MVP;
void main()
{
	gl_Position = vec4( Position, 1.0 );
	TexCoord0 = TexCoord;
	Color0 = Color;
}