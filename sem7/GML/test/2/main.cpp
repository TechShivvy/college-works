#include <GL/glut.h>
#include <stdio.h>
#include <vector>
#include <cmath>
int width = 1000, height = 1000;
void myInit(void)
{
    glClearColor(0, 0, 1, 0);
    glPointSize(10);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);
}
void draw_pixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}
void draw_axis()
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2d(-2000, 0);
    glVertex2d(2000, 0);

    glVertex2d(0, 2000);
    glVertex2d(0, -2000);
    glEnd();
    glFlush();
}
void DDA(GLfloat x0, GLfloat y0, GLfloat xn, GLfloat yn)
{
    GLfloat dx = xn - x0;
    GLfloat dy = yn - y0;

    GLfloat steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    GLfloat xInc = dx / steps;
    GLfloat yInc = dy / steps;
    GLfloat x = x0;
    GLfloat y = y0;
    for (int i = 0; i <= steps; i++)
    {
        draw_pixel(static_cast<int>(x + 0.5), static_cast<int>(x + 0.5));
        x += xInc;
        y += yInc;
    }
}
void bresh(int x1, int y1, int x2, int y2)
{
    int dx,dy,i,e;
    int incx,incy,inc1,inc2;
    int x,y;
    dx=abs(x2-x1);
    dy=abs(y2-y1);
    incx=x2<x1?-1:1;
    incy=y2<y1?-1:1;
    x=x1,y=y1;
    if(dx>dy)
    {
        draw_pixel(x,y);
        e=2*dy-dx;
        inc1=2*(dy-dx);
        inc2=2*dy;
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
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw_axis();
    glColor3f(0, 1, 1);
    glBegin(GL_LINES);
    DDA(-300, -300, 300, 300);
    bresh(-300,300,300,-300);
    glEnd();
    glFlush();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);

    glutCreateWindow("1-a");
    glutDisplayFunc(myDisplay);

    myInit();
    glutMainLoop();

    return 1;
}
