#include "libmat4.h"

t_mat4	mat4_mul(t_mat4 a, t_mat4 b)
{
	int		h;
	int		w;
	int		z;
	t_mat4	m;

	h = -1;
	while (++h < 4)
	{
		w = -1;
		while (++w < 4)
		{
			z = -1;
			m.m[h * 4 + w] = 0;
			while (++z < 4)
				m.m[h * 4 + w] += a.m[h * 4 + z] * b.m[z * 4 + w];
		}
	}
	return (m);
}
