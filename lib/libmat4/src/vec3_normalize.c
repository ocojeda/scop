#include "libmat4.h"

t_vec3	vec3_normalize(t_vec3 v)
{
	float	magnitude;

	magnitude = vec3_magnitude(v);
	v.v[0] /= magnitude;
	v.v[1] /= magnitude;
	v.v[2] /= magnitude;
	return (v);
}
