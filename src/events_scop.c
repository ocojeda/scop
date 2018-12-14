#include "scop.h"

void    events_scop(t_env *env)
{
	if (glfwGetKey(env->win.ptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    	glfwSetWindowShouldClose(env->win.ptr, GL_TRUE);
    if (glfwGetKey(env->win.ptr, 32) == GLFW_PRESS)
	{
        glfwSetInputMode(env->win.ptr, GLFW_STICKY_KEYS, 1);
        if (glfwGetKey(env->win.ptr, 32) == GLFW_RELEASE)
        {
        if (env->flag_texture == 0)
            env->flag_texture = 1;
        else    
            env->flag_texture = 0;
        }
    }
};

void	key_action(t_env *env)
{
	if (env->mod.focus)
		camera_center(env);
	model_move_demo(env);
	model_move_inertia(env, 0.9);
	camera_move_inertia(env, 0.93, 0);
	camera_look_at_target(env);
}

void	key_handle(t_env *env)
{
	int	i;

	if (glfwGetKey(env->win.ptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(env->win.ptr, GL_TRUE);
	key_action(env);
}