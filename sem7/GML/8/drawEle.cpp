#include <GL/glut.h>
#include <vector>

std::vector<GLfloat> vertices = {
    0, 0, 0,
    5, 0, 0,
    5, 0, 5,
    0, 0, 5,
    0, 5, 0,
    5, 5, 0,
    5, 5, 5,
    0, 5, 5
};

std::vector<GLuint> indices = {
    0, 1, 2, 3, // Bottom face
    4, 5, 6, 7, // Top face
    0, 4, 5, 1, // Front face
    1, 5, 6, 2, // Right face
    2, 6, 7, 3, // Back face
    3, 7, 4, 0  // Left face
};

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices.data());

    // Draw faces
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, 1.0);

    glColor3f(1.0, 0.0, 0.0); // Red color for the bottom face
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, indices.data());

    glColor3f(0.0, 1.0, 0.0); // Green color for the top face
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, indices.data() + 4);

    glColor3f(0.0, 0.0, 1.0); // Blue color for the front face
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, indices.data() + 8);

    glColor3f(1.0, 1.0, 0.0); // Yellow color for the right face
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, indices.data() + 12);

    glColor3f(1.0, 0.0, 1.0); // Magenta color for the back face
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, indices.data() + 16);

    glColor3f(0.0, 1.0, 1.0); // Cyan color for the left face
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, indices.data() + 20);

    // Draw edges
    glDisable(GL_POLYGON_OFFSET_FILL);
    glColor3f(1.0, 1.0, 1.0); // Black color for the edges
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, indices.data());
    glDisableClientState(GL_VERTEX_ARRAY);

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(8.0, 8.0, 20.0, 2.5, 2.5, 2.5, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("OpenGL Cube Example");
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
