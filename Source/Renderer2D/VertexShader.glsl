#version 330
in vec3 Position;
in vec3 Color;
in vec2 TexCoord;
out vec2 TexCoord0;
out vec3 Color0;
uniform mat4 MVP;
void main()
{
	gl_Position = vec4( Position, 1.0 );
	TexCoord0 = TexCoord;
	Color0 = Color;
}