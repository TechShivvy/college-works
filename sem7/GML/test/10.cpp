#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;

GLfloat ambient[] = {1, 1, 1, 0};
GLfloat specular[] = {1, 1, 1, 0};
GLfloat diffuse[] = {1, 1, 1, 0};

GLfloat light_position[] = {1, 1, 1, 0};

GLfloat shininess[] = {100};
float inc = 0.2f, y = 0.0f;
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

    gluLookAt(5, 5, 0, 0, 0, 0, 0, 1, 0);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_FLAT);
}

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

void lightAndTexture()
{
    glPushMatrix();

    light_position[1] = sin(y * 45.0 * M_PI / 180.0);
    light_position[2] = cos(y * 45.0 * M_PI / 180.0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glPopMatrix();
}

void drawSphere()
{
    glPushMatrix();
    glTranslatef(0, y, 0);
    glutSolidSphere(1, 100, 100);
    glPopMatrix();
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    lightAndTexture();
    drawSphere();

    glutSwapBuffers();
}

void update(int val)
{
    if (y > 3 || y < -3)
        inc = (inc < 0 ? 1 : -1) * 0.2;
    y += inc;
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);

    glutCreateWindow("Lighting and textures");
    glutDisplayFunc(myDisplay);
    glutTimerFunc(25, update, 0);

    myInit();
    glutMainLoop();
    return 1;
}