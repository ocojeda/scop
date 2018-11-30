#include "scop.h"

void    events_scop(t_env *env)
{
	if (glfwGetKey(env->win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    	glfwSetWindowShouldClose(env->win, GL_TRUE);
    if (glfwGetKey(env->win, 32) == GLFW_PRESS)
	{
        glfwSetInputMode(env->win, GLFW_STICKY_KEYS, 1);
        if (glfwGetKey(env->win, 32) == GLFW_RELEASE)
        {
        if (env->flag_texture == 0)
            env->flag_texture = 1;
        else    
            env->flag_texture = 0;
        }
    }        
    // printf("%d\n", GLFW_PRESS);
};