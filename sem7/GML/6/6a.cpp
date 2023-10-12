#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#define pi 3.142857

void mm(double m[3][3], double v[3])
{
    for (int i = 0; i < 3; ++i)
    {
        double temp = 0;
        for (int k = 0; k < 3; ++k)
            temp += m[i][k] * v[k];
        v[i] = temp;
    }
}
int X = 100, Y = -50;
void draw_pixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}
void output(int x, int y, const char *str)
{

    glRasterPos2f(x, y);
    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
    }
}

void obj(int a, int b, int c, int d, int w, int x, int y, int z)
{
    glBegin(GL_QUADS);
    glVertex2d(a, b);
    glVertex2d(c, d);
    glVertex2d(w, x);
    glVertex2d(y, z);

    glEnd();
}
void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(0.0, 1.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-780, 780, -420, 420);
}

void translation(double x1[], double x2[], double x3[], double x4[])
{
    // TRANSLATION

    double T[3][3] = {{1, 0, 150}, {0, 1, 150}, {0, 0, 1}};
    mm(T, x1);
    mm(T, x2);
    mm(T, x3);
    mm(T, x4);

    obj(x1[0], x1[1], x2[0], x2[1], x3[0], x3[1], x4[0], x4[1]);
    output(260, 360, "translatedA:");
}

void rotation(double x1[], double x2[], double x3[], double x4[])
{
    // ROTATION
    double R[3][3] = {{cos(pi / 4), -sin(pi / 4), 0}, {sin(pi / 4), cos(pi / 4), 0}, {0, 0, 1}};

    mm(R, x1);
    mm(R, x2);
    mm(R, x3);
    mm(R, x4);
    printf("%lf%lf%lf%lf%lf%lf%lf%lf", x1[0], x1[1], x2[0], x2[1], x3[0], x3[1], x4[0], x4[1]);
    obj(x1[0], x1[1], x4[0], x4[1], x3[0], x3[1], x2[0], x2[1]);
    output(10, 300, "rotatedA:");
    printf("%lf", cos(pi / 4));
}

void scaling(double x1[], double x2[], double x3[], double x4[])
{
    // SCALING

    glColor3f(1.0, 0.0, 1.0);
    double S[3][3] = {{2, 0, 0}, {0, 2, 0}, {0, 0, 1}};
    mm(S, x1);
    mm(S, x2);
    mm(S, x3);
    mm(S, x4);
    obj(x1[0], x1[1], x2[0], x2[1], x3[0], x3[1], x4[0], x4[1]);
    output(-200, -90, "scaledA:");
}

void reflection(double x1[], double x2[], double x3[], double x4[])
{
    // REFLECTION
    x1[2] = x2[2] = x3[2] = x4[2] = 1;

    double RY[3][3] = {{-1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    mm(RY, x1);
    mm(RY, x2);
    mm(RY, x3);
    mm(RY, x4);
    obj(x1[0], x1[1], x2[0], x2[1], x3[0], x3[1], x4[0], x4[1]);
    output(-200, 210, "reflectedYA:");
}

void shearing(double x1[], double x2[], double x3[], double x4[])
{
    // SHEARING

    double SX[3][3] = {{1, 2, 0}, {0, 1, 0}, {0, 0, 1}};
    mm(SX, x1);
    mm(SX, x2);
    mm(SX, x3);
    mm(SX, x4);
    printf("%lf%lf%lf%lf%lf%lf%lf%lf", x1[0], x1[1], x2[0], x2[1], x3[0], x3[1], x4[0], x4[1]);

    obj(x1[0], x1[1], x2[0], x2[1], x3[0], x3[1], x4[0], x4[1]);
    output(500, 210, "ShearedXA:");
}

void display(void)
{
    double x1[3];
    double x2[3];
    double x3[3];
    double x4[3];
    x1[2] = x2[2] = x3[2] = x4[2] = 1;
    x1[0] = 100;
    x1[1] = 100;
    x2[0] = 200;
    x2[1] = 100;
    x3[0] = 200;
    x3[1] = 200;
    x4[0] = 100;
    x4[1] = 200;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2d(0, 420);
    glVertex2d(0, -420);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(780, 0);
    glVertex2d(-780, 0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    obj(x1[0], x1[1], x2[0], x2[1], x3[0], x3[1], x4[0], x4[1]);
    output(110, 210, "originalA:");
    int firstOp, secondOp;
    printf("Enter first operation (1-5) for transl, rot, scale, refl, shearing respectively:");
    scanf("%d", &firstOp);
    printf("Enter second operation (1-5) for transl, rot, scale, refl, shearing respectively:");
    scanf("%d", &secondOp);

    switch (firstOp)
    {
    case 1:
        translation(x1, x2, x3, x4);
        break;
    case 2:
        rotation(x1, x2, x3, x4);
        break;
    case 3:
        scaling(x1, x2, x3, x4);
        break;
    case 4:
        reflection(x1, x2, x3, x4);
        break;
    default:
        shearing(x1, x2, x3, x4);
    }

    switch (secondOp)
    {
    case 1:
        translation(x1, x2, x3, x4);
        break;
    case 2:
        rotation(x1, x2, x3, x4);
        break;
    case 3:
        scaling(x1, x2, x3, x4);
        break;
    case 4:
        reflection(x1, x2, x3, x4);
        break;
    default:
        shearing(x1, x2, x3, x4);
    }

    glFlush();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Transformations");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();
}
