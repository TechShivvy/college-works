#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>

#define vd vector<double>
#define vvd vector<vd>

using namespace std;

const int SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 1000;

typedef struct
{
    GLfloat x, y;
} Point;

Point p1, p2, c;

float angle = 0.0f, r = 100;

void drawAxes()
{
    glBegin(GL_LINES);
    glVertex2i(0, 2000);
    glVertex2i(0, -2000);
    glVertex2i(-2000, 0);
    glVertex2i(2000, 0);
    glEnd();
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

vvd rotate(vvd P, int deg)
{
    vvd R(3, vd(3, 0));
    R[2][2] = 1;
    R[0][0] = R[1][1] = cos(M_PI * deg / 180);
    R[0][1] = R[1][0] = sin(M_PI * deg / 180);
    R[0][1] *= -1;
    return multiply(R, P);
}

void drawFig(GLenum mode, vvd P)
{
    glBegin(mode);
    for (int i = 0; i < P[0].size(); i++)
        glVertex2d(P[0][i], P[1][i]);
    glEnd();
}

void draw_pixel(GLfloat x, GLfloat y)
{
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void Bresenham()
{
    int x = p1.x, y = p1.y, swapped = 0;

    int p,
        dx = fabs(p2.x - p1.x),
        dy = fabs(p2.y - p1.y);

    int inc1, inc2,
        incx = p2.x < p1.x ? -1 : 1,
        incy = p2.y < p1.y ? -1 : 1;

    if (dx <= dy)
    {
        swap(dx, dy);
        swapped = 1;
    }

    p = 2 * dy - dx;
    inc1 = 2 * (dy - dx);
    inc2 = 2 * dy;

    draw_pixel(x, y);

    for (int i = 0; i < dx; i++, swapped ? y += incy : x += incx, draw_pixel(x, y))
    {
        if (p < 0)
            p += inc2;
        else
        {
            p += inc1;
            !swapped ? y += incy : x += incx;
        }
    }
}

void drawInEachOctet(GLint x, GLint y)
{
    draw_pixel(c.x + x, c.y + y);
    draw_pixel(c.x + y, c.y - x);
    draw_pixel(c.x + y, c.y + x);
    draw_pixel(c.x + x, c.y - y);
    draw_pixel(c.x - x, c.y + y);
    draw_pixel(c.x - y, c.y - x);
    draw_pixel(c.x - y, c.y + x);
    draw_pixel(c.x - x, c.y - y);
}

void drawCircle()
{
    GLint xk, yk, pk;
    pk = 1 - r;
    xk = 0, yk = r;
    drawInEachOctet(xk, yk);
    while (xk <= yk)
    {
        pk += 2 * (++xk) + 1 - ((pk >= 0) ? 2 * (--yk) : 0);
        drawInEachOctet(xk, yk);
    }
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
    // if (angle > 360.0f)
    //     angle -= 360.0f;

    glutPostRedisplay();         // Request a redraw to update the display
    glutTimerFunc(1, update, 0); // Call the update function again after 16 milliseconds
}
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    c.x = c.y = 0;
    drawCircle();

    // using user defined rotate
    // drawFig(GL_LINES,rotate({{0,0},{-100,100},{1,1}},angle));

    // translating the points around circle using polar coordinates
    p1.x = 0 * cos(angle) - (-100) * sin(angle);
    p1.y = 0 * sin(angle) + (-100) * cos(angle);
    p2.x = 0 * cos(angle) - 100 * sin(angle);
    p2.y = 0 * sin(angle) + 100 * cos(angle);
    Bresenham();

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

    glutTimerFunc(25, update, 0);
    glutMainLoop();
    return 1;
}