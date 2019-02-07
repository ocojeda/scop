/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_glfw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 13:07:44 by ocojeda-          #+#    #+#             */
/*   Updated: 2019/02/07 15:31:09 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_glfw_win(t_env *env)
{
	env->ptr = glfwCreateWindow(env->width, env->height, "scop", NULL, NULL);
	glfwMakeContextCurrent(env->ptr);
	glfwGetFramebufferSize(env->ptr, &env->width, &env->height);
	glViewport(0, 0, env->width, env->height);
	glfwSetInputMode(env->ptr, GLFW_STICKY_KEYS, 1);
}

void	init_glfw_env(void)
{
	if (!glfwInit())
		ft_error("GLFW error");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}
