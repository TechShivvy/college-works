#include <GL/glut.h>
#include <stdio.h>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 1000;

void myInit()
{
    glClearColor(0, 0, 0, 0);
    glPointSize(10);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluOrtho2D(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2);
}

void drawBoard()
{
    const GLint ROWS = 8;
    const GLint COLS = 8;
    const GLint SQUARE_SIZE = SCREEN_WIDTH / COLS;
    int c = 1;
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            c = ((i + j) & 1);
            glColor3f(c, c, c);
            glVertex2i(j * SQUARE_SIZE - SCREEN_WIDTH / 2, i * SQUARE_SIZE - SCREEN_HEIGHT / 2);
            glVertex2i((j + 1) * SQUARE_SIZE - SCREEN_WIDTH / 2, i * SQUARE_SIZE - SCREEN_HEIGHT / 2);
            glVertex2i((j + 1) * SQUARE_SIZE - SCREEN_WIDTH / 2, (i + 1) * SQUARE_SIZE - SCREEN_HEIGHT / 2);
            glVertex2i(j * SQUARE_SIZE - SCREEN_WIDTH / 2, (i + 1) * SQUARE_SIZE - SCREEN_HEIGHT / 2);
        }
    }
    glEnd();
    glFlush();
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawBoard();
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    glutCreateWindow("1-b");
    glutDisplayFunc(myDisplay);

    myInit();
    glutMainLoop();

    return 1;
}