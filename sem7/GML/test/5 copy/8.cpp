#include <GL/glut.h>

GLfloat cubeRotation = 0.0f;
GLfloat pyramidRotation = 0.0f;

void myInit()
{
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
}

void drawShape(GLenum mode, const GLfloat *vertices, const GLfloat *colors)
{
    glBegin(mode);

    for (int i = 0, j = 0; i < 24; i += 3, j += 3)
    {
        glColor3fv(&colors[j]);
        glVertex3fv(&vertices[i]);
    }

    glEnd();
}

void drawAxes()
{
    glBegin(GL_LINES);

    // X-axis (Red)
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    // Y-axis (Green)
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    // Z-axis (Blue)
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw 3D Axes
    drawAxes();

    // Draw 3D Shapes with Rotation
    glPushMatrix();
    glRotatef(cubeRotation, 1.0f, 1.0f, 1.0f);

    GLfloat cubeVertices[] = {
        // Front face (Red)
        -1,
        -1,
        1,
        1,
        -1,
        1,
        1,
        1,
        1,
        -1,
        1,
        1,
        // Back face (Green)
        -1,
        -1,
        -1,
        1,
        -1,
        -1,
        1,
        1,
        -1,
        -1,
        1,
        -1,
    };

    GLfloat cubeColors[] = {
        1,
        0,
        0,
        1,
        0,
        0,
        1,
        0,
        0,
        1,
        0,
        0,
        0,
        1,
        0,
        0,
        1,
        0,
        0,
        1,
        0,
        0,
        1,
        0,
    };

    drawShape(GL_QUADS, cubeVertices, cubeColors);
    glPopMatrix();

    glPushMatrix();
    glRotatef(pyramidRotation, 0.0f, 1.0f, 0.0f);

    GLfloat pyramidVertices[] = {
        // Base
        -1, -1, -1,
        1, -1, -1,
        1, -1, 1,
        -1, -1, 1,
        // Apex
        0, 1, 0};

    GLfloat pyramidColors[] = {
        1, 1, 0,
        1, 1, 0,
        1, 1, 0,
        1, 1, 0,
        1, 1, 0};

    // drawShape(GL_TRIANGLE_FAN, pyramidVertices, pyramidColors);
    glPopMatrix();

    glutSwapBuffers();
}

void update(int value)
{
    cubeRotation += 2.0f;
    pyramidRotation += 1.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("3D Shapes with Axes");
    glutDisplayFunc(myDisplay);

    myInit();
    glutTimerFunc(25, update, 0); // Add timer function for animation
    glutMainLoop();
    return 0;
}
