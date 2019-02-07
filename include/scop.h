/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 15:47:20 by ocojeda-          #+#    #+#             */
/*   Updated: 2019/02/07 17:17:11 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <GLFW/glfw3.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "libmat4.h"
# include "libft.h"
# include <stdio.h>
# define BUFFER_SIZE 2500
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define FOV 90

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
	GLuint			vao;
	GLuint			vbo;
	GLuint			ebo;
	GLuint			texture;
}				t_buffer;

typedef struct	s_shader
{
	GLuint			program;
	GLint			mvploc;
	GLint			tmdloc;
	GLint			gmdloc;
	GLint			texloc;
	GLint			magnitude;
}				t_shader;

typedef struct	s_cam
{
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			target;
	t_vec3			up;
	t_vec3			right;
	t_vec3			front;
	float			fov;
}				t_cam;

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
	float			depth;
	t_mat4			model;
	t_mat4			view;
	t_mat4			projection;
	t_mat4			mvp;
}				t_model;

typedef struct	s_env
{
	t_cam			cam;
	t_buffer		buffer;
	t_shader		shader;
	t_model			model;
	GLFWwindow		*ptr;
	int				width;
	int				height;
	float			ratio;
	int				flag_texture;
}				t_env;

void			init(t_env *env, int argc, char **argv);
void			load_bmp(t_env *env, char *filename);
void			create_texture(t_env *env);
void			load_obj(t_env *e, char *filename);
void			camera_look_at_target(t_env *env);
void			camera_center(t_env *env);
void			translate(t_mat4 *m, t_vec3 v);
void			rotate(t_mat4 *m, t_vec3 v);
void			init_matrices(t_env *env);
void			events_scop(t_env *env);
GLuint			create_shader(char *filename, int shader_type);
GLuint			create_shader_program(GLuint shader_vert, GLuint shader_frag);
void			init_cam(t_env *env);
void			init_glfw_win(t_env *env);
void			init_glfw_env(void);
GLfloat			*append_vertices(GLfloat *array, char *line, int *length);
GLuint			*append_indices(GLuint *array, char *line, int *length);

#endif
