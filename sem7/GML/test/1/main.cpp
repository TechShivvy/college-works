#include <GL/glut.h>
#include <stdio.h>
#include <vector>
using namespace std;
int width = 1000, height = 1000;
void myInit()
{
    glClearColor(0, 0, 0, 0);
    glPointSize(10);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);
}
void drawShape(GLenum mode, const vector<int> &vertices)
{
    glBegin(mode);
    for (int i = 0; i < vertices.size(); i += 2)
    {
        int x = vertices[i];
        int y = vertices[i + 1];
        glVertex2d(x, y);
    }
    glEnd();
    glFlush();
}
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawShape(GL_POINTS, {0, 0});

    glColor3f(0.0f, 1.0f, 0.0f);
    drawShape(GL_LINES, {-100, -100, 100, 100});
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