/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 09:22:15 by ocojeda-          #+#    #+#             */
/*   Updated: 2019/02/09 17:46:21 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vec3	center_search(GLfloat *vertices, int num_vertices)
{
	int		i;
	t_vec3	max;
	t_vec3	min;
	t_vec3	center;

	i = 0;
	max = vec3(0, 0, 0);
	min = vec3(0, 0, 0);
	while (i < num_vertices - 6)
	{
		vertices[i] > max.v[0] ? max.v[0] = vertices[i] : 0;
		vertices[i] < min.v[0] ? min.v[0] = vertices[i] : 0;
		vertices[i + 1] > max.v[1] ? max.v[1] = vertices[i + 1] : 0;
		vertices[i + 1] < min.v[1] ? min.v[1] = vertices[i + 1] : 0;
		vertices[i + 2] > max.v[2] ? max.v[2] = vertices[i + 2] : 0;
		vertices[i + 2] < min.v[2] ? min.v[2] = vertices[i + 2] : 0;
		i += 6;
	}
	center = vec3_fmul(vec3_add(max, min), 0.5);
	return (center);
}

void	center_all_vertices(t_env *env, int length)
{
	int		i;

	i = 0;
	while (i < length)
	{
		env->model.vertices[i] -= env->model.center_axis.v[0];
		env->model.vertices[i + 1] -= env->model.center_axis.v[1];
		env->model.vertices[i + 2] -= env->model.center_axis.v[2];
		i += 6;
	}
}

void	set_obj_values(t_env *env, int v, int f)
{
	int i;

	i = 0;
	env->model.depth = 0;
	while (env->model.vertices[i])
	{
		if (env->model.depth < env->model.vertices[i + 2])
			env->model.depth = env->model.vertices[i + 2];
		i += 6;
	}
	env->model.size_vertices = v * sizeof(GLfloat);
	env->model.size_indices = f * sizeof(GLuint);
	env->model.num_indices = f;
	env->model.center_axis = center_search(env->model.vertices, v);
}

void	load_obj(t_env *e, char *filename)
{
	int		fd;
	int		v;
	int		f;
	char	*line;

	v = 0;
	f = 0;
	e->model.vertices = (GLfloat*)malloc(sizeof(GLfloat) * 3);
	e->model.indices = (GLuint*)malloc(sizeof(GLuint) * 3);
	if ((fd = open(filename, O_RDWR)) == -1 || check_obj(filename))
		ft_error("obj file opening failed.");
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'v' && line[1] == ' ')
			e->model.vertices = append_vertices(e->model.vertices, line, &v);
		else if (line[0] == 'f' && line[1] == ' ')
			e->model.indices = append_indices(e->model.indices, line, &f);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	set_obj_values(e, v, f);
	close(fd);
	center_all_vertices(e, v);
}
