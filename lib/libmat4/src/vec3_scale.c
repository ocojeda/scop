#include "libmat4.h"

t_vec3	vec3_scale(t_vec3 v, float f)
{
	int	i;

	vec3_normalize(v);
	i = -1;
	while (++i < 3)
		v.v[i] *= f;
	return (v);
}
