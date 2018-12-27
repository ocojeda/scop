#include "libmat4.h"

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	int	i;

	i = -1;
	while (++i < 3)
		a.v[i] += b.v[i];
	return (a);
}
