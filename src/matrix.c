/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 09:22:11 by ocojeda-          #+#    #+#             */
/*   Updated: 2019/02/07 15:30:43 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	translate(t_mat4 *m, t_vec3 v)
{
	m->m[3] += v.v[0];
	m->m[7] += v.v[1];
	m->m[11] += v.v[2];
}

void	rotate(t_mat4 *m, t_vec3 v)
{
	if (v.v[0] != 0.0)
		*m = mat4_rotate_axis(*m, 0, v.v[0]);
	if (v.v[1] != 0.0)
		*m = mat4_rotate_axis(*m, 1, v.v[1]);
	if (v.v[2] != 0.0)
		*m = mat4_rotate_axis(*m, 2, v.v[2]);
}

t_mat4	init_matrix(float x, float y, float z, float m)
{
	t_mat4 ini;

	ini.m[0] = x;
	ini.m[1] = 0;
	ini.m[2] = 0;
	ini.m[3] = 0;
	ini.m[4] = 0;
	ini.m[5] = y;
	ini.m[6] = 0;
	ini.m[7] = 0;
	ini.m[8] = 0;
	ini.m[9] = 0;
	ini.m[10] = z;
	ini.m[11] = 0;
	ini.m[12] = 0;
	ini.m[13] = 0;
	ini.m[14] = 0;
	ini.m[15] = m;
	return (ini);
}
