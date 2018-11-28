#ifndef SCOP_H
#define SCOP_H


#define BUFFER_SIZE 2500

#include <GLFW/glfw3.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include <stdio.h>

typedef struct t_env_st 
{
    GLuint prgm;
    GLuint vert;
    GLuint frag;
    GLuint array;
    GLuint buf;
    GLFWwindow* win;
}           t_env;

t_env init_scop(void);
int create_prog(t_env *env);

size_t	ft_strlen(const char *str);
int		ft_strdel(char **as);
char	*ft_strnew(size_t size);
char	*ft_strjoin(char const *s1, char const *s2);


#endif
