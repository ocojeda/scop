#include "libmat4.h"

float	vec3_magnitude(t_vec3 v)
{
	return (sqrt(v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2]));
}
