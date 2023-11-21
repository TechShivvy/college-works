#include <GL/glut.h>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 1000;

const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;

typedef struct
{
    GLfloat x, y;
} Point;

Point wmin, wmax, p1, p2;

int i = 0;

void drawFig(GLenum mode, vector<double> xy)
{
    glBegin(mode);

    for (int i = 0; i < xy.size(); i += 2)
        glVertex2d(xy[i], xy[i + 1]);

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
}

void swap_points(Point *p1, Point *p2)
{
    Point t = *p1;
    *p1 = *p2;
    *p2 = t;
}

void swap_codes(GLint *x, GLint *y)
{
    GLint t = *x;
    *x = *y;
    *y = t;
}

GLint inside(GLint code)
{
    return !code;
}

GLint accept(GLint c1, GLint c2)
{
    return !(c1 | c2);
}

GLint reject(GLint c1, GLint c2)
{
    return (c1 & c2);
}

GLint encode(Point p)
{
    int x = p.x, y = p.y;
    int code = INSIDE;

    if (x > wmax.x)
        code |= RIGHT;
    else if (x < wmin.x)
        code |= LEFT;
    if (y > wmax.y)
        code |= TOP;
    else if (y < wmin.y)
        code |= BOTTOM;

    return code;
}

void cohen()
{
    GLint code1, code2;
    GLint done = 0, plot = 0;
    GLfloat m = 0;
    if (p1.x != p2.x)
        m = (p2.y - p1.y) / (p2.x - p1.x);

    while (!done)
    {
        code1 = encode(p1);
        code2 = encode(p2);
        if (accept(code1, code2))
        {
            done = 1;
            plot = 1;
        }
        else if (reject(code1, code2))
        {
            done = 1;
        }
        else
        {
            if (inside(code1))
            {
                swap_points(&p1, &p2);
                swap_codes(&code1, &code2);
            }

            if (code1 & LEFT)
            {
                p1.y += (wmin.x - p1.x) * m;
                p1.x = wmin.x;
            }
            if (code1 & RIGHT)
            {
                p1.y += (wmax.x - p1.x) * m;
                p1.x = wmax.x;
            }
            if (code1 & TOP)
            {
                if (p1.x != p2.x)
                    p1.x += (wmax.y - p1.y) / m;
                p1.y = wmax.y;
            }
            if (code1 & BOTTOM)
            {
                if (p1.x != p2.x)
                    p1.x += (wmin.y - p1.y) / m;
                p1.y = wmin.y;
            }
        }
    }

    if (plot)
    {
        glColor3f(1, 0, 0);
        glLineWidth(2);
        drawFig(GL_LINES, {round(p1.x), round(p1.y), round(p2.x), round(p2.y)});
    }
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    wmin.x = -250;
    wmax.x = 170;
    wmin.y = -130;
    wmax.y = 300;

    drawFig(GL_LINE_LOOP, {wmin.x, wmin.y, wmax.x, wmin.y, wmax.x, wmax.y, wmin.x, wmax.y});
}

void myKey(unsigned char ch, int x, int y)
{
    if (ch == 'c')
    {
        cohen();
    }
}

void myMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && i < 2)
    {
        if (i == 0)
        {
            p1.x = x - SCREEN_WIDTH / 2;
            p1.y = SCREEN_HEIGHT / 2 - y;
        }
        if (i == 1)
        {
            p2.x = x - SCREEN_WIDTH / 2;
            p2.y = SCREEN_HEIGHT / 2 - y;
        }
        i++;
    }
    else if (i == 2)
    {
        drawFig(GL_LINES, {p1.x, p1.y, p2.x, p2.y});
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    glutCreateWindow("CSL");
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKey);
    glutMouseFunc(myMouse);

    myInit();
    glutMainLoop();
    return 1;
}