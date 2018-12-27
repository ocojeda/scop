#include "scop.h"

void    events_scop(t_env *env)
{
	if (glfwGetKey(env->win.ptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(env->win.ptr, GL_TRUE);
	rotate(&env->model.rotation, vec3(0, 0.1, 0));
	model_move_inertia(env, 0.9);
	camera_move_inertia(env, 0.93, 0);
	camera_look_at_target(env);
	env->sim.model = mat4_mul(env->model.translation, env->model.rotation);

	if (glfwGetKey(env->win.ptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    	glfwSetWindowShouldClose(env->win.ptr, GL_TRUE);
    if (glfwGetKey(env->win.ptr, 32) == GLFW_PRESS)
	{
        if (glfwGetKey(env->win.ptr, 32) == GLFW_RELEASE)
        {
			env->flags.texture = (env->flags.texture == 0 ? 1 : 0);
        }
    }
};