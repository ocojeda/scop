/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 09:22:26 by ocojeda-          #+#    #+#             */
/*   Updated: 2019/02/07 16:28:42 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	shaders_creator(t_env *env)
{
	GLuint	shader_vert;
	GLuint	shader_frag;

	shader_vert = create_shader("../Shaders/basique2D.vert", \
	GL_VERTEX_SHADER);
	shader_frag = create_shader("../Shaders/basique2D.frag", \
	GL_FRAGMENT_SHADER);
	env->shader.program = create_shader_program(shader_vert, shader_frag);
	env->shader.mvploc = glGetUniformLocation(env->shader.program, "mvp");
	env->shader.tmdloc = glGetUniformLocation(env->shader.program, "tmod");
	env->shader.gmdloc = glGetUniformLocation(env->shader.program, "gmod");
	env->shader.texloc = glGetUniformLocation(env->shader.program, "ltexture");
	env->shader.magnitude = glGetUniformLocation(env->shader.program, \
	"magnitude");
}

void	create_buffers(t_env *env, int mode)
{
	glGenBuffers(1, &env->buffer.vbo);
	glGenBuffers(1, &env->buffer.ebo);
	glGenVertexArrays(1, &env->buffer.vao);
	glBindVertexArray(env->buffer.vao);
	glBindBuffer(GL_ARRAY_BUFFER, env->buffer.vbo);
	glBufferData(GL_ARRAY_BUFFER, env->model.size_vertices,
		env->model.vertices, mode);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->buffer.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, env->model.size_indices,
		env->model.indices, mode);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	create_texture(env);
}

void	init(t_env *env, int argc, char **argv)
{
	if (argc == 2)
	{
		env->model.filename = ft_strjoin("../", argv[1]);
		env->cam.fov = FOV;
		env->width = WIN_WIDTH;
		env->height = WIN_HEIGHT;
		env->ratio = (float)env->width / (float)env->height;
		init_glfw_env();
		init_glfw_win(env);
		load_obj(env, env->model.filename);
		load_bmp(env, "../resources/duck_original.bmp");
		shaders_creator(env);
		create_buffers(env, GL_DYNAMIC_DRAW);
		glEnable(GL_DEPTH_TEST);
		init_cam(env);
		init_matrices(env);
		env->flag_texture = 0;
	}
}
