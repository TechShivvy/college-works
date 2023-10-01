#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <cstring>
#define pi 3.142857

void output(int x, int y, const char *string)
{
    glRasterPos2f(x, y);
    int len, i;
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
    }
}
void draw_pixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}
void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(0.0, 1.0, 0.0); // making picture color green (in RGB mode), as middle argument is 1.0
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-780, 780, -420, 420);
}
int sign(int x)
{
    return (x > 0) - (x < 0);
}
void bresenham(int x1, int y1, int x2, int y2)
{
    int dx, dy, i, e;
    int incx, incy, inc1, inc2;
    int x, y;
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    incx = x2 < x1 ? -1 : 1;
    incy = y2 < y1 ? -1 : 1;
    x = x1;
    y = y1;
    if (dx > dy)
    {
        draw_pixel(x, y);
        e = 2 * dy - dx;
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;
        for (i = 0; i < dx; i++)
        {
            if (e >= 0)
            {
                y += incy;
                e += inc1;
            }
            else
                e += inc2;
            x += incx;
            draw_pixel(x, y);
        }
    }
    else
    {
        draw_pixel(x, y);
        e = 2 * dx - dy;
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;
        for (i = 0; i < dy; i++)
        {
            if (e >= 0)
            {
                x += incx;
                e += inc1;
            }
            else
                e += inc2;
            y += incy;
            draw_pixel(x, y);
        }
    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_LINES);
    glVertex2d(0, 420);
    glVertex2d(0, -420);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(780, 0);
    glVertex2d(-780, 0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);

    bresenham(0, 0, 400, 200);
    output(420, 200, "(400,200)");
    bresenham(0, 0, 200, 400);
    output(220, 400, "(200,400)");
    bresenham(-400, 200, 0, 0);
    output(-420, 220, "(-400,200)");
    bresenham(-200, 400, 0, 0);
    output(-220, 400, "(-200,400)");

    bresenham(0, 0, 400, -200);
    output(420, -200, "(400,-200)");
    bresenham(0, 0, 200, -400);
    output(220, -400, "(200,-400)");
    bresenham(-400, -200, 0, 0);
    output(-420, -200, "(-400,-200)");
    bresenham(-200, -400, 0, 0);
    output(-220, -400, "(-200,-400)");

    glFlush();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham line Drawing");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 1;
}
