#include "scop.h"

void	compute_mvp_matrix(t_env *env)
{
	env->sim.mvp = mat4_mul(mat4_transpose(env->sim.model),
		mat4_mul(env->sim.view, env->sim.projection));
}



void	read_header(char *filename, t_texture *texture)
{
	FILE	*file;

	if ((file = fopen(filename, "r")) == NULL)
		error("bmp file opening (fopen) failed.");
	fseek(file, 18, SEEK_SET);
	fread(&texture->w, 4, 1, file);
	fread(&texture->h, 4, 1, file);
	fseek(file, 2, SEEK_CUR);
	fread(&texture->bpp, 2, 1, file);
	fclose(file);
	texture->opp = texture->bpp / 8;
	texture->sl = texture->w * texture->opp;
	texture->w < 0 ? texture->w = -texture->w : 0;
	texture->h < 0 ? texture->h = -texture->h : 0;
	texture->size = texture->sl * texture->h;
}

void	get_image(t_texture *texture, char *buffer, int i)
{
	int	h;
	int	j;
	int	size;

	h = 0;
	size = texture->size * 2;
	texture->img = (unsigned char*)malloc(sizeof(unsigned char) * size);
	while (i >= 0)
	{
		i -= texture->sl;
		j = 0;
		while (j < texture->sl)
		{
			texture->img[h + j] = (unsigned char)buffer[i + j + 2];
			texture->img[h + j + 1] = (unsigned char)buffer[i + j + 1];
			texture->img[h + j + 2] = (unsigned char)buffer[i + j];
			j += 3;
		}
		h += texture->sl;
	}
}

void	load_bmp(t_env *env, char *filename)
{
	int		fd;
	int		i;
	char	*buffer;

	read_header(filename, &env->model.texture);
	buffer = (char*)malloc(sizeof(char) * env->model.texture.size + 1);
	if ((fd = open(filename, O_RDWR)) == -1)
		error("bmp file opening failed.");
	lseek(fd, 54, SEEK_SET);
	i = read(fd, buffer, env->model.texture.size);
	get_image(&env->model.texture, buffer, i);
	ft_strdel((char**)&buffer);
	close(fd);
}

void			update_shader_uniforms(t_env *env)
{
	glUniformMatrix4fv(env->shader.mvploc, 1, GL_FALSE, env->sim.mvp.m);
	glUniform1i(env->shader.tmdloc, env->flags.texture);
}

const GLchar	*get_shader_source(char *filename)
{
	int		fd;
	int		ret;
	char	buffer[BUFFER_SIZE];
	char	*source;
	char	*del;

	source = ft_strnew(BUFFER_SIZE);
	if ((fd = open(filename, O_RDONLY)) == -1)
		error("shader source file opening failed.");
	while ((ret = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[ret] = '\0';
		del = source;
		source = ft_strjoin(source, buffer);
		ft_strdel(&del);
	}
	close(fd);
	return (source);
}

GLuint			create_shader(char *filename, int shader_type)
{
	GLint			success;
	GLuint			shader;
	const GLchar	*shader_source;

	shader_source = get_shader_source(filename);
	shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);
	free((void*)shader_source);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
		error("shader compilation failed.");
	return (shader);
}

GLuint			create_shader_program(GLuint shader_vert, GLuint shader_frag)
{
	GLint	success;
	GLuint	shader_program;

	shader_program = glCreateProgram();
	glAttachShader(shader_program, shader_vert);
	glAttachShader(shader_program, shader_frag);
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
		error("shader program compilation failed.");
	glDeleteShader(shader_vert);
	glDeleteShader(shader_frag);
	return (shader_program);
}

void			build_shader_program(t_env *env)
{
	GLuint	shader_vert;
	GLuint	shader_frag;

	shader_vert = create_shader("../Shaders/basique2D.vert", GL_VERTEX_SHADER);
	shader_frag = create_shader("../Shaders/basique2D.frag", GL_FRAGMENT_SHADER);
	env->shader.program = create_shader_program(shader_vert, shader_frag);
	env->shader.mvploc = glGetUniformLocation(env->shader.program, "mvp");
	env->shader.smdloc = glGetUniformLocation(env->shader.program, "smod");
	env->shader.cmdloc = glGetUniformLocation(env->shader.program, "cmod");
	env->shader.tmdloc = glGetUniformLocation(env->shader.program, "tmod");
	env->shader.gmdloc = glGetUniformLocation(env->shader.program, "gmod");
	env->shader.mmdloc = glGetUniformLocation(env->shader.program, "mmod");
	env->shader.texloc = glGetUniformLocation(env->shader.program, "ltexture");
}

void	create_texture(t_env *env)
{
	glGenTextures(1, &env->buffer.texture);
	glBindTexture(GL_TEXTURE_2D, env->buffer.texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, env->model.texture.w,
	env->model.texture.h, 0, GL_RGB, GL_UNSIGNED_BYTE, env->model.texture.img);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void	create_buffers(t_env *env, int mode)
{
	glGenBuffers(1, &env->buffer.vbo);
	glGenBuffers(1, &env->buffer.ebo);
	glGenVertexArrays(1, &env->buffer.vao);
	glBindVertexArray(env->buffer.vao);
	glBindBuffer(GL_ARRAY_BUFFER, env->buffer.vbo);
	glBufferData(GL_ARRAY_BUFFER, env->model.size_vertices,
		env->model.vertices, mode);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->buffer.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, env->model.size_indices,
		env->model.indices, mode);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	create_texture(env);
}

void	clean_glfw(t_env *env)
{
	glDeleteVertexArrays(1, &env->buffer.vao);
	glDeleteBuffers(1, &env->buffer.vbo);
	glDeleteBuffers(1, &env->buffer.ebo);
	glfwTerminate();
}

void	model_move_inertia(t_env *env, float inertia)
{
	env->model.inertia = vec3_fmul(env->model.inertia, inertia);
	translate(&env->model.translation, env->model.inertia);
}

void	model_move_demo(t_env *env)
{
	
}

int main(int argc, char **argv)
{
	t_env env;
	init(&env, argc, argv);
	load_obj(&env, env.model.filename);
	load_bmp(&env, "../resources/chaton.bmp");
	build_shader_program(&env);
	create_buffers(&env, GL_DYNAMIC_DRAW);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(env.win.ptr))
	{
		glfwPollEvents();
		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		events_scop(&env);
		
		glUseProgram(env.shader.program);
		compute_mvp_matrix(&env);
		update_shader_uniforms(&env);
		glBindTexture(GL_TEXTURE_2D, env.buffer.texture);
		glBindVertexArray(env.buffer.vao);
		glDrawElements(GL_TRIANGLES, env.model.num_indices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glfwSwapBuffers(env.win.ptr);
	}
	clean_glfw(&env);

	return 0;
}
