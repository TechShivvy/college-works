#include<stdio.h>
#include<GL/glut.h> //Change to <GLUT/glut.h> in Mac
#include<math.h>
#include<string.h>
#include<iostream>
using namespace std;
#define pi 3.142857
void display (void){
   
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //TEAPOT
  
    GLfloat diff[] = {1.0, 1.0, 0.0, 1.0};
    GLfloat spec[] = {0.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    glMaterialf(GL_FRONT, GL_SHININESS, 15.0);
    glutSolidTeapot(140);
    glColor3f(0.0,0.0,1.0);
    
    diff[0] = 0.0; diff[1] = 0.5; diff[2] = 1.0; diff[3] = 0.35;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    glMaterialf(GL_FRONT, GL_SHININESS, 15.0);
    GLUquadric *quad;
    quad = gluNewQuadric();
    glTranslatef(230,-10,200);
    gluSphere(quad,10,100,20);
    glFlush();
}
int main (int argc, char** argv){
    /*--------WINDOW INITS-------*/
    glutInit(&argc, argv); //Mandatory. Initializes the GLUT library.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1380, 700); //Set the size of output window (kinda optional)
    glutInitWindowPosition(200, 200); //position of output window on screen (optional)
    glutCreateWindow("3D scene");// Giving name to window
    /*-------OTHER INITS-------*/
    glClearColor(0.0, 0.0, 0.0, 1.0); //Clear the buffer values for color AND set these values
    /*can set initial color here also*/
    glMatrixMode(GL_PROJECTION);  //Uses something called "projection matrix" to represent
    glLoadIdentity(); //load the above matrix to fill with identity values
    glOrtho(-454.0, 454.0, -250.0, 250.0, -250.0, 250.0);
    gluPerspective(100, 100, 100, 100);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
   glutDisplayFunc(display); //sets the display callback for the current window
   glutMainLoop(); //Enters event processing loop. Compulsory
   return 0;
}
