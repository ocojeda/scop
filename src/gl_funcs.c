#include "scop.h"

//vertices has to be gone, jsut a test for the objects, it works =)

float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 1.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, -1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
};
unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

GLuint			create_shader_program(GLuint shader_vert, GLuint shader_frag)
{
	GLint	success;
	GLuint	shader_program;

	shader_program = glCreateProgram();
	glAttachShader(shader_program, shader_vert);
	glAttachShader(shader_program, shader_frag);
	glBindFragDataLocation(shader_program, 0, "outColor");
	glLinkProgram(shader_program);
	glUseProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
		return (-1);
	glDeleteShader(shader_vert);
	glDeleteShader(shader_frag);
	return (shader_program);
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
		return (0);
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
		return (0);
	return (shader);
}


char* LoadSource(const char *filename)
{
	char *src = NULL;   /* code source de notre shader */
	FILE *fp = NULL;    /* fichier */
	long size;          /* taille du fichier */
	long i;             /* compteur */


	/* on ouvre le fichier */
	fp = fopen(filename, "r");
	/* on verifie si l'ouverture a echoue */
	if(fp == NULL)
	{
		fprintf(stderr, "impossible d'ouvrir le fichier '%s'\n", filename);
		return (NULL);
	}

	/* on recupere la longueur du fichier */
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);

	/* on se replace au debut du fichier */
	rewind(fp);

	/* on alloue de la memoire pour y placer notre code source */
	src = malloc(size+1); /* +1 pour le caractere de fin de chaine '\0' */
	if(src == NULL)
	{
		fclose(fp);
		fprintf(stderr, "erreur d'allocation de memoire!\n");
		return NULL;
	}

	/* lecture du fichier */
	for(i=0; i<size; i++)
		src[i] = fgetc(fp);

	/* on place le dernier caractere a '\0' */
	src[size] = '\0';

	fclose(fp);

	return (src);
}

GLuint LoadShader(GLenum type, const char *filename)
{
	GLuint shader = 0;
	GLsizei logsize = 0;
	GLint compile_status = GL_TRUE;
	char *log = NULL;
	char *src = NULL;

	/* creation d'un shader de sommet */
	shader = glCreateShader(type);
	if(shader == 0)
	{
		fprintf(stderr, "impossible de creer le shader\n");
		return 0;
	}
	/* chargement du code source */
	if (!(src = LoadSource(filename)))
	{
        // fail to load the source
		glDeleteShader(shader);
		return 0;
	}

	/* assignation du code source */
	glShaderSource(shader, 1, (const GLchar**)&src, NULL);

	/* compilation du shader */
	glCompileShader(shader);

	/* liberation de la memoire du code source */
	free(src);
	src = NULL;

	/* verification du succes de la compilation */
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
	if(compile_status != GL_TRUE)
	{
		/* erreur a la compilation recuperation du log d'erreur */

		/* on recupere la taille du message d'erreur */
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);

		/* on alloue un espace memoire dans lequel OpenGL ecrira le message */
		log = malloc(logsize + 1);
		if(log == NULL)
		{
			fprintf(stderr, "impossible d'allouer de la memoire !\n");
			return 0;
		}
		/* initialisation du contenu */
		memset(log, '\0', logsize + 1);

		glGetShaderInfoLog(shader, logsize, &logsize, log);
		fprintf(stderr, "impossible de compiler le shader '%s' :\n%s",
				filename, log);

		/* ne pas oublier de liberer la memoire et notre shader */
		free(log);
		glDeleteShader(shader);

		return (0);
	}
	return (shader);
}

int create_prog(t_env *env)
{
    // load shader, coposed of a vertex for 
    // coordinates and a fragment for the color

    env->vert = LoadShader(GL_VERTEX_SHADER, "Shaders/basique2D.vert");
	env->frag = LoadShader(GL_FRAGMENT_SHADER, "Shaders/basique2D.frag");
    if(!(env->vert) || !(env->frag))
        return (0);
    
    // Create a program and link the shaders 
	env->prgm = glCreateProgram();
	glAttachShader(env->prgm, env->vert);
	glAttachShader(env->prgm, env->frag);
	glLinkProgram(env->prgm);

	// create an array of objects and bind them to the program
	glGenVertexArrays(1, &env->array);
	glGenBuffers(1, &env->buf);
    glGenBuffers(1, &env->EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(env->array);

	glBindBuffer(GL_ARRAY_BUFFER, env->buf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1); 

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    return (1);
};

t_env init_scop(void)
{
    t_env env;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    env.win = glfwCreateWindow(800, 600, "Scop", NULL, NULL); // Windowed
    glfwMakeContextCurrent(env.win);
    return (env);
};