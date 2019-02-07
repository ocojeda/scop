/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:29:55 by ocojeda-          #+#    #+#             */
/*   Updated: 2019/02/07 16:27:29 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	set_projection_matrix(t_env *env, float fov)
{
	float	s;
	float	far;
	float	near;

	far = 10000;
	near = 0.001;
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
