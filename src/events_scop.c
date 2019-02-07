/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_scop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 10:42:52 by ocojeda-          #+#    #+#             */
/*   Updated: 2019/02/07 15:40:19 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		key_code_pressed(t_env *env, int key)
{
	if (glfwGetKey(env->ptr, key) == GLFW_PRESS)
		return (key);
	return (0);
}

void	translation_handler(t_env *env)
{
	if (key_code_pressed(env, GLFW_KEY_6))
		translate(&env->model.translation, vec3(0, 0, 0.2));
	if (key_code_pressed(env, GLFW_KEY_5))
		translate(&env->model.translation, vec3(0, 0, -0.2));
	if (key_code_pressed(env, GLFW_KEY_4))
		translate(&env->model.translation, vec3(0, 0.01, 0));
	if (key_code_pressed(env, GLFW_KEY_3))
		translate(&env->model.translation, vec3(0, -0.01, 0));
	if (key_code_pressed(env, GLFW_KEY_2))
		translate(&env->model.translation, vec3(0.01, 0, 0));
	if (key_code_pressed(env, GLFW_KEY_1))
		translate(&env->model.translation, vec3(-0.01, 0, 0));
	if (key_code_pressed(env, GLFW_KEY_UP))
		rotate(&env->model.rotation, vec3(0.5, 0, 0));
	if (key_code_pressed(env, GLFW_KEY_DOWN))
		rotate(&env->model.rotation, vec3(-0.5, 0, 0));
	if (key_code_pressed(env, GLFW_KEY_LEFT))
		rotate(&env->model.rotation, vec3(0, 0, 0.5));
	if (key_code_pressed(env, GLFW_KEY_RIGHT))
		rotate(&env->model.rotation, vec3(0, 0, -0.5));
	if (glfwGetKey(env->ptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(env->ptr, GL_TRUE);
}

void	events_scop(t_env *env)
{
	translation_handler(env);
	rotate(&env->model.rotation, vec3(0, 0.5, 0));
	camera_look_at_target(env);
	env->model.model = mat4_mul(env->model.translation, env->model.rotation);
	glUniform1f(env->shader.magnitude, env->model.depth);
	if (glfwGetKey(env->ptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(env->ptr, GL_TRUE);
	if (glfwGetKey(env->ptr, 32) == GLFW_PRESS)
	{
		if (glfwGetKey(env->ptr, 32) == GLFW_RELEASE)
			env->flag_texture = (env->flag_texture == 0 ? 1 : 0);
	}
}
