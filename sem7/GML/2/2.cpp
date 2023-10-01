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

    drawLineDDA(0, 0, 400, 200);
    output(420, 200, "(400,200)");
    
    drawLineDDA(0, 0, 200, 400);
    output(220, 400, "(200,400)");

    drawLineDDA(-400, 200, 0, 0);
    output(-420, 200, "(-400,200)");
    
    drawLineDDA(-200, 400, 0, 0);
    output(-220, 400, "(-200,400)");
    
    drawLineDDA(0, 0, 400, -200);
    output(420, -200, "(400,-200)");
    
    drawLineDDA(0, 0, 200, -400);
    output(220, -400, "(200,-400)");
    
    drawLineDDA(-400, -200, 0, 0);
    output(-420, -200, "(-400,-200)");
    
    drawLineDDA(-200, -400, 0, 0);
    output(-220, -400, "(-200,-400)");
    
    glFlush();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // giving window size in X- and Y- direction
    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(0, 0);
    // Giving name to window
    glutCreateWindow("DDA line Drawing");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
