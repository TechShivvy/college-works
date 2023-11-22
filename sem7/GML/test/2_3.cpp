#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;

const int SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 1000;
int i = 0;
typedef struct
{
    GLfloat x, y;
} Point;

Point p1, p2;

void draw_pixel(GLfloat x, GLfloat y)
{
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void draw_axis()
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    // glVertex2d(-2000, SCREEN_HEIGHT/2);
    // glVertex2d(2000, SCREEN_HEIGHT/2);

    // glVertex2d(SCREEN_WIDTH, 2000);
    // glVertex2d(SCREEN_WIDTH/2, -2000);
    glVertex2d(-2000, 0);
    glVertex2d(2000, 0);

    glVertex2d(0, 2000);
    glVertex2d(0, -2000);
    glEnd();
    glFlush();
}

void myInit()
{
    glClearColor(0, 0, 0, 0);
    glPointSize(10);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2);
    // gluOrtho2D(0, 1000, 0, 1000);
}

void DDA()
{
    // cout << "P1: " << p1.x << " " << p1.y << endl;
    // cout << "P2: " << p2.x << " " << p2.y << endl;
    GLfloat dx = p2.x - p1.x,
            dy = p2.y - p1.y;

    GLfloat steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    GLfloat xInc = dx / steps,
            yInc = dy / steps;

    GLfloat x = p1.x,
            y = p1.y;

    for (int i = 0; i <= steps; i++)
    {
        draw_pixel(x, y);
        x += xInc;
        y += yInc;
    }
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

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // draw_pixel(0, 0);
    draw_axis();
    // DDA();
    // Bresenham();
}

void myKey(unsigned char ch, int x, int y)
{
    if (ch == 'b')
    {
        Bresenham();
        glFlush();
    }
    else if (ch == 'd')
    {
        DDA();
        glFlush();
    }
}

void myMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && i < 2)
    {
        cout << "x:" << x << " y:" << y << endl;
        if (i == 0)
        {
            p1.x = x - SCREEN_WIDTH / 2;
            p1.y = SCREEN_HEIGHT / 2 - y;
            i++;
        }
        else
        {
            p2.x = x - SCREEN_WIDTH / 2;
            p2.y = SCREEN_HEIGHT / 2 - y;
            i++;
            i = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    glutCreateWindow("line drawing");
    glutDisplayFunc(myDisplay);

    glutKeyboardFunc(myKey);
    glutMouseFunc(myMouse);

    myInit();
    glutMainLoop();
    return 1;
}