#ifndef SCOP_H
#define SCOP_H

#define BUFFER_SIZE 2500
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define FOV 90
#define CAMERA_NEAR 0.001
#define CAMERA_FAR 100.0
# define OPENGL_VERSION "4.0"

#include <GLFW/glfw3.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>

#include "libmat4.h"
#include "libft.h"


#include <stdio.h>

typedef struct	s_texture
{
	unsigned char	*img;
	int				size;
	int				w;
	int				h;
	int				sl;
	short			bpp;
	short			opp;
}				t_texture;

typedef struct	s_buffer
{
	GLuint	vao;
	GLuint	vbo;
	GLuint	ebo;
	GLuint	texture;
}				t_buffer;

typedef struct	s_flags
{
	short	texture;
}				t_flags;

typedef struct	s_win
{
	GLFWwindow	*ptr;
	int			w;
	int			h;
	float		ratio;
}				t_win;

typedef struct	s_shader
{
	GLuint	program;
	GLint	mvploc;
	GLint	cmdloc;
	GLint	smdloc;
	GLint	tmdloc;
	GLint	gmdloc;
	GLint	mmdloc;
	GLint	texloc;
}				t_shader;

typedef struct	s_sim
{
	t_mat4	model;
	t_mat4	view;
	t_mat4	projection;
	t_mat4	mvp;
}				t_sim;

typedef struct s_cam
{
	t_vec3	pos;
	t_vec3	dir;
	t_vec3	target;
	t_vec3	up;
	t_vec3	right;
	t_vec3	front;
	
	float	fov;
}   t_cam;

typedef struct	s_model
{
	t_mat4			translation;
	t_mat4			rotation;
	GLfloat			*vertices;
	GLuint			*indices;
	unsigned int	size_indices;
	unsigned int	size_vertices;
	unsigned int	num_indices;
	t_vec3			center_axis;
	
	t_texture		texture;
	float			velocity;
	char			*filename;
}				t_model;

typedef struct t_env_st 
{
    t_win		win;
	t_sim		sim;
	t_cam		cam;
	t_flags		flags;
	t_buffer	buffer;
	t_shader	shader;
	t_model		model;

    int        flag_texture;
}           t_env;

void	init(t_env *env, int argc, char **argv);

void	camera_look_at_target(t_env *env);
void	camera_center(t_env *env);
void	translate(t_mat4 *m, t_vec3 v);
void	rotate(t_mat4 *m, t_vec3 v);


void    events_scop(t_env *env);

#endif
