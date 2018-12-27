#include "libmat4.h"

t_mat4	mat4_copy(t_mat4 *a, t_mat4 b)
{
	int i;

	i = -1;
	while (++i < 16)
		a->m[i] = b.m[i];
	return (*a);
}
