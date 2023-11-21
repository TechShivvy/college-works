#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>

#define vd vector<double>
#define vvd vector<vd>

using namespace std;

const int SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 1000;

vvd points = {{0, 100, 0},
              {0, 0, 100},
              {1, 1, 1}};
vvd points2 = {{100, 200, 100},
               {100, 100, 200},
               {1, 1, 1}};

float angle = 0.0f;

void drawAxes()
{
    glBegin(GL_LINES);
    glVertex2i(0, 2000);
    glVertex2i(0, -2000);
    glVertex2i(-2000, 0);
    glVertex2i(2000, 0);
    glEnd();
    ;
}

vvd multiply(vvd a, vvd b)
{
    vvd c(a.size(), vd(b[0].size(), 0));
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < b[0].size(); j++)
            for (int k = 0; k < b.size(); k++)
                c[i][j] += a[i][k] * b[k][j];
    return c;
}

vvd translate(vvd P, int tx, int ty)
{
    vvd T(3, vd(3, 0));
    for (int i = 0; i < 3; i++)
        T[i][i] = 1;
    T[0][2] = tx;
    T[1][2] = ty;
    return multiply(T, P);
}

vvd rotate(vvd P, int deg)
{
    vvd R(3, vd(3, 0));
    R[2][2] = 1;
    R[0][0] = R[1][1] = cos(M_PI * deg / 180);
    R[0][1] = R[1][0] = sin(M_PI * deg / 180);
    R[0][1] *= -1;
    return multiply(R, P);
}

vvd scale(vvd P, int sx, int sy)
{
    vvd S(3, vd(3, 0));
    S[2][2] = 1;
    S[0][0] = sx;
    S[1][1] = sy;
    return multiply(S, P);
}

vvd shear(vvd P, int shx, int shy)
{
    vvd S(3, vd(3, 0));
    for (int i = 0; i < 3; i++)
        S[i][i] = 1;
    S[0][1] = shx;
    S[1][0] = shy;
    return multiply(S, P);
}

void drawFig(GLenum mode, vvd P)
{
    glBegin(mode);
    for (int i = 0; i < P[0].size(); i++)
        glVertex2d(P[0][i], P[1][i]);
    glEnd();
    ;
}
void myInit()
{
    glClearColor(0, 0, 0, 0);
    glPointSize(10);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2);
}

void update(int value)
{
    angle += 2.0f; // Update the angle for rotation
    if (angle > 360.0f)
    {
        angle -= 360.0f;
    }

    glutPostRedisplay();          // Request a redraw to update the display
    glutTimerFunc(10, update, 0); // Call the update function again after 16 milliseconds
}
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    glColor3f(1, 0, 0);
    drawFig(GL_TRIANGLES, rotate(points, angle));
    glColor3f(0, 1, 0);
    drawFig(GL_TRIANGLES, translate(points, -100, 0));

    glColor3f(0, 0, 1);
    drawFig(GL_TRIANGLES, shear(scale(rotate(translate(points, -100, 0), 180), 2, 2), -1, 0));

    drawFig(GL_TRIANGLES, points2);
    drawFig(GL_TRIANGLES, rotate(points2, angle));

    glColor3f(1, 0, 1);
    drawFig(GL_TRIANGLES, translate(rotate(translate(points2, -100, -100), angle), 100, 100));

    glFlush();
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    glutCreateWindow("2d-trans");
    glutDisplayFunc(myDisplay);
    myInit();

    glutTimerFunc(20, update, 0);
    glutMainLoop();
    return 1;
}