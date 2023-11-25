#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

GLboolean ortho = true; // try toggling

// Rotation angles
float rotateX = 0.0f;
float rotateY = 0.0f;
// Camera position
float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 15.0f;

GLfloat SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 1000;

void drawAxes()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3d(-1000, 0, 0);
    glVertex3d(1000, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3d(0, -1000, 0);
    glVertex3d(0, 1000, 0);

    glColor3f(0, 0, 1);
    glVertex3d(0, 0, -1000);
    glVertex3d(0, 0, 1000);

    glEnd();
}

void setProjection()
{
    ortho = !ortho;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    (!ortho) ? gluPerspective(45.0f, 1.0f, 0.1f, 100.0f) : glOrtho(-25, 25, -25, 25, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

void myKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 32:
        setProjection();
        rotateX = 0;
        rotateY = 0;
        cameraZ = 15;
        glutSetWindowTitle(!ortho?"Perspective":"Orthogonal");
        break;
    case 'w':
        rotateX += 5.0f; // Rotate object in X dirn
        break;
    case 'a':
        rotateY += 5.0f; // Rotate object in Y dirn
        break;
    case 's':
        rotateX -= 5.0f; // Rotate object in X dirn
        break;
    case 'd':
        rotateY -= 5.0f; // Rotate object in Y dirn
        break;
    case 'f':
        cameraZ -= 5.0f; // Move camera forward
        break;
    case 'b':
        cameraZ += 5.0f; // Move camera backward
        break;
    case 27: // ESC key to exit
        exit(0);
    }
    glutPostRedisplay();
}

void myReshape(int width, int height)
{
    if (height == 0)
        height = 1;

    float ratio = width * 1.0 / height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    (!ortho) ? gluPerspective(45.0f, ratio, 0.1f, 100.0f) : glOrtho(-0.1 * width / 5, 0.1 * width / 5, -0.1 * height / 5, 0.1 * height / 5, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void myInit()
{
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    (!ortho) ? gluPerspective(45.0f, 1.0f, 0.1f, 100.0f) : glOrtho(-25, 25, -25, 25, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(15, 15, 15, 0, 0, 0, 0, 1, 0);
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f); // Roate along X
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f); // Rotate along Y
    drawAxes();

    glutWireTeapot(7);
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);

    glutCreateWindow("3d basics");
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    glutKeyboardFunc(myKeyboard);

    myInit();
    glutMainLoop();
    return 1;
}