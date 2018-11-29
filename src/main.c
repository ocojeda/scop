#include "scop.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, t_env *env)
{
	if (key == 32)
	{
	    if (env->flag_texture == 0)
            env->flag_texture = 1;
        else    
            env->flag_texture = 0;
	}
}

int main(void)
{

	t_env env;
	env = init_scop();
	if (create_prog(&env) == 0)
	{
		printf("fail to load the shaders\n");
		return (0);
	}

	unsigned int texture;
	glGenTextures(1, &texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load("Shaders/Chaton.jpg", &width, &height, &nrChannels, 0); 
	
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	unsigned int p_text = glGetUniformLocation(env.prgm, "text_flag");
	env.flag_texture = 0;
	glUniform1f(p_text, env.flag_texture);

	while(!glfwWindowShouldClose(env.win))
	{		
		events_scop(&env);
		//glfwSetKeyCallback(env.win, key_callback);
		// glfwSetKeyCallback(env.win, key_callback);

		glUniform1f(p_text, env.flag_texture);
 		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, texture);
		// render the triangle
		glUseProgram(env.prgm);
		glBindVertexArray(env.array);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(env.win);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &env.array);
	glDeleteBuffers(1, &env.buf);
	stbi_image_free(data);
	glfwTerminate();
	return 0;
}
