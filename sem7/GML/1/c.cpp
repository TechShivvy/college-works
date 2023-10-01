// #include <GLUT/glut.h>   //in clg system
#include <GL/glut.h> //my laptop

int windowWidth = 800;
int windowHeight = 600;

void myInit()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); //White BG
    // glPointSize(10);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);

    // why?
    // glMatrixMode(GL_MODELVIEW);
}
void drawHouse()
{
    // Clear the screen
    // Draw the house using different primitive shapes
    // Draw the base of the house using a quad
    glColor3f(0.59f, 0.85f, 0.71f); // Gray color
    glBegin(GL_QUADS);
    glVertex2i(100, 100);
    glVertex2i(500, 100);
    glVertex2i(500, 400);
    glVertex2i(100, 400);
    glEnd();

    // Draw the roof using triangles
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glBegin(GL_TRIANGLES);
    glVertex2i(100, 400);
    glVertex2i(300, 600);
    glVertex2i(500, 400);
    glEnd();
    
    // Draw the door using quads
    glColor3f(1.0f, 1.0f, 1.0f); // Blue color
    glBegin(GL_QUADS);
    glVertex2i(250, 100);
    glVertex2i(350, 100);
    glVertex2i(350, 300);
    glVertex2i(250, 300);
    // glEnd();

    glColor3f(0.36f, 0.05f, 0.05f);
    // glBegin(GL_QUADS);
    glVertex2i(250, 100);
    glVertex2i(330, 130);
    glVertex2i(330, 300);
    glVertex2i(250, 300);
    // glEnd();

    // Draw the windows using quads
    glColor3f(0.06f, 0.22f, 0.45f); // Green color
    // glBegin(GL_QUADS);
    glVertex2i(150, 200);
    glVertex2i(200, 200);
    glVertex2i(200, 250);
    glVertex2i(150, 250);
    glVertex2i(400, 200);
    glVertex2i(450, 200);
    glVertex2i(450, 250);
    glVertex2i(400, 250);

    glEnd();
    glFlush();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawHouse();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Drawing a House using OpenGL");
    glutDisplayFunc(display);
    myInit(); // glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // White background
    glutMainLoop();
    return 0;
}