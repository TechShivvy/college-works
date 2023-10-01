// #include <GLUT/glut.h>   //in clg system
#include <GL/glut.h> //my laptop

int windowWidth = 800;
int windowHeight = 800;
void myInit()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // glPointSize(10);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);

    // why?
    // glMatrixMode(GL_MODELVIEW);
}
void drawCheckerboard()
{
    // glVertex2i-2i-i=int

    int rows = 8;
    int cols = 8;
    int squareSize = windowWidth / cols;

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            ((i + j) & 1) ? glColor3f(0.0f, 0.0f, 0.0f) : glColor3f(1.0f, 1.0f, 1.0f);
            glVertex2i(j * squareSize, i * squareSize);
            glVertex2i((j + 1) * squareSize, i * squareSize);
            glVertex2i((j + 1) * squareSize, (i + 1) * squareSize);
            glVertex2i(j * squareSize, (i + 1) * squareSize);
        }
    }

    glEnd();
    glFlush();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawCheckerboard();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("1-b");
    glutDisplayFunc(display);
    myInit(); // glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutMainLoop();
    return 1;
}