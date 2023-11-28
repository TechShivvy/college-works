#include <GL/glut.h>
#include <stdio.h>

using namespace std;

GLfloat X = -3, Y = 4.5, angle = 0.0f;

void drawAxes()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3d(-1000, 0, 0);
    glVertex3d(1000, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3d(0, -1000, 0);
    glVertex3d(0, 1000, 0);

    glColor3f(0, 0, 1);
    glVertex3d(0, 0, -1000);
    glVertex3d(0, 0, 1000);

    glEnd();
}

void myReshape(int width, int height)
{
    if (height == 0)
        height = 1;

    float ratio = width * 1.0 / height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    // -2.0, 2.0, -2.0, 2.0, 1.0, 100.0
    glLoadIdentity();
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

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

    gluLookAt(15, 15, 15, 0, 0, 0, 0, 1, 0);
}

void drawTeapot()
{
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(X, Y, 0);
    glRotatef(angle, 0, 1, 0);
    glutWireTeapot(2);
    glPopMatrix();
}

void drawDisc()
{

    GLUquadricObj *disc = gluNewQuadric();

    glPushMatrix();
    glColor3f(1, 0, 1);
    glRotatef(90, 1, 0, 0);
    glTranslatef(3, 0, 0);
    gluDisk(disc, 0.0, 2, 20, 20); // Draw the base circle
    glPopMatrix();

    gluDeleteQuadric(disc);
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawAxes();

    drawTeapot();

    drawDisc();

    glutSwapBuffers();
}

void update(int value)
{
    angle += 5.0f;
    if (X < 3)
        X += 0.2;
    if (angle > 360.0f)
        angle -= 360.0f;
    if (X > 3)
    {

        Y -= 0.1;
        if (Y < 1.5)
            return;
    }
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);

    glutCreateWindow("Flying Teapot");
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    glutTimerFunc(25, update, 0);

    myInit();
    glutMainLoop();
    return 1;
}