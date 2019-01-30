/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_funcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 09:22:26 by ocojeda-          #+#    #+#             */
/*   Updated: 2019/01/30 18:07:06 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"


void	set_projection_matrix(t_env *env, float fov)
{
	float	s;
	float	far;
	float	near;

	far = CAMERA_FAR;
	near = CAMERA_NEAR;
	s = 1 / (tan(fov * 0.5 * M_PI / 180.0));
	mat4_set(&env->model.projection, 0);
	env->model.projection.m[0] = s / env->ratio;
	env->model.projection.m[5] = s;
	env->model.projection.m[10] = -(far + near) / (far - near);
	env->model.projection.m[11] = -1;
	env->model.projection.m[14] = -2 * far * near / (far - near);
}

void	init_matrices(t_env *env)
{
	mat4_set(&env->model.model, IDENTITY);
	mat4_set(&env->model.view, IDENTITY);
	set_projection_matrix(env, env->cam.fov);
	mat4_set(&env->model.rotation, IDENTITY);
	mat4_set(&env->model.translation, IDENTITY);
	vec3_set(&env->model.center_axis, 0);
}

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
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void	init_cam(t_env *env)
{
	env->cam.pos = vec3(0, 0, 3);
	env->cam.target = vec3(0, 0, 0);
	env->cam.dir = vec3_normalize(vec3_sub(env->cam.pos, env->cam.target));
	env->cam.right = vec3_normalize(vec3_cross(vec3(0,1,0), env->cam.dir));
	env->cam.up = vec3_cross(env->cam.dir, env->cam.right);
	env->cam.front = vec3_cross(env->cam.up, env->cam.right);
}

void	init(t_env *env, int argc, char **argv)
{
	if(argc == 2)
	{
		env->model.filename = ft_strjoin("../resources/", argv[1]);
		env->cam.fov = FOV;
		env->width = WIN_WIDTH;
		env->height = WIN_HEIGHT;
		env->ratio = env->width / (float)env->height;
		init_glfw_env();
		init_glfw_win(env);
		init_cam(env);
		init_matrices(env);
		env->flags.texture = 0;
	}
}