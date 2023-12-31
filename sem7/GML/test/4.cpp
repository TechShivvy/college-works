#include <GL/glut.h>
#include <stdio.h>
#include <cmath>
#include <iostream>

#define RANDOM static_cast<double>(rand()) / static_cast<double>(RAND_MAX)

using namespace std;

const int SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 1000;

typedef struct
{
    GLfloat x, y;
} Point;

Point c;
GLfloat r;

void myInit()
{
    glClearColor(0, 0, 0, 0);
    glPointSize(10);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2);
}

void drawPixel(float x, float y)
{
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}

void drawAxis()
{
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2d(2000, 0);
    glVertex2d(-2000, 0);
    glVertex2d(0, 2000);
    glVertex2d(0, -2000);
    glEnd();
    glFlush();
}

// pattern: 4 plus xyyx,1 plus yxxy
void drawInEachOctet(GLint x, GLint y)
{
    drawPixel(c.x + x, c.y + y);
    drawPixel(c.x + y, c.y - x);
    drawPixel(c.x + y, c.y + x);
    drawPixel(c.x + x, c.y - y);
    drawPixel(c.x - x, c.y + y);
    drawPixel(c.x - y, c.y - x);
    drawPixel(c.x - y, c.y + x);
    drawPixel(c.x - x, c.y - y);
}

void drawCircle()
{
    GLint xk, yk, pk;
    pk = 1 - r;
    xk = 0, yk = r;
    drawInEachOctet(xk, yk);
    while (xk <= yk)
    {
        // if (pk < 0)
        // {
        //     xk++;
        //     pk += 2 * xk + 1;
        // }
        // else
        // {
        //     xk++;
        //     yk--;
        //     pk += 2 * xk + 1 - 2 * yk;
        // }
        pk += 2 * (++xk) + 1 - ((pk >= 0) ? 2 * (--yk) : 0);
        drawInEachOctet(xk, yk);
    }
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxis();

    cout << "Enter center,radius (x,y,r): ";
    cin >> c.x >> c.y >> r;

    // c.x = c.y = 0;
    // r = 100;

    drawCircle();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    glutCreateWindow("CIRCLE");
    glutDisplayFunc(myDisplay);

    myInit();
    glutMainLoop();
    return 1;
}