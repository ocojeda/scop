#include "scop.h"


void	set_projection_matrix(t_env *env, float fov)
{
	float	s;
	float	far;
	float	near;

	far = CAMERA_FAR;
	near = CAMERA_NEAR;
	s = 1 / (tan(fov * 0.5 * M_PI / 180.0));
	mat4_set(&env->sim.projection, 0);
	env->sim.projection.m[0] = s / env->win.ratio;
	env->sim.projection.m[5] = s;
	env->sim.projection.m[10] = -(far + near) / (far - near);
	env->sim.projection.m[11] = -1;
	env->sim.projection.m[14] = -2 * far * near / (far - near);
}

void	init_matrices(t_env *env)
{
	mat4_set(&env->sim.model, IDENTITY);
	mat4_set(&env->sim.view, IDENTITY);
	set_projection_matrix(env, env->cam.fov);
	mat4_set(&env->model.rotation, IDENTITY);
	mat4_set(&env->model.translation, IDENTITY);
	vec3_set(&env->model.inertia, 0);
	vec3_set(&env->model.center_axis, 0);
}

void	init_glfw_win(t_env *env)
{
	int width;
	int height;

	env->win.ptr = glfwCreateWindow(env->win.w, env->win.h, "scop", NULL, NULL);
	glfwMakeContextCurrent(env->win.ptr);
	glfwGetFramebufferSize(env->win.ptr, &width, &height);
	glViewport(0, 0, width, height);
	glfwSetInputMode(env->win.ptr, GLFW_STICKY_KEYS, 1);
}

void	init_glfw_env(void)
{
	if (!glfwInit())
		ft_putstr("ERROR: glfw initialization failed.");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, ft_atoi(&OPENGL_VERSION[0]));
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ft_atoi(&OPENGL_VERSION[2]));
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void	init_cam(t_env *env)
{
	t_vec3	up;

	up = vec3(0, 1, 0);
	env->cam.pos = vec3(0, 0, 3);
	env->cam.target = vec3(0, 0, 0);
	env->cam.dir = vec3_normalize(vec3_sub(env->cam.pos, env->cam.target));
	env->cam.right = vec3_normalize(vec3_cross(up, env->cam.dir));
	env->cam.up = vec3_cross(env->cam.dir, env->cam.right);
	env->cam.front = vec3_cross(env->cam.up, env->cam.right);
	vec3_set(&env->cam.inertia, 0);
}

void	init(t_env *env, int argc, char **argv)
{
	int	i;

	i = -1;
	env->model.filename = "../resources/teapot.obj";
	env->cam.fov = FOV;
	env->win.w = WIN_WIDTH;
	env->win.h = WIN_HEIGHT;
	env->win.ratio = env->win.w / (float)env->win.h;
	init_glfw_env();
	init_glfw_win(env);
	init_cam(env);
	init_matrices(env);
	env->flags.texture = 0;
}