#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <math.h>
#define vvd vector<vector<double>>
#define vd vector<double>
using namespace std;
vvd points, points2;
double angle;
void myInit(void)
{
    glClearColor(1, 1, 1, 1);
    glColor3f(0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-320, 320, -240, 240);
}
vvd multiply(vvd a, vvd b)
{
    int r1 = a.size();
    int c1 = a[0].size();
    int r2 = b.size();
    int c2 = b[0].size();
    vvd c(r1, vd(c2, 0));
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            for (int k = 0; k < r2; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}
vvd translate(vvd P, int tx, int ty)
{
    vvd T(3, vd(3, 0));
    for (int i = 0; i < 3; i++)
    {
        T[i][i] = 1;
    }
    T[0][2] = tx;
    T[1][2] = ty;
    return multiply(T, P);
}
void displayFig(vvd fig)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < fig[0].size(); i++)
    {
        glVertex2f(fig[0][i], fig[1][i]);
    }
    glEnd();
}
void circle(int x1, int y1, int r)
{
    int x = 0;
    int y = r;
    float decision = 5 / 4 - r;
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    glVertex2i(x + x1, y + y1);
    while (x < y)
    {
        if (decision < 0)
        {
            x++;
            decision += 2 * x + 1;
        }
        else
        {
            x++;
            y--;
            decision += 2 * (x - y) + 1;
        }
        glVertex2i(x1 + x, y1 + y);
        glVertex2i(x1 - x, y1 + y);
        glVertex2i(x1 + x, y1 - y);
        glVertex2i(x1 - x, y1 - y);
        glVertex2i(x1 + y, y1 + x);
        glVertex2i(x1 - y, y1 + x);
        glVertex2i(x1 + y, y1 - x);
        glVertex2i(x1 - y, y1 - x);
    }
    glEnd();
}
vvd rotate(vvd P, double deg)
{
    double rad = (M_PI / 180) * deg;
    vvd R(3, vd(3, 0));
    R[0][0] = R[1][1] = cos(rad);
    R[0][1] = -1 * sin(rad);
    R[1][0] = sin(rad);
    return multiply(R, P);
}
void displayWings(int val)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2.0);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2i(-500, 0);
    glVertex2i(500, 0);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(0, -500);
    glVertex2i(0, 500);
    glEnd();
    // displayFig(points);
    circle(0, 0, 30);
    displayFig(rotate(translate(points, 0, 30), val));
    displayFig(rotate(translate(points, 0, 30), val - 120));
    displayFig(rotate(translate(points, 0, 30), val - 240));
    glFlush();
    glutTimerFunc(25, displayWings, val - 2);
}
void myDisplay(void)
{
    // displayWings(0);
    glutTimerFunc(100, displayWings, 0);
}
int main(int argc, char *argv[])
{
    points = {
        {-7, -7, 7, 7},
        {0, 100, 100, 0},
        {1, 1, 1, 1}};
    angle = 0;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Fan rotation");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
    return 0;
}