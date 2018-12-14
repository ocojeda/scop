#include "scop.h"

t_mat4 init_matrix(float x, float y, float z, float m)
{
	t_mat4 ini;

	ini.m[0] = x;
	ini.m[1] = 0;
	ini.m[2] = 0;
	ini.m[3] = 0;
	ini.m[4] = 0;
	ini.m[5] = y;
	ini.m[6] = 0;
	ini.m[7] = 0;
	ini.m[8] = 0;
	ini.m[9] = 0;
	ini.m[10] = z;
	ini.m[11] = 0;
	ini.m[12] = 0;
	ini.m[13] = 0;
	ini.m[14] = 0;
	ini.m[15] = m;
	return (ini);
}

void		round_mat(t_mat4 *matrix)
{
	int		i;

	i = -1;
	while (++i <= 15)
	{
		matrix->m[i] = ((float)((int)(matrix->m[i] * 100)) / 100);
	}
}

t_mat4		rotx_mat(float theta)
{
	t_mat4		matrix;

	matrix = init_matrix(0,0,0, 1);
	matrix.m[0] = 1;
	matrix.m[5] = cos(theta * DEG2RAD);
	matrix.m[6] = -sin(theta * DEG2RAD);
	matrix.m[9] = sin(theta * DEG2RAD);
	matrix.m[10] = cos(theta * DEG2RAD);
	round_mat(&matrix);
	return (matrix);
}

t_mat4		roty_mat(float theta)
{
	t_mat4		matrix;

	matrix = init_matrix(0,0,0, 1);
	matrix.m[0] = cos(theta * DEG2RAD);
	matrix.m[2] = sin(theta * DEG2RAD);
	matrix.m[5] = 1;
	matrix.m[8] = -sin(theta * DEG2RAD);
	matrix.m[10] = cos(theta * DEG2RAD);
	round_mat(&matrix);

	return (matrix);
}

t_mat4 rotz_mat(float theta)
{
	t_mat4		matrix;

	matrix = init_matrix(0,0,0, 1);
	matrix.m[0] = cos(theta * DEG2RAD);
	matrix.m[1] = -sin(theta * DEG2RAD);
	matrix.m[4] = sin(theta * DEG2RAD);
	matrix.m[5] = cos(theta * DEG2RAD);
	matrix.m[10] = 1;
	round_mat(&matrix);

	return (matrix);
}

static void	prod_mat_p2(t_mat4 *matrix, t_mat4 a, t_mat4 b)
{
	(*matrix).m[10] = a.m[8] * b.m[2] + a.m[9] * b.m[6]
			+ a.m[10] * b.m[10] + a.m[11] * b.m[14];
	(*matrix).m[11] = a.m[8] * b.m[3] + a.m[9] * b.m[7]
			+ a.m[10] * b.m[11] + a.m[11] * b.m[15];
	(*matrix).m[12] = a.m[12] * b.m[0] + a.m[13] * b.m[4]
			+ a.m[14] * b.m[8] + a.m[15] * b.m[12];
	(*matrix).m[13] = a.m[12] * b.m[1] + a.m[13] * b.m[5]
			+ a.m[14] * b.m[9] + a.m[15] * b.m[13];
	(*matrix).m[14] = a.m[12] * b.m[2] + a.m[13] * b.m[6]
			+ a.m[14] * b.m[10] + a.m[15] * b.m[14];
	(*matrix).m[15] = a.m[12] * b.m[3] + a.m[13] * b.m[7]
			+ a.m[14] * b.m[11] + a.m[15] * b.m[15];
}

t_mat4		prod_mat(t_mat4 a, t_mat4 b)
{
	t_mat4		matrix;

	matrix.m[0] = a.m[0] * b.m[0] + a.m[1] * b.m[4]
		+ a.m[2] * b.m[8] + a.m[3] * b.m[12];
	matrix.m[1] = a.m[0] * b.m[1] + a.m[1] * b.m[5]
		+ a.m[2] * b.m[9] + a.m[3] * b.m[13];
	matrix.m[2] = a.m[0] * b.m[2] + a.m[1] * b.m[6]
		+ a.m[2] * b.m[10] + a.m[3] * b.m[14];
	matrix.m[3] = a.m[0] * b.m[3] + a.m[1] * b.m[7]
		+ a.m[2] * b.m[11] + a.m[3] * b.m[15];
	matrix.m[4] = a.m[4] * b.m[0] + a.m[5] * b.m[4]
		+ a.m[6] * b.m[8] + a.m[7] * b.m[12];
	matrix.m[5] = a.m[4] * b.m[1] + a.m[5] * b.m[5]
		+ a.m[6] * b.m[9] + a.m[7] * b.m[13];
	matrix.m[6] = a.m[4] * b.m[2] + a.m[5] * b.m[6]
		+ a.m[6] * b.m[10] + a.m[7] * b.m[14];
	matrix.m[7] = a.m[4] * b.m[3] + a.m[5] * b.m[7]
		+ a.m[6] * b.m[11] + a.m[7] * b.m[15];
	matrix.m[8] = a.m[8] * b.m[0] + a.m[9] * b.m[4]
		+ a.m[10] * b.m[8] + a.m[11] * b.m[12];
	matrix.m[9] = a.m[8] * b.m[1] + a.m[9] * b.m[5]
		+ a.m[10] * b.m[9] + a.m[11] * b.m[13];
	prod_mat_p2(&matrix, a, b);
	return (matrix);
}

t_vec3 new_vec(float x, float y, float z)
{
    t_vec3 new;
    new.v[0] = x;
    new.v[1] = y;
    new.v[2] = z;

    return (new);
}

t_mat4		transl_mat(float x, float y, float z)
{
	t_mat4		matrix;

	matrix = init_matrix(1,1,1,1);
	matrix.m[0] = 1;
	matrix.m[3] = x;
	matrix.m[5] = 1;
	matrix.m[7] = y;
	matrix.m[10] = 1;
	matrix.m[11] = z;
	return (matrix);
}