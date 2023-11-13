#include <GL/glut.h>
#include <SOIL/SOIL.h>

GLuint texture;

void displayCallback(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	  glEnable(GL_TEXTURE_2D);
	  glBindTexture(GL_TEXTURE_2D, texture);
	  glBegin(GL_QUADS);
	  glTexCoord2f(0, 0);			glVertex3f(200, 200, 0);
	  glTexCoord2f(1, 0);			glVertex3f(500, 200, 0);
	  glTexCoord2f(1, 1);			glVertex3f(500, 500, 0);
	  glTexCoord2f(0, 1);			glVertex3f(200, 500, 0);
	  glEnd();
	  glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Texture 2D");
	glutDisplayFunc(displayCallback);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	gluOrtho2D(0,600,0,600);
        texture = SOIL_load_OGL_texture("texture2.jpg", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB);
	glutMainLoop();
  return 0;
}