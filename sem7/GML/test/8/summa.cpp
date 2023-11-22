#include <GL/glut.h>

void myInit()
{
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0f, 1.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
}

void drawShape(GLenum mode, const GLfloat *vertices, int numVertices)
{
    glBegin(mode);

    for (int i = 0; i < numVertices * 3; i += 3)
        glVertex3fv(&vertices[i]);

    glEnd();
}

void drawAxes()
{
    glBegin(GL_LINES);

    // X-axis (Red)
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    // Y-axis (Green)
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    // Z-axis (Blue)
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawAxes();
    // Draw 3D Shapes
    glColor3f(1, 0, 0);
    GLfloat cubeVertices[] = {
        -1, -1, -1,
        1, -1, -1,
        1, 1, -1,
        -1, 1, -1,
        -1, -1, 1,
        1, -1, 1,
        1, 1, 1,
        -1, 1, 1};
    drawShape(GL_QUADS, cubeVertices, 8);

    glColor3f(0, 1, 0);
    GLfloat pyramidVertices[] = {
        0, 1, 0,
        -1, -1, 1,
        1, -1, 1,
        1, -1, -1,
        -1, -1, -1};
    // drawShape(GL_TRIANGLE_FAN, pyramidVertices, 5);

    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("3D Shapes");
    glutDisplayFunc(myDisplay);

    myInit();
    glutMainLoop();
    return 0;
}
