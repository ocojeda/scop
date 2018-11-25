#include "../include/scop.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

    // glVertex3d(-1,-1,1);
    // glVertex3d(-1,-1,-1);
    // glVertex3d(1,-1,-1);

    float vertices[] = {
        // positions         // colors
         5.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
    };
    float pos[] = {
         0.5f, -0.5f, 0.0f};

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
        return NULL;
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
    
    return src;
}


// angle of rotation for the camera direction
float angle = 0.0f;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f, z=5.0f;
// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void computeDir(float deltaAngle) {

	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}


void renderScene(context env) {
    

	if (deltaMove)
		computePos(deltaMove);
	if (deltaAngle)
		computeDir(deltaAngle);

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(	x, 1.0f, z,
				x+lx, 1.0f,  z+lz,
				0.0f, 1.0f,  0.0f);
                
    glBegin(GL_TRIANGLES);
    glColor3ub(255,0,0); //face rouge
	vector_gl a = ini_vector_gl(-1, 1, -1);
	vector_gl b = ini_vector_gl(-1,1,1);
	vector_gl c = ini_vector_gl(-1,-1,1);
	triangle_gl tri = ini_triangle_gl(a,b,c);
	tringle_render(tri);
   

    glColor3ub(0,255,0); //face verte
    glVertex3d(1,-1,1);
    glColor3ub(255, 0 ,0);
    glVertex3d(1,-1,-1);
    glColor3ub(0,0,255);
    glVertex3d(1,1,-1);
    
    
    
   glColor4f(1.0, 1.0, 0.0, 1); //face bleue
    glVertex3d(-1,-1,1);
    glVertex3d(-1,-1,-1);
    glVertex3d(1,-1,-1);
    

 glEnd();
  glBegin(GL_TRIANGLES);
   glColor4f(1.0, 1.0, 0.5, 1);
   glVertex3d(-1,-1,1);
    glVertex3d(0.9, -0.9, 0.2);
    glVertex3d(0.0, 0.9, -0.2);
glEnd();

 glFlush();
	glutSwapBuffers();
}


void pressKey(int key, int xx, int yy) {
	switch (key) {
		case 27 : glutDestroyWindow(glutGetWindow()); break;
		case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
		case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
		case GLUT_KEY_UP : deltaMove = 0.5f; break;
		case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
		
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : deltaMove = 0;break;
	}
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
    src = LoadSource(filename);
    if(src == NULL)
    {
        /* theoriquement, la fonction LoadSource a deja affiche un message
           d'erreur, nous nous contenterons de supprimer notre shader
           et de retourner 0 */
        
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
        
        return 0;
    }
    
    return shader;
}

int init_glut(int argc, char **argv, context env)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(800,600);
	glutCreateWindow("Scop");
	// register callbacks
	glEnable(GL_DEPTH_TEST);
    env.prgm = glCreateProgram();
 
    env.fract = LoadShader(GL_FRAGMENT_SHADER, "Shaders/basique2D.frag");
	env.shader = LoadShader(GL_VERTEX_SHADER, "Shaders/basique2D.vert");


    glAttachShader(env.prgm, env.shader);
    glAttachShader(env.prgm, env.fract);
	
    
    glGenVertexArrays(1, &env.VAO);
    glGenBuffers(1, &env.VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(env.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, env.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindAttribLocation(env.prgm, 0, "pos");
    glBindAttribLocation(env.prgm, 1, "col");
    return (glutGetWindow());
}

int main(int argc, char **argv) {

	// init GLUT and create window

    context env;
	if(!init_glut(argc, argv, env))
		return -1;
    glLinkProgram(env.prgm);
	while(glutGetWindow())
	{
        glUseProgram(env.prgm);
        glutDisplayFunc(renderScene);
		glutReshapeFunc(changeSize);
		glutIdleFunc(renderScene);

		glutSpecialFunc(pressKey);

		// here are the new entries
		glutIgnoreKeyRepeat(1);
		glutSpecialUpFunc(releaseKey);

		// enter GLUT event processing cycle
		glutKeyboardFunc(pressKey);
		glutMainLoop();
        glUseProgram(0);
	}

    glDeleteShader(env.shader);
    glDeleteProgram(env.prgm);
	return 1;
}
