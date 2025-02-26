#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <vector>

// Global variables for transformations
float translateX = 0.0f, translateY = 0.0f, translateZ = 0.0f;
float rotateAngleX = 0.0f, rotateAngleY = 0.0f, rotateAngleZ = 0.0f;
float scaleX = 1.0f, scaleY = 1.0f, scaleZ = 1.0f;
float colorR = 1.0f, colorG = 1.0f, colorB = 1.0f;

// Global variables for VBOs
GLuint pyramidVBO, pyramidColorVBO;
GLuint baseVBO, baseColorVBO;

void changeSize(int w, int h) {
    if(h == 0)
        h = 1;
    float ratio = w * 1.0 / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void setupVBOs() {
    // Pyramid vertices (excluding base)
    std::vector<float> pyramidVertices = {
        // Front face
        0.0f, 1.0f, 0.0f,
        -0.5f, 0.0f, 0.5f,
        0.5f, 0.0f, 0.5f,
        // Right face
        0.0f, 1.0f, 0.0f,
        0.5f, 0.0f, 0.5f,
        0.5f, 0.0f, -0.5f,
        // Back face
        0.0f, 1.0f, 0.0f,
        0.5f, 0.0f, -0.5f,
        -0.5f, 0.0f, -0.5f,
        // Left face
        0.0f, 1.0f, 0.0f,
        -0.5f, 0.0f, -0.5f,
        -0.5f, 0.0f, 0.5f
    };

    std::vector<float> pyramidColors = {
        // Front face (Red)
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        // Right face (Green)
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        // Back face (Blue)
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        // Left face (Yellow)
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f
    };

    // Base vertices
    std::vector<float> baseVertices = {
        -0.5f, 0.0f, 0.5f,
        0.5f, 0.0f, -0.5f,
        -0.5f, 0.0f, -0.5f,
        -0.5f, 0.0f, 0.5f,
        0.5f, 0.0f, 0.5f,
        0.5f, 0.0f, -0.5f
    };

    std::vector<float> baseColors(18, 0.5f); // 6 vertices * 3 components, all grey

    // Create and bind pyramid VBO
    glGenBuffers(1, &pyramidVBO);
    glBindBuffer(GL_ARRAY_BUFFER, pyramidVBO);
    glBufferData(GL_ARRAY_BUFFER, pyramidVertices.size() * sizeof(float), pyramidVertices.data(), GL_STATIC_DRAW);

    // Create and bind pyramid color VBO
    glGenBuffers(1, &pyramidColorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, pyramidColorVBO);
    glBufferData(GL_ARRAY_BUFFER, pyramidColors.size() * sizeof(float), pyramidColors.data(), GL_STATIC_DRAW);

    // Create and bind base VBO
    glGenBuffers(1, &baseVBO);
    glBindBuffer(GL_ARRAY_BUFFER, baseVBO);
    glBufferData(GL_ARRAY_BUFFER, baseVertices.size() * sizeof(float), baseVertices.data(), GL_STATIC_DRAW);

    // Create and bind base color VBO
    glGenBuffers(1, &baseColorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, baseColorVBO);
    glBufferData(GL_ARRAY_BUFFER, baseColors.size() * sizeof(float), baseColors.data(), GL_STATIC_DRAW);
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(5.0f, 5.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    // Draw axes
    glBegin(GL_LINES);
    // X-axis (Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);
    // Y-axis (Green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    // Z-axis (Blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();

    // Apply transformations for the pyramid
    glPushMatrix();
    glTranslatef(translateX, translateY, translateZ);
    glRotatef(rotateAngleX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotateAngleY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotateAngleZ, 0.0f, 0.0f, 1.0f);
    glScalef(scaleX, scaleY, scaleZ);

    // Draw pyramid faces
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    // Draw pyramid sides
    glBindBuffer(GL_ARRAY_BUFFER, pyramidVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, pyramidColorVBO);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 12);

    // Draw base
    glBindBuffer(GL_ARRAY_BUFFER, baseVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, baseColorVBO);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glPopMatrix();

    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': translateY += 0.1f; break;
        case 's': translateY -= 0.1f; break;
        case 'a': translateX -= 0.1f; break;
        case 'd': translateX += 0.1f; break;
        case 'q': translateZ += 0.1f; break;
        case 'e': translateZ -= 0.1f; break;
        case 'r': rotateAngleY += 5.0f; break;
        case 'f': rotateAngleY -= 5.0f; break;
        case 'x': rotateAngleX += 5.0f; break;
        case 'z': rotateAngleX -= 5.0f; break;
        case 'c': rotateAngleZ += 5.0f; break;
        case 'v': rotateAngleZ -= 5.0f; break;
        case 't': scaleX += 0.1f; scaleY += 0.1f; scaleZ += 0.1f; break;
        case 'g': scaleX -= 0.1f; scaleY -= 0.1f; scaleZ -= 0.1f; break;
        case '1': colorR = 1.0f; colorG = 0.0f; colorB = 0.0f; break;
        case '2': colorR = 0.0f; colorG = 1.0f; colorB = 0.0f; break;
        case '3': colorR = 0.0f; colorG = 0.0f; colorB = 1.0f; break;
        case '4': colorR = 1.0f; colorG = 1.0f; colorB = 1.0f; break;
        case 27: exit(0); break; // ESC key
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI-UM");

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutKeyboardFunc(processNormalKeys);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    setupVBOs(); // Add this line to initialize VBOs

    glutMainLoop();

    return 1;
}