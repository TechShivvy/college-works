#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdio.h>
using namespace std;

// Setting Projection mode (0 for Orthographic, 1 for Perspective)
int projectionMode = 0;
// Rotation angles
float rotateX = 0.0f;
float rotateY = 0.0f;
// Camera position
float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 5.0f;
// Function to draw the 3D object
void draw3DObject()
{
    glBegin(GL_TRIANGLES);
    glColor3f(0.478, 0.149, 0.678); // Dark Purple
    glVertex3f(0, 1, 0);
    glVertex3f(-1, 0, -1);
    glVertex3f(1, 0, -1);
    glColor3f(0.706, 0.576, 0.839); // Lavender
    glVertex3f(0, 1, 0);
    glVertex3f(1, 0, -1);
    glVertex3f(1, 0, 1);
    glColor3f(0.306, 0.2, 0.42); // Indigo
    glVertex3f(0, 1, 0);
    glVertex3f(1, 0, 1);
    glVertex3f(-1, 0, 1);
    glColor3f(0.482, 0, 1); // Purple 2
    glVertex3f(0, 1, 0);
    glVertex3f(-1, 0, 1);
    glVertex3f(-1, 0, -1);
    glEnd();
    glColor3f(1.0, 1.0, 1.0); // White Base
    glBegin(GL_QUADS);
    glVertex3f(-1, 0, -1);
    glVertex3f(1, 0, -1);
    glVertex3f(-1, 0, 1);
    glVertex3f(-1, 0, -1);
    glEnd();
    // Vertices
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glLineWidth(2.0f);
    glVertex3f(0, 1, 0);
    glVertex3f(-1, 0, -1);
    glVertex3f(0, 1, 0);
    glVertex3f(1, 0, -1);
    glVertex3f(0, 1, 0);
    glVertex3f(1, 0, 1);
    glVertex3f(0, 1, 0);
    glVertex3f(-1, 0, 1);
    glVertex3f(-1, 0, -1);
    glVertex3f(1, 0, -1);
    glVertex3f(1, 0, -1);
    glVertex3f(1, 0, 1);
    glVertex3f(1, 0, 1);
    glVertex3f(-1, 0, 1);
    glVertex3f(-1, 0, -1);
    glVertex3f(-1, 0, 1);
    glEnd();
}
// Function to set up the perspective projection
void setPerspectiveProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}
// Function to set up the orthographic projection
void setOrthographicProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}
// Display function
void display()
{
    glClearColor(0.0, 1.0, 1.0, 0.3);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set camera position and look at (0, 0, 0) and positive Y up vector
    gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);
    // Apply rotation
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f); // Roate along X
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f); // Rotate along Y
    // Draw X, Y, and Z axes
    glBegin(GL_LINES);
    glLineWidth(5.0f);
    glColor3f(0.075, 0.043, 0.349); // X - Dark Blue
    glVertex3f(-2, 0, 0);
    glVertex3f(2, 0, 0);
    glColor3f(0.49, 0.6, 0.859); // Y - Medium Blue
    glVertex3f(0, -2, 0);
    glVertex3f(0, 2, 0);
    glColor3f(0.118, 0.871, 0.969); // Z - Light Blue
    glVertex3f(0, 0, -2);
    glVertex3f(0, 0, 2);
    glEnd();
    draw3DObject(); // Draw the 3D object
    glutSwapBuffers();
}
// Keyboard function to handle menu-driven options
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'o':
        projectionMode = 0; // Switch to Orthographic projection
        setOrthographicProjection();
        break;
    case 'p':
        projectionMode = 1; // Switch to Perspective projection
        setPerspectiveProjection();
        break;
    case 'x':
        rotateX += 10.0f; // Rotate object in X dirn
        break;
    case 'y':
        rotateY += 10.0f; // Rotate object in Y dirn
        break;
    case 'b':
        cameraZ -= 5.0f; // Move camera forward
        break;
    case 'f':
        cameraZ += 5.0f; // Move camera backward
        break;
    case 27: // ESC key to exit
        exit(0);
    }
    glutPostRedisplay();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Projection");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    setOrthographicProjection(); // Initial projection mode
    glutMainLoop();
    return 0;
}