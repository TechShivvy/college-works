#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <cstring>
#include <iostream>
#define pi 3.142857
using namespace std;

int windowWidth = 1000;
int windowHeight = 1000;

void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(0.0, 1.0, 0.0); // making picture color green (in RGB mode), as middle argument is 1.0
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-windowHeight / 2, windowHeight / 2, -windowWidth / 2, windowWidth / 2);
}
void draw_pixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}
void drawLineDDA(float x0, float y0, float xn, float yn)
{
    // glClear(GL_COLOR_BUFFER_BIT);
    float dx = xn - x0;
    float dy = yn - y0;
    float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    float xIncrement = dx / steps;
    float yIncrement = dy / steps;
    float x = x0;
    float y = y0;
    for (int i = 0; i <= steps; ++i)
    {
        draw_pixel(static_cast<int>(x + 0.5), static_cast<int>(y + 0.5));
        x += xIncrement;
        y += yIncrement;
    }
}

void draw_axis()
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2d(-2000, 0);
    glVertex2d(2000, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(0, 2000);
    glVertex2d(0, -2000);
    glEnd();
    glFlush();
}
void draw_in_each_oct(GLint xk, GLint yk, GLint xc, GLint yc)
{
    draw_pixel(xc + xk, yc + yk);
    draw_pixel(xc + yk, yc + xk);
    draw_pixel(xc - yk, yc + xk);
    draw_pixel(xc - xk, yc + yk);
    draw_pixel(xc - xk, yc - yk);
    draw_pixel(xc - yk, yc - xk);
    draw_pixel(xc + yk, yc - xk);
    draw_pixel(xc + xk, yc - yk);
}

void midPtCircle(GLint xc, GLint yc, GLint r)
{
    GLint pk, xk, yk;
    pk = 1 - r;
    xk = 0;
    yk = r;
    draw_in_each_oct(xk, yk, xc, yc);
    while (xk <= yk)
    {
        if (pk < 0)
        {
            xk = xk + 1;
            pk = pk + (2 * xk) + 1;
        }
        else
        {
            xk = xk + 1;
            yk = yk - 1;
            pk = pk + (2 * xk) + 1 - (2 * yk);
        }
        draw_in_each_oct(xk, yk, xc, yc);
    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw_axis();
    glColor3f(0.0, 1.0, 0.0);

    GLint xc, yc, r;
    cout << "Enter xc, yc, radius(resp): ";
    cin >> xc >> yc >> r;
    midPtCircle(xc, yc, r);
    drawLineDDA(0, r, r, 0);
    drawLineDDA(r, 0, 0, -r);
    drawLineDDA(0, -r, -r, 0);
    drawLineDDA(-r, 0, 0, r);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowHeight, windowWidth);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Circle Drawing");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 1;
}
