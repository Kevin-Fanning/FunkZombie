#version 330
in vec3 Position;
in vec2 TexCoord;
out vec2 TexCoord0;
uniform mat4 MVP;
void main()
{
	gl_Position = MVP * vec4( Position, 1.0 );
	TexCoord0 = TexCoord;
}