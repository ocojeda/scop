#include "libmat4.h"

void	vec3_set(t_vec3 *v, float f)
{
	int		i;

	i = -1;
	while (++i < 3)
		v->v[i] = f;
}
