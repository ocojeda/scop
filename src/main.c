#include "scop.h"

int main(void)
{

	t_env env;
	env = init_scop();
	if (create_prog(&env) == 0)
	{
		printf("fail to load the shaders\n");
		return (0);
	}

	while(!glfwWindowShouldClose(env.win))
	{

		if (glfwGetKey(env.win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(env.win, GL_TRUE);
 		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render the triangle
		glUseProgram(env.prgm);
		glBindVertexArray(env.array);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(env.win);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &env.array);
	glDeleteBuffers(1, &env.buf);
	glfwTerminate();
	return 0;
}
