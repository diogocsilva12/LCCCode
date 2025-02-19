#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

// Camera variables
float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;
float cameraDistance = 5.0f;

void changeSize(int w, int h) {
    if (h == 0)
        h = 1;

    float ratio = w * 1.0 / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);

    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
}

void drawCylinder(float radius, float height, int slices) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    float angleStep = 2 * M_PI / slices;
    float halfHeight = height / 2.0f;

    // Draw top cap
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, halfHeight, 0.0f);
    for (int i = 0; i <= slices; i++) {
        float angle = i * angleStep;
        glVertex3f(radius * cos(angle), halfHeight, radius * sin(angle));
    }
    glEnd();

    // Draw bottom cap
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, -halfHeight, 0.0f);
    for (int i = 0; i <= slices; i++) {
        float angle = i * angleStep;
        glVertex3f(radius * cos(angle), -halfHeight, radius * sin(angle));
    }
    glEnd();

    // Draw side surface
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= slices; i++) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        glVertex3f(x, halfHeight, z);
        glVertex3f(x, -halfHeight, z);
    }
    glEnd();
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // Calculate camera position
    float cameraX = cameraDistance * cos(cameraAngleY * M_PI / 180.0f) * sin(cameraAngleX * M_PI / 180.0f);
    float cameraY = cameraDistance * sin(cameraAngleY * M_PI / 180.0f);
    float cameraZ = cameraDistance * cos(cameraAngleY * M_PI / 180.0f) * cos(cameraAngleX * M_PI / 180.0f);

    gluLookAt(cameraX, cameraY, cameraZ,
              0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);

    drawCylinder(1, 2, 10);

    glutSwapBuffers();
}

void processKeys(unsigned char key, int xx, int yy) {
    switch (key) {
        case 'w':
        case 'W':
            cameraDistance -= 0.1f;
            if (cameraDistance < 1.0f) cameraDistance = 1.0f; // Prevent going too close
            break;
        case 's':
        case 'S':
            cameraDistance += 0.1f;
            break;
        case 'a':
        case 'A':
          cameraAngleX -= 2.0f;
          break;
        case 'd':
        case 'D':
          cameraAngleX += 2.0f;
          break;
    }
    glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_UP:
            cameraAngleY += 2.0f;
            break;
        case GLUT_KEY_DOWN:
            cameraAngleY -= 2.0f;
            break;
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

    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 1;
}