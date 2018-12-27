#include "libmat4.h"

void	mat4_set(t_mat4 *m, float f)
{
	int		i;

	i = -1;
	while (++i < 16)
	{
		if (f == IDENTITY)
			m->m[i] = (i % 5 == 0 ? 1 : 0);
		else
			m->m[i] = f;
	}
}
