// Version du GLSL

#version 410 

flat in vec4		fragment_color_f;
smooth in vec4		fragment_color_s;
in vec2				texture_coordinates;

uniform bool		tmod;
uniform bool		gmod;
uniform sampler2D	ltexture;

out vec4		color;

void	main()
{
	float	grey;
	
	color = fragment_color_f;
	if (tmod)
		color = texture(ltexture, texture_coordinates);
	if (gmod)
	{
		color = vec4(color.x, color.y, color.z, 1.0f);
	}
}
