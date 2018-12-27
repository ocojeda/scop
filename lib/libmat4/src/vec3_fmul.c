#include "libmat4.h"

t_vec3	vec3_fmul(t_vec3 v, float f)
{
	int	i;

	i = -1;
	while (++i < 3)
		v.v[i] *= f;
	return (v);
}
