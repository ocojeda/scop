#ifndef SCOP_H
#define SCOP_H
/*
#include <GL/gl.h>
#include <GL/glut.h>
*/
#define BUFFER_SIZE 2500
#define PI 3.1415926535898

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <GLFW/glfw3.h>
#else
#include <GL/glut.h>
#include "GL/freeglut.h"
#endif
#include <math.h>


#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct vector_gl 
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
}           vector_gl;

typedef struct triangle_gl
{
    vector_gl a;
    vector_gl b;
    vector_gl c;
}           triangle_gl;

typedef struct context_st 
{
    GLuint prgm;
    GLuint shader;
    GLuint fract;
    GLuint array;
    GLuint VBO;
    GLuint VAO;

} context;

vector_gl ini_vector_gl(GLfloat x, GLfloat y, GLfloat z);
triangle_gl ini_triangle_gl(vector_gl a, vector_gl b, vector_gl c);
void tringle_render(triangle_gl tri);
#endif
