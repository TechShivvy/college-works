#include <cmath>
#include <cstring>
#include <stdio.h>
#include <GL/glut.h>
using namespace std;

// screen dimensions
const int windowWidth = 1300;
const int windowHeight = 1300;

void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-windowWidth / 2, windowWidth / 2, -windowHeight / 2, windowHeight / 2);
    // glViewport(0, 0, windowWidth, windowHeight);
}

void mykey(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
    }
}

// Just to draw a point
void draw_pixel(int x, int y)
{
    glPointSize(1.0); // Specify point thickness
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void obj(int a, int b, int c, int d, int e, int f)
{
    glBegin(GL_POLYGON);
    glVertex2d(a, b);
    glVertex2d(c, d);
    glVertex2d(e, f);
    glEnd();
}

// window to viewport transformation
void wov(int *x, int *y, int x_wmax,
         int y_wmax, int x_wmin, int y_wmin,
         int x_vmax, int y_vmax, int x_vmin,
         int y_vmin)
{
    // point on viewport
    int x_v, y_v;

    // scaling factors for x coordinate and y coordinate
    float sx, sy;

    // calculating Sx and Sy
    sx = (float)(x_vmax - x_vmin) / (x_wmax - x_wmin);
    sy = (float)(y_vmax - y_vmin) / (y_wmax - y_wmin);

    // calculating the point on viewport
    x_v = x_vmin + (float)((*x - x_wmin) * sx);
    y_v = y_vmin + (float)((*y - y_wmin) * sy);

    *x = x_v;
    *y = y_v;
}

void display1(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Green
    glColor3f(0.0, 1.0, 0.0);

    // Call function
    obj(-200, 150, 500, 150, -400, -450);

    // White
    glColor3f(1.0, 1.0, 1.0);

    glFlush();
     glutSwapBuffers();
}

void display2(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    int xmin = -375, xmax = 525, ymin = -200, ymax = 600;

    // Green
    glColor3f(0.0, 1.0, 0.0);

    // Call function
    int x1[2], x2[2], x3[2];
    x1[0] = -200, x1[1] = 150, x2[0] = 500, x2[1] = 150, x3[0] = -400, x3[1] = -450;

    // Red
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2i(xmin, ymax);
    glVertex2i(xmax, ymax);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(xmin, ymax);
    glVertex2i(xmin, ymin);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(xmin, ymin);
    glVertex2i(xmax, ymin);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(xmax, ymax);
    glVertex2i(xmax, ymin);
    glEnd();

    // Green
    glColor3f(0.0, 1.0, 0.0);
    x1[0] = -200, x1[1] = 150, x2[0] = 500, x2[1] = 150, x3[0] = -400, x3[1] = -450;
    wov(&x1[0], &x1[1], windowHeight / 2, windowWidth / 2, -windowHeight / 2, -windowWidth / 2, xmax, ymax, xmin, ymin);
    wov(&x2[0], &x2[1], windowHeight / 2, windowWidth / 2, -windowHeight / 2, -windowWidth / 2, xmax, ymax, xmin, ymin);
    wov(&x3[0], &x3[1], windowHeight / 2, windowWidth / 2, -windowHeight / 2, -windowWidth / 2, xmax, ymax, xmin, ymin);
    obj(x1[0], x1[1], x2[0], x2[1], x3[0], x3[1]);

    glFlush();
     glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);

    glutInitWindowPosition(0, 0);
    glutCreateWindow("Window");
    // glutReshapeFunc(handleResize);
    glutDisplayFunc(display1);

    myInit();
    glutKeyboardFunc(mykey);

    glutInitWindowPosition(500, 500);
    glutCreateWindow("Viewport");
    // glutReshapeFunc(handleResize);
    glutDisplayFunc(display2);

    myInit();
    glutKeyboardFunc(mykey);
    glutMainLoop();
}