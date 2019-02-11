/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 09:22:07 by ocojeda-          #+#    #+#             */
/*   Updated: 2019/02/09 19:44:36 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	compute_mvp_matrix(t_env *env)
{
	env->model.mvp = mat4_mul(mat4_transpose(env->model.model),
		mat4_mul(env->model.view, env->model.projection));
}

void	update_shader(t_env *env)
{
	glUniformMatrix4fv(env->shader.mvploc, 1, GL_FALSE, env->model.mvp.m);
	glUniform1i(env->shader.tmdloc, env->flag_texture);
}

void	clear_glfw(t_env *env)
{
	glDeleteVertexArrays(1, &env->buffer.vao);
	glDeleteBuffers(1, &env->buffer.vbo);
	glDeleteBuffers(1, &env->buffer.ebo);
	free(env->model.filename);
	glfwTerminate();
}

int		main(int argc, char **argv)
{
	t_env env;

	init(&env, argc, argv);
	if (env.ptr != NULL)
	{
		while (!glfwWindowShouldClose(env.ptr))
		{
			glfwPollEvents();
			glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			events_scop(&env);
			glUseProgram(env.shader.program);
			compute_mvp_matrix(&env);
			update_shader(&env);
			glBindTexture(GL_TEXTURE_2D, env.buffer.texture);
			glBindVertexArray(env.buffer.vao);
			glDrawElements(GL_TRIANGLES, env.model.num_indices, \
			GL_UNSIGNED_INT, 0);
			glfwSwapBuffers(env.ptr);
		}
		clear_glfw(&env);
	}
	return (0);
}
