#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

const int SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 1000;

vector<double> points = {-300, -300, -280, 278, 301, 265};
GLfloat xmin = -100, xmax = 150, ymin = -75, ymax = 200;

void myInit()
{
    glClearColor(0, 0, 0, 0);
    glPointSize(10);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2);
}

void drawPixel(GLfloat x, GLfloat y)
{
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}

void drawFig(GLenum mode, vector<double> xy)
{
    glBegin(mode);

    for (int i = 0; i < xy.size(); i += 2)
    {
        glVertex2f(xy[i], xy[i + 1]);
    }

    glEnd();
    glFlush();
}

void wov(double *x, double *y)
{
    // scaling factors
    double sx = (xmax - xmin) / (SCREEN_WIDTH / 2 - (-SCREEN_WIDTH / 2));
    double sy = (ymax - ymin) / (SCREEN_HEIGHT / 2 - (-SCREEN_HEIGHT / 2));

    // viewpoint coordinates
    *x = xmin + ((*x - (-SCREEN_WIDTH / 2)) * sx);
    *y = ymin + ((*y - (-SCREEN_HEIGHT / 2)) * sy);
}

void myDisplay1()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawFig(GL_TRIANGLES, points);
    glutSwapBuffers();
}

void myDisplay2()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawFig(GL_LINE_LOOP, {xmin, ymin, xmax, ymin, xmax, ymax, xmin, ymax});

    for (int i = 0; i < points.size(); i += 2)
        wov(&points[i], &points[i + 1]);

    drawFig(GL_TRIANGLES, points);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    glutCreateWindow("window");
    glutDisplayFunc(myDisplay1);
    myInit();

    glutCreateWindow("Viewport");
    glutDisplayFunc(myDisplay2);
    myInit();

    glutMainLoop();

    return 1;
}