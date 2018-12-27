#include "libmat4.h"

t_mat4	mat4_transpose(t_mat4 m)
{
	int		h;
	int		w;
	t_mat4	t;

	h = -1;
	while (++h < 4)
	{
		w = -1;
		while (++w < 4)
			t.m[w * 4 + h] = m.m[h * 4 + w];
	}
	m = mat4_copy(&m, t);
	return (m);
}
