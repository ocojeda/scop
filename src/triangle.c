#include "../include/scop.h"

triangle_gl ini_triangle_gl( vector_gl a,  vector_gl b,  vector_gl c)
{
    triangle_gl tri;
    tri.a = a;
    tri.b = b;
    tri.c = c;
    return tri;
}

void tringle_render(triangle_gl tri)
{
    glVertex3d(tri.a.x, tri.a.y, tri.a.z);
    glVertex3d(tri.b.x, tri.b.y, tri.b.z);
    glVertex3d(tri.c.x, tri.c.y, tri.c.z);
}
