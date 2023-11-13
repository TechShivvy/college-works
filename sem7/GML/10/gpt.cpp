#include <iostream>
#include <SOIL/SOIL.h>
#include <GL/glut.h>

// Texture variables
GLuint textureID;

// Rotation angles
float angleX = 0.0f;
float angleY = 0.0f;

// Texture coordinates
float texCoordX = 0.0f;
float texCoordY = 0.0f;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    // Load texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    int width, height;
    unsigned char *image = SOIL_load_image("texture2.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Enable lighting and set light parameters
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    // Enable texture and set shading model
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_FLAT);

    // Set up perspective projection
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0f, 1.0f, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Apply transformations
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    // Draw a cube with texture
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f + texCoordX, 0.0f + texCoordY);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f + texCoordX, 0.0f + texCoordY);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f + texCoordX, 1.0f + texCoordY);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f + texCoordX, 1.0f + texCoordY);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    glTexCoord2f(0.0f + texCoordX, 0.0f + texCoordY);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f + texCoordX, 0.0f + texCoordY);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f + texCoordX, 1.0f + texCoordY);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f + texCoordX, 1.0f + texCoordY);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    glTexCoord2f(0.0f + texCoordX, 0.0f + texCoordY);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f + texCoordX, 0.0f + texCoordY);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f + texCoordX, 1.0f + texCoordY);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f + texCoordX, 1.0f + texCoordY);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    glTexCoord2f(0.0f + texCoordX, 0.0f + texCoordY);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f + texCoordX, 0.0f + texCoordY);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f + texCoordX, 1.0f + texCoordY);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f + texCoordX, 1.0f + texCoordY);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    glTexCoord2f(0.0f + texCoordX, 0.0f + texCoordY);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f + texCoordX, 0.0f + texCoordY);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f + texCoordX, 1.0f + texCoordY);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f + texCoordX, 1.0f + texCoordY);
    glVertex3f(1.0f, -1.0f, -1.0f);

    glTexCoord2f(0.0f + texCoordX, 0.0f + texCoordY);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f + texCoordX, 0.0f + texCoordY);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f + texCoordX, 1.0f + texCoordY);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f + texCoordX, 1.0f + texCoordY);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glEnd();

    glutSwapBuffers();
}

void update(int value)
{
    // Animation update
    angleX += 1.0f;
    angleY += 1.0f;
    texCoordX += 0.01f;
    texCoordY += 0.01f;

    if (texCoordX > 1.0f)
        texCoordX = 0.0f;
    if (texCoordY > 1.0f)
        texCoordY = 0.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // 60 FPS
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("OpenGL 3D Animation");
    glutInitWindowSize(800, 600);

    init();
    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);
    glutMainLoop();

    return 0;
}
