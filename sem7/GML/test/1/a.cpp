#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

const int SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 1000;

void myInit()
{
    glClearColor(0, 0, 0, 0);
    glPointSize(10);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluOrtho2D(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2);
}

void drawShape(GLenum mode, vector<double> vertices)
{
    glBegin(mode);

    for (int i = 0; i < vertices.size(); i += 2)
        glVertex2d(vertices[i], vertices[i + 1]);

    glEnd();
    glFlush();
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawShape(GL_POINTS, {0, 0});

    glColor3f(0, 1, 0);
    drawShape(GL_LINES, {-100, -100, -50, -50});

    glColor3f(0, 0, 1);
    drawShape(GL_LINE_STRIP, {-100, -50, -200, -200, -200, -100});

    glColor3f(1, 1, 0);
    drawShape(GL_LINE_LOOP, {-100, -50, -150, -150, -200, -150});

    glColor3f(1, 0, 1);
    drawShape(GL_TRIANGLES, {-50, -50, 0, 50, 50, -50});

    glColor3f(0, 1, 1);
    drawShape(GL_TRIANGLE_STRIP, {0, 30, -20, -20, 20, -20, 0, -200});

    glColor3f(1, 0.5, 0);
    drawShape(GL_TRIANGLE_FAN, {0, 0, 50, 0, 0, 40, 0, -200, 50, -200});

    glColor3f(0.5, 0, 0.5);
    drawShape(GL_QUADS, {100, 100, 150, 100, 150, 150, 100, 150});

    glColor3f(0, 0.5, 0);
    drawShape(GL_POLYGON, {-100, -100, 0, -50, 100, -100, 50, -150, -50, -150});

    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    glutCreateWindow("1-a");
    glutDisplayFunc(myDisplay);

    myInit();
    glutMainLoop();
    return 1;
}