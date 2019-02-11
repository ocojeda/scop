// Version du GLSL

#version 400

layout (location = 0) in vec3 position;


uniform mat4	mvp;
uniform float magnitude;

flat out vec4	fragment_color;
out	vec2		texture_coordinates;

float	ft_map(float x, float lenght, float min, float max)
{
	float	a;
	return (a = (x / (lenght / (max - min))) + min);
}

float round_color(float col)
{
	
	if (col < 0)
		col *= -1;
	return ft_map(col, magnitude, 0, 1);
}

void	main()
{
	gl_Position = mvp * vec4(position, 1.0f);
	fragment_color = vec4(round_color(position.x), round_color(position.y), round_color(position.z), 1);
	texture_coordinates = vec2(ft_map(position.x, 1, 0, 1) + position.z , (ft_map(position.y , 1, 0, -1)));
}