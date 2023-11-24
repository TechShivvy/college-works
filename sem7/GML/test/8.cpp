// if usin perspective, use small values for all funcs
// if ortho, meh, use relatively larger

#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>

#define vf vector<GLfloat>
#define vvf vector<vf>
#define X 0
#define Y 1
#define Z 2

using namespace std;

GLenum GL_CUBE = 9999;

GLboolean ortho = true; // try toggling

GLfloat SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 1000, angle = 0.0f;

vvf vertices = {
    {0, 5, 5, 0, 0, 5, 5, 0},  // x coordinates
    {0, 0, 0, 0, 5, 5, 5, 5},  // y coordinates
    {0, 0, 5, 5, 0, 0, 5, 5},  // z coordinates
    {1, 1, 1, 1, 1, 1, 1, 1}}; // h

vf indices = {
    0, 1, 2, 3, // bottom
    4, 5, 6, 7, // top
    0, 4, 5, 1, // back
    1, 5, 6, 2, // right
    2, 6, 7, 3, // front
    3, 7, 4, 0  // left
};

vf colors = {
    1, 0, 0, // Bottom face (red)
    0, 1, 0, // Top face (green)
    0, 0, 1, // Back face (blue)
    1, 1, 0, // Right face (yellow)
    0, 1, 1, // Front face (cyan)
    1, 0, 1  // Left face (magenta)
};

void displayMat(vvf res)
{
    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[0].size(); j++)
            cout << res[i][j] << " ";
        cout << ";" << endl;
    }
}

vvf multiply(vvf a, vvf b)
{
    vvf c(a.size(), vf(b[0].size(), 0));
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < b[0].size(); j++)
            for (int k = 0; k < b.size(); k++)
                c[i][j] += a[i][k] * b[k][j];
    return c;
}

vvf translate(vvf P, int tx, int ty, int tz)
{
    vvf T(4, vf(4, 0));
    for (int i = 0; i < 4; i++)
        T[i][i] = 1;
    T[0][3] = tx;
    T[1][3] = ty;
    T[2][3] = tz;
    return multiply(T, P);
}

vvf rotate(vvf P, int axis, int deg)
{
    vvf R(4, vf(4, 0));

    R[3][3] = 1;
    R[0][0] = R[1][1] = R[2][2] = cos(M_PI * deg / 180);
    R[axis][axis] = 1;

    R[!axis][(axis != 2) + 1] = R[(axis != 2) + 1][!axis] = sinf(M_PI * deg / 180);
    if (axis != Y)
        R[!axis][(axis != 2) + 1] *= -1;
    else
        R[(axis != 2) + 1][!axis] *= -1;

    return multiply(R, P);
}

vvf scale(vvf P, int sx, int sy, int sz)
{
    vvf S(4, vf(4, 0));
    S[0][0] = sx;
    S[1][1] = sy;
    S[2][2] = sz;
    S[3][3] = 1;
    return multiply(S, P);
}

vvf shear(vvf P, int xy, int xz, int yx, int yz, int zx, int zy)
{
    vvf S(4, vf(4, 0));
    for (int i = 0; i < 4; i++)
        S[i][i] = 1;
    S[1][0] = xy;
    S[2][0] = xz;
    S[0][1] = yx;
    S[2][1] = yz;
    S[0][2] = zx;
    S[1][2] = zy;
    return multiply(S, P);
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

void drawFig(GLenum mode, vvf vertices)
{
    if (mode == GL_CUBE)
    {
        // glRotatef(angle, 0, 1, 1);
        // only edges
        for (int i = 0; i < indices.size(); i++)
        {
            glColor3f(0.5, 0, 0);
            int j = indices[i];
            if (i % 4 == 0)
                glBegin(GL_LINE_LOOP);
            glVertex3f(vertices[0][j], vertices[1][j], vertices[2][j]);
            if (i % 4 == 3)
                glEnd();
        }

        // faces
        for (int i = 0; i < indices.size(); i++)
        {
            int j = indices[i];
            if (i % 4 == 0)
            {
                glColor3fv(&colors[(i / 4) * 3]);
                glBegin(GL_QUADS);
            }
            glVertex3f(vertices[0][j], vertices[1][j], vertices[2][j]);
            if (i % 4 == 3)
                glEnd();
        }
    }
}

void inbuiltCube()
{
    // inbuilt cube
    glPushMatrix();
    (!ortho) ? glTranslatef(8, 8, 0) : glTranslatef(10, 10, 0);
    glColor3f(1, 1, 0);
    glutSolidCube(!ortho ? 2 : 10); // o
    glPopMatrix();
}

void userDefinedCube1()
{
    // custom cube points
    glPushMatrix();
    drawFig(GL_CUBE, vertices); // pls see line 15
    glPopMatrix();
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
    (!ortho) ? gluPerspective(45.0f, ratio, 0.1f, 100.0f) : glOrtho(-0.1 * width / 5, 0.1 * width / 5 , -0.1 * height / 5 , 0.1 * height / 5 , 0.1, 100.0);

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

    (!ortho) ? gluPerspective(45.0f, 1.0f, 0.1f, 100.0f) : glOrtho(-25, 25, -25, 25, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(15, 15, 15, 0, 0, 0, 0, 1, 0);
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawAxes();

    inbuiltCube();
    userDefinedCube1();

    drawFig(GL_CUBE, rotate(translate(vertices, 8, 0, 0), X, angle));
    // drawFig(GL_CUBE, rotate(rotate(vertices, Z, angle), X, angle));
    // drawFig(GL_CUBE, scale(vertices, 2, 1, 1));
    // drawFig(GL_CUBE, shear(vertices, 0, 0, 2, 2, 0, 0));
    glutSwapBuffers();
}

void update(int value)
{
    angle += 1.0f;
    if (angle > 360.0f)
        angle -= 360.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);

    glutCreateWindow("3d basics");
    glutDisplayFunc(myDisplay);
    // glutReshapeFunc(myReshape);
    glutTimerFunc(25, update, 0);

    myInit();
    glutMainLoop();
    return 1;
}

void drawText(double x, double y, double z, string str, int a = 0, int b = 0, int c = 0)
{
    string text = "(" + to_string(x) + "," + to_string(y) + ")";

    text = str;
    // stringstream ss;
    // ss << "(" << fixed << setprecision(0) << x + a << ","
    //    << y + b << "," << z + c << ")";
    // string text = ss.str();
    glColor3f(1, 1, 1);
    glRasterPos3d(x + a, y + b, z + c);

    for (char c : text)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, int(c));
}