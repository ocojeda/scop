// Version du GLSL

#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform mat4	mvp;
uniform int		cmod;
uniform bool	mmod;

flat out vec4	fragment_color_f;
smooth out vec4	fragment_color_s;
out	vec2		texture_coordinates;

float	ft_map(float x, float lenght, float min, float max)
{
	float	a;
	return (a = (x / (lenght / (max - min))) + min);
}

float round_color(float col)
{
	if (col < 0)
		col = col * -1;
	return (ft_map(col, 3, 0, 1));
}
void	main()
{
	gl_Position = mvp * vec4(position, 1.0f);
	fragment_color_s = vec4(round_color(position.x), round_color(position.y), round_color(position.z), 1);
	fragment_color_f = fragment_color_s;
	texture_coordinates = vec2(position.x / 2, position.y / -1);
}