#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <stdio.h>
#define pi M_PI

using namespace std;
void myInit()
{
    glClearColor(0.5, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-320.0, 320.0, -240.0, 240.0);
}
vector<vector<float>> translation()
{
    float tx, ty;
    cout << "Enter tx, ty: ";
    cin >> tx >> ty;
    vector<vector<float>> translate(3, vector<float>(3, 0.0));
    (translate)[0][0] = 1;
    (translate)[0][2] = tx;
    (translate)[1][1] = 1;
    (translate)[1][2] = ty;
    (translate)[2][2] = 1;
    return translate;
}
vector<vector<float>> rotate()
{
    float deg;
    cout << "Enter deg: ";
    cin >> deg;
    vector<vector<float>> rotate(3, vector<float>(3, 0.0));
    deg *= M_PI / 180;
    cout << deg << " : deg" << endl;
    rotate[0][0] = cos(deg);
    rotate[0][1] = -sin(deg);
    rotate[1][0] = sin(deg);
    rotate[1][1] = cos(deg);
    rotate[2][2] = 1;
    // rotate[0][2] = tx*(1-cos(deg))+ty*sin(deg);
    // rotate[1][2] = ty*(1-cos(deg))-tx*sin(deg);
    return rotate;
}
vector<vector<float>> scale()
{
    float sx, sy;
    cout << "Enter sx, sy: ";
    cin >> sx >> sy;
    vector<vector<float>> scale(3, vector<float>(3, 0.0));
    scale[0][0] = sx;
    scale[1][1] = sy;
    scale[2][2] = 1;
    // scale[0][2] = tx * (1 - sx);
    // scale[1][2] = ty * (1 - sy);
    return scale;
}
vector<vector<float>> reflect()
{
    float axis;
    cout << "Enter option 1.x-axis 2.y-axis 3.origin 4.x=y (1/2/3/4): ";
    cin >> axis;
    vector<vector<float>> reflect(3, vector<float>(3, 0.0));
    reflect[0][0] = 1;
    reflect[1][1] = 1;
    reflect[2][2] = 1;
    if (axis == 1)
        reflect[1][1] = -1;
    else if (axis == 2)
        reflect[0][0] = -1;
    else if (axis == 3)
    {
        reflect[0][0] = -1;
        reflect[1][1] = -1;
    }
    else if (axis == 4)
    {
        reflect[0][1] = 1;
        reflect[0][0] = 0;
        reflect[1][0] = 1;
        reflect[1][1] = 0;
    }
    return reflect;
}
vector<vector<float>> shear()
{
    float op;
    cout << "Enter option 1.x-shear 2.y-shear (1/2): ";
    cin >> op;
    float sh, ref;
    if (op == 1)
        cout << "Enter shx, yref: ";
    else if (op == 2)
        cout << "Enter shy, xref: ";
    cin >> sh >> ref;
    vector<vector<float>> shear(3, vector<float>(3, 0.0));
    shear[0][0] = 1;
    shear[1][1] = 1;
    shear[2][2] = 1;
    if (op == 1)
    {
        shear[0][1] = sh;
        shear[0][2] = -sh * ref;
    }
    else if (op == 2)
    {
        shear[1][0] = sh;
        shear[1][2] = -sh * ref;
    }
    return shear;
}
vector<vector<float>> matrixMul(vector<vector<float>> t1,
                                vector<vector<float>> t2, vector<vector<float>> res, int n)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < n; j++)
        {
            res[i][j] = 0;
            for (int k = 0; k < 3; k++)
            {
                res[i][j] += t1[i][k] * t2[k][j];
            }
        }
    }
    return res;
}
void matrixDisp(vector<vector<float>> m)
{
    cout << endl;
    for (auto arrp : m)
    {
        for (auto p : arrp)
        {
            cout << p << " ";
        }
        cout << endl;
    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int op1, op2;
    cout << "Enter any 2 tranformations:- \n1.translation \n2.rotation\n3.scaling \n4.reflection \n5.shearing(1 / 2 / 3 / 4 / 5) \ninc order(op1, op2) : ";
    cin >> op1 >> op2;
    vector<vector<float>> t1, t2;
    if (op1 == 1)
    {
        t1 = translation();
    }
    else if (op1 == 2)
    {
        t1 = rotate();
    }
    else if (op1 == 3)
    {
        t1 = scale();
    }
    else if (op1 == 4)
    {
        t1 = reflect();
    }
    else if (op1 == 5)
    {
        t1 = shear();
    }
    // for op2
    if (op2 == 1)
    {
        t2 = translation();
    }
    else if (op2 == 2)
    {
        t2 = rotate();
    }
    else if (op2 == 3)
    {
        t2 = scale();
    }
    else if (op2 == 4)
    {
        t2 = reflect();
    }
    else if (op2 == 5)
    {
        t2 = shear();
    }
    for (auto a : t1)
    {
        for (auto x : a)
        {
            cout << x << " ";
        }
        cout << endl;
    }
    for (auto a : t2)
    {
        for (auto x : a)
        {
            cout << x << " ";
        }
        cout << endl;
    }
    int n;
    cout << "Enter no. of points for polygon: ";
    cin >> n;
    // points matrix
    vector<vector<float>> points(3, vector<float>(n));
    for (int i = 0; i < n; i++)
    {
        cout << "Enter x, y coords: ";
        cin >> points[0][i] >> points[1][i];
        points[2][i] = 1;
    }
    // order for now is op1 then op2
    // result matrix
    vector<vector<float>> res(3, vector<float>(n));
    // t2 x t1
    res = matrixMul(t2, t1, res, 3);
    matrixDisp(res);
    // t21 x points
    res = matrixMul(res, points, res, n);
    matrixDisp(res);
    // axis
    glBegin(GL_LINES);
    glVertex2d(-320, 0);
    glVertex2d(320, 0);
    glVertex2d(0, -240);
    glVertex2d(0, 240);
    glEnd();
    // original shape
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++)
    {
        glVertex2f(points[0][i], points[1][i]);
    }
    glEnd();
    // result shape plot
    glRasterPos2i(res[0][n / 2], res[1][n / 2] - 15);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, int('S'));
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 0.0f, 0.0f);
    for (int i = 0; i < n; i++)
    {
        glVertex2f(res[0][i], res[1][i]);
    }
    glEnd();
    glFlush();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("ex6");
    glutDisplayFunc(display);
    myInit();
    glutMainLoop();
    return 0;
}