/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 09:22:07 by ocojeda-          #+#    #+#             */
/*   Updated: 2019/01/30 17:55:23 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	compute_mvp_matrix(t_env *env)
{
	env->model.mvp = mat4_mul(mat4_transpose(env->model.model),
		mat4_mul(env->model.view, env->model.projection));
}

void			update_shader_uniforms(t_env *env)
{
	glUniformMatrix4fv(env->shader.mvploc, 1, GL_FALSE, env->model.mvp.m);
	glUniform1i(env->shader.tmdloc, env->flags.texture);
}

const GLchar	*get_shader_source(char *filename)
{
	int		fd;
	int		ret;
	char	buffer[BUFFER_SIZE];
	char	*source;
	char	*del;

	source = ft_strnew(BUFFER_SIZE);
	if ((fd = open(filename, O_RDONLY)) == -1)
		ft_error("shader source file opening failed.");
	while ((ret = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[ret] = '\0';
		del = source;
		source = ft_strjoin(source, buffer);
		ft_strdel(&del);
	}
	close(fd);
	return (source);
}

GLuint			create_shader(char *filename, int shader_type)
{
	GLint			success;
	GLuint			shader;
	const GLchar	*shader_source;

	shader_source = get_shader_source(filename);
	shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);
	free((void*)shader_source);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
		ft_error("shader compilation failed.");
	return (shader);
}

GLuint			create_shader_program(GLuint shader_vert, GLuint shader_frag)
{
	GLint	success;
	GLuint	shader_program;

	shader_program = glCreateProgram();
	glAttachShader(shader_program, shader_vert);
	glAttachShader(shader_program, shader_frag);
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
		ft_error("shader program compilation failed.");
	glDeleteShader(shader_vert);
	glDeleteShader(shader_frag);
	return (shader_program);
}

void			build_shader_program(t_env *env)
{
	GLuint	shader_vert;
	GLuint	shader_frag;

	shader_vert = create_shader("../Shaders/basique2D.vert", GL_VERTEX_SHADER);
	shader_frag = create_shader("../Shaders/basique2D.frag", GL_FRAGMENT_SHADER);
	env->shader.program = create_shader_program(shader_vert, shader_frag);
	env->shader.mvploc = glGetUniformLocation(env->shader.program, "mvp");
	env->shader.cmdloc = glGetUniformLocation(env->shader.program, "cmod");
	env->shader.tmdloc = glGetUniformLocation(env->shader.program, "tmod");
	env->shader.gmdloc = glGetUniformLocation(env->shader.program, "gmod");
	env->shader.mmdloc = glGetUniformLocation(env->shader.program, "mmod");
	env->shader.texloc = glGetUniformLocation(env->shader.program, "ltexture");
}

void	create_texture(t_env *env)
{
	glGenTextures(1, &env->buffer.texture);
	glBindTexture(GL_TEXTURE_2D, env->buffer.texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, env->model.texture.w,
	env->model.texture.h, 0, GL_RGB, GL_UNSIGNED_BYTE, env->model.texture.img);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
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

void	clean_glfw(t_env *env)
{
	glDeleteVertexArrays(1, &env->buffer.vao);
	glDeleteBuffers(1, &env->buffer.vbo);
	glDeleteBuffers(1, &env->buffer.ebo);
	free(env->model.filename);
	glfwTerminate();
}



int main(int argc, char **argv)
{
	t_env env;
	init(&env, argc, argv);
	load_obj(&env, env.model.filename);
	load_bmp(&env, "../resources/duck_original.bmp");
	build_shader_program(&env);
	create_buffers(&env, GL_DYNAMIC_DRAW);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(env.ptr))
	{
		glfwPollEvents();
		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		events_scop(&env);
		glUseProgram(env.shader.program);
		compute_mvp_matrix(&env);
		update_shader_uniforms(&env);
		glBindTexture(GL_TEXTURE_2D, env.buffer.texture);
		glBindVertexArray(env.buffer.vao);
		glDrawElements(GL_TRIANGLES, env.model.num_indices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glfwSwapBuffers(env.ptr);
	}
	clean_glfw(&env);
	return 0;
}
