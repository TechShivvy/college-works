#include <GL/glut.h>
#include <SOIL/SOIL.h>

const int windowWidth = 800;
const int windowHeight = 600;

GLfloat angle = 0.0f; // Initial rotation angle

// Texture variables
GLuint textureID;

// Rotation angles
float angleX = 0.0f;
float angleY = 0.0f;

// Texture coordinates
float texCoordX = 0.0f;
float texCoordY = 0.0f;

void init2()
{
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D
    glEnable(GL_LIGHTING);   // Enable lighting
    glEnable(GL_LIGHT0);     // Use light source 0

    GLfloat light_position[] = {1.0f, 1.0f, 1.0f, 0.0f}; // Light position
    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};  // Light color
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    glEnable(GL_TEXTURE_2D); // Enable texture mapping

    // Load and bind texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Load texture image using SOIL (replace "texture.jpg" with your actual image file)
    int width, height;
    unsigned char *image = SOIL_load_image("./texture2.jpg", &width, &height, 0, SOIL_LOAD_RGB);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glShadeModel(GL_FLAT); // Set shading model to flat
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    // Load texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    int width, height;
    unsigned char *image = SOIL_load_image("texture1.jpg", &width, &height, 0, SOIL_LOAD_RGB);
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



// void drawCube()
// {
//     glutSolidCube(1.0); // Draw a solid cube
// }

// void drawSphere()
// {
//     glutSolidSphere(0.5, 20, 20); // Draw a solid sphere
// }

// void drawCylinder()
// {
//     GLUquadricObj *cylinder = gluNewQuadric();
//     gluQuadricDrawStyle(cylinder, GLU_FILL);
//     gluCylinder(cylinder, 0.5, 0.5, 1.0, 20, 20); // Draw a cylinder
//     gluDeleteQuadric(cylinder);
// }

// void drawTorus()
// {
//     glutSolidTorus(0.3, 0.7, 20, 20); // Draw a solid torus
// }

void drawCube()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID); // Bind the texture

    glBegin(GL_QUADS);

    // Front face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5, 0.5, 0.5);

    // Back face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5, 0.5, -0.5);

    // Right face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.5, 0.5, 0.5);

    // Left face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.5, 0.5, 0.5);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5, 0.5, -0.5);

    // Top face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5, 0.5, 0.5);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5, 0.5, -0.5);

    // Bottom face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5, -0.5, 0.5);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}


void drawSphere()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID); // Bind the texture

    GLUquadricObj *sphere = gluNewQuadric();
    gluQuadricTexture(sphere, GL_TRUE);

    gluSphere(sphere, 0.5, 20, 20);

    gluDeleteQuadric(sphere);
    glDisable(GL_TEXTURE_2D);
}

void drawCylinder()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID); // Bind the texture

    GLUquadricObj *cylinder = gluNewQuadric();
    gluQuadricTexture(cylinder, GL_TRUE);

    gluCylinder(cylinder, 0.5, 0.5, 1.0, 20, 20);

    gluDeleteQuadric(cylinder);
    glDisable(GL_TEXTURE_2D);
}

void drawTorus()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID); // Bind the texture

    glutSolidTorus(0.3, 0.7, 20, 20);

    glDisable(GL_TEXTURE_2D);
}

void display()
{
    glViewport(0, 0, windowWidth, windowHeight); // Set the viewport size

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, static_cast<double>(windowWidth) / windowHeight, 0.1, 100.0); // Adjusted near and far planes

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Adjusted camera position

    glTranslatef(0.0f, 0.0f, -5.0f);    // Move the scene back along the z-axis
    glRotatef(angle, 1.0f, 1.0f, 0.0f); // Rotate around the x and y-axis

    // Apply material properties (color, etc.)
    GLfloat material_diffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);

    // Draw 3D objects
    drawCube(); // Draw a cube
    glTranslatef(2.0f, 0.0f, 0.0f);
    drawSphere(); // Draw a sphere
    glTranslatef(-4.0f, -2.0f, 0.0f);
    drawCylinder(); // Draw a cylinder
    glTranslatef(4.0f, -2.0f, 0.0f);
    drawTorus(); // Draw a torus

    glutSwapBuffers();
}

void update(int value)
{
    angle += 2.0f; // Update rotation angle
    if (angle > 360)
    {
        angle -= 360; // Keep the angle within 0 to 360 degrees
    }

    glutPostRedisplay();          // Trigger a redraw
    glutTimerFunc(16, update, 0); // Call update function every 16 milliseconds
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight); // Set window size
    glutCreateWindow("OpenGL 3D Scene");

    // Add these lines for proper initialization
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);

    init();

    glutMainLoop();
    return 0;
}
