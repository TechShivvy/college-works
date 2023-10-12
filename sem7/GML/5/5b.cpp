#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<string.h>
#define pi 3.142857
void mm(double m[3][3], double v[3]){
	for(int i = 0; i < 3; ++i){
    	double temp=0;
    	for(int k = 0; k < 3; ++k)
        	temp += m[i][k] * v[k];
    	v[i]=temp;
	}
}
void draw_pixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
void output(int x, int y, char *string)
{
 
  glRasterPos2f(x, y);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) {
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
  }
}
void obj(int a,int b, int c,int d,int w,int x,int y,int z){
	glBegin(GL_QUADS);
	glVertex2d(a,b);
	glVertex2d(c,d);
	glVertex2d(w,x);
	glVertex2d(y,z);
    
	glEnd();
}
void myInit (void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(0.0, 1.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-780, 780, -420, 420);
}
void display (void)
{
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
    
	//REFLECTION
	double x1[3];
	double x2[3];
	double x3[3];
	double x4[3];
	x1[2]=x2[2]=x3[2]=x4[2]=1;
	x1[0]=100;x1[1]=100;
	x2[0]=200;x2[1]=100;
	x3[0]=200;x3[1]=200;
	x4[0]=100;x4[1]=200;
	obj(x1[0],x1[1],x2[0],x2[1],x3[0],x3[1],x4[0],x4[1]);
	output(100,210,"originalA:");
	double RY[3][3]={{-1,0,0},{0,1,0},{0,0,1}};
	mm(RY,x1);mm(RY,x2);mm(RY,x3);mm(RY,x4);
	obj(x1[0],x1[1],x2[0],x2[1],x3[0],x3[1],x4[0],x4[1]);
	output(-200,210,"reflectedYA:");
	x1[0]=100;x1[1]=100;
	x2[0]=200;x2[1]=100;
	x3[0]=200;x3[1]=200;
	x4[0]=100;x4[1]=200;
	double RX[3][3]={{1,0,0},{0,-1,0},{0,0,1}};
	mm(RX,x1);mm(RX,x2);mm(RX,x3);mm(RX,x4);
	obj(x1[0],x1[1],x2[0],x2[1],x3[0],x3[1],x4[0],x4[1]);
	output(160,-90,"reflectedXA:");
	x1[0]=100;x1[1]=100;
	x2[0]=200;x2[1]=100;
	x3[0]=200;x3[1]=200;
	x4[0]=100;x4[1]=200;
	double RXY[3][3]={{-1,0,0},{0,-1,0},{0,0,1}};
	mm(RXY,x1);mm(RXY,x2);mm(RXY,x3);mm(RXY,x4);
	obj(x1[0],x1[1],x2[0],x2[1],x3[0],x3[1],x4[0],x4[1]);
	output(-200,-90,"reflectedXYA:");
    
	//SHEARING
	x1[0]=100;x1[1]=100;
	x2[0]=200;x2[1]=100;
	x3[0]=200;x3[1]=200;
	x4[0]=100;x4[1]=200;
	double SX[3][3]={{1,2,0},{0,1,0},{0,0,1}};
	mm(SX,x1);mm(SX,x2);mm(SX,x3);mm(SX,x4);
	obj(x1[0],x1[1],x2[0],x2[1],x3[0],x3[1],x4[0],x4[1]);
	output(500,210,"ShearedXA:");
	glColor3f(1.0, 0.0, 1.0);
	x1[0]=100;x1[1]=100;
	x2[0]=200;x2[1]=100;
	x3[0]=200;x3[1]=200;
	x4[0]=100;x4[1]=200;
	double SY[3][3]={{1,0,0},{-2,1,0},{0,0,1}};
	mm(SY,x1);mm(SY,x2);mm(SY,x3);mm(SY,x4);
	obj(x1[0],x1[1],x2[0],x2[1],x3[0],x3[1],x4[0],x4[1]);
	output(100,10,"ShearedYA:");
	glFlush();
}
int main (int argc, char** argv)
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
