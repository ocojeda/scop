/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 09:21:44 by ocojeda-          #+#    #+#             */
/*   Updated: 2019/02/11 12:23:06 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_cam(t_env *env)
{
	env->cam.pos = vec3(0, 0, env->model.depth * 2);
	env->cam.target = vec3(0, 0, 0);
	env->cam.dir = vec3_normalize(vec3_sub(env->cam.pos, env->cam.target));
	env->cam.right = vec3_normalize(vec3_cross(vec3(0, 1, 0), env->cam.dir));
	env->cam.up = vec3_cross(env->cam.dir, env->cam.right);
	env->cam.front = vec3_cross(env->cam.up, env->cam.right);
}

void	camera_look_at_target(t_env *env)
{
	t_vec3	tmp;
	t_mat4	view;

	tmp = env->cam.up;
	env->cam.front = vec3_normalize(vec3_sub(env->cam.pos, env->cam.target));
	env->cam.right = vec3_normalize(vec3_cross(env->cam.up, env->cam.front));
	tmp = vec3_cross(env->cam.front, env->cam.right);
	mat4_set(&view, IDENTITY);
	view.m[0] = env->cam.right.v[0];
	view.m[1] = tmp.v[0];
	view.m[2] = env->cam.front.v[0];
	view.m[4] = env->cam.right.v[1];
	view.m[5] = tmp.v[1];
	view.m[6] = env->cam.front.v[1];
	view.m[8] = env->cam.right.v[2];
	view.m[9] = tmp.v[2];
	view.m[10] = env->cam.front.v[2];
	view.m[12] = -vec3_dot(env->cam.right, env->cam.pos);
	view.m[13] = -vec3_dot(tmp, env->cam.pos);
	view.m[14] = -vec3_dot(env->cam.front, env->cam.pos);
	env->model.view = view;
}
