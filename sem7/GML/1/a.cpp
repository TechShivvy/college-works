// #include <GLUT/glut.h>   //in clg system
#include <GL/glut.h> //my laptop
#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;
void myInit()
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // used for glClear: sets bitplane window
    glPointSize(10);
    glMatrixMode(GL_PROJECTION); // applies the matrix operations to corresponding stack
    /*
    GL_MODELVIEW    -   modelview matrix stack.
    GL_PROJECTION   -   projection
    GL_TEXTURE      -   texture
    GL_COLOR        -   color
    */
    glLoadIdentity();                   // replaces the current matrix with the identity matrix
    gluOrtho2D(0.0, 640.0, 0.0, 480.0); // sets up a 2D orthographic viewing region
    // for (0,0) to be at the center of the screen, put it like (-320,320,-240,240)
}

//****************************version 1****************************:

// void myDisplay()
// {
//     glClear(GL_COLOR_BUFFER_BIT);
//     glBegin(GL_POINTS);
//     glVertex2d(150, 100);
//     glEnd();

//     glBegin(GL_LINES);
//     glVertex2d(150, 150);
//     glVertex2d(150, 200);
//     glEnd();

//     glBegin(GL_QUADS);
//     glColor3f(0.0f, 1.0f, 0.0f);
//     glVertex2d(300, 300);
//     glVertex2d(300, 350);
//     glVertex2d(350, 350);
//     glVertex2d(350, 300);
//     glVertex2d(300, 300);
//     glEnd();

//     glBegin(GL_TRIANGLES); // Each set of 3 vertices form a triangle
//     glColor3f(0.0f, 0.0f, 1.0f);
//     glVertex2d(400, 400);
//     glVertex2d(400, 450);
//     glVertex2d(450, 450);
//     glVertex2d(400, 400);
//     glEnd();

//     glBegin(GL_POLYGON);         // These vertices form a closed polygon
//     glColor3f(1.0f, 1.0f, 0.0f); // Yellow
//     glVertex2d(200, 200);
//     glVertex2d(200, 220);
//     glVertex2d(220, 240);
//     glVertex2d(240, 200);
//     glVertex2d(230, 250);
//     glVertex2d(250, 250);
//     glVertex2d(200, 200);
//     glEnd();

//     glFlush();
// }

//****************************version 2****************************:

// Function to convert GLenum value to string
string GLenumToString(GLenum mode)
{
    switch (mode)
    {
    case GL_POINTS:
        return "GL_POINTS";
    case GL_LINES:
        return "GL_LINES";
    case GL_LINE_STRIP:
        return "GL_LINE_STRIP";
    case GL_LINE_LOOP:
        return "GL_LINE_LOOP";
    case GL_TRIANGLES:
        return "GL_TRIANGLES";
    case GL_TRIANGLE_STRIP:
        return "GL_TRIANGLE_STRIP";
    case GL_TRIANGLE_FAN:
        return "GL_TRIANGLE_FAN";
    case GL_QUADS:
        return "GL_QUADS";
    case GL_QUAD_STRIP:
        return "GL_QUAD_STRIP";
    case GL_POLYGON:
        return "GL_POLYGON";
    default:
        return "Unknown";
    }
    return "";
}

// Common function to draw shapes
void drawShape(GLenum mode, double vertices[], int numVertices)
{
    // glVertex2d-2d-d=double
    glBegin(mode);
    cout << "Drawing mode: " << GLenumToString(mode) << " (Value: " << mode << ")\n";
    for (int i = 0; i < numVertices; i += 2)
    {
        // glVertex2d(vertices[i], vertices[i + 1]);

        double x = vertices[i];
        double y = vertices[i + 1];
        cout << "Vertex (" << x << ", " << y << ")" << endl; // Print coordinates
        glVertex2d(x, y);
    }
    glEnd();
    cout << endl;
}

// Function to draw text at a given position
void drawText(double x, double y, int a = 0, int b = 0)
{
    char text[20];
    snprintf(text, 20, "(%0.0f,%0.0f)", x, y);
    glRasterPos2d(x + a, y + b);
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text[i]);
    memset(text, 0, sizeof(text));
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);

    double pointVertices[] = {150, 100};
    double lineVertices[] = {150, 150, 150, 200};
    double quadVertices[] = {300, 300, 300, 350, 350, 350, 350, 300, 300, 300};
    double triangleVertices[] = {400, 400, 400, 450, 450, 450, 400, 400};
    double polygonVertices[] = {200, 200, 200, 220, 220, 240, 240, 200, 230, 250, 250, 250, 200, 200};

    // Draw points
    drawShape(GL_POINTS, pointVertices, sizeof(pointVertices) / sizeof(pointVertices[0]));
    drawText(pointVertices[0], pointVertices[1], 10, -5);

    // Draw lines
    drawShape(GL_LINES, lineVertices, sizeof(lineVertices) / sizeof(lineVertices[0]));
    drawText(lineVertices[0], lineVertices[1], 10, -5);
    drawText(lineVertices[2], lineVertices[3], -55,-5);

    // Draw quads
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);
    drawShape(GL_QUADS, quadVertices, sizeof(quadVertices) / sizeof(quadVertices[0]));
    glEnd();

    // Draw triangles
    glColor3f(0.0f, 0.0f, 1.0f);
    drawShape(GL_TRIANGLES, triangleVertices, sizeof(triangleVertices) / sizeof(triangleVertices[0]));

    // Draw polygon
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    drawShape(GL_POLYGON, polygonVertices, sizeof(polygonVertices) / sizeof(polygonVertices[0]));
    glEnd();

    glFlush();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("1-a");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
    return 1;
}