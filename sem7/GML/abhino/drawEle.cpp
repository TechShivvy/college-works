#include <GL/glut.h>
#include <vector>

std::vector<GLfloat> vertices = {
    -1.0f, -1.0f, 0.0f,  // Vertex 1
    1.0f, -1.0f, 0.0f,   // Vertex 2
    0.0f, 1.0f, 0.0f     // Vertex 3
};

std::vector<GLuint> indices = {
    0, 1, 2  // Indices of the vertices forming a triangle
};

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Specify the vertex array
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices.data());

    // Draw the indexed geometry
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, indices.data());

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
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("OpenGL glDrawElements Example");
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
