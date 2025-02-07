#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

// Global variable to track the teapot's position along the z-axis
float teapotPosZ = -10.0f;
// Speed at which the teapot moves along the z-axis
float teapotSpeed = 0.05f;
float rotationAngle = 0.0f;  // Angle for rotation
float colorChangeSpeed = 0.01f; // Speed for color change
float timeElapsed = 0.0f;
float red = 0.0f, green = 0.0f, blue = 1.0f;  // Initial RGB color (blue)

void changeSize(int w, int h)
{
    if (h == 0)
        h = 1;
    float ratio = w * 1.0f / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the perspective with a 45-degree field of view
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

    // Return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);

    // Set the viewport to cover the new window
    glViewport(0, 0, w, h);
}

void renderScene(void)
{
    // Update teapot's position: move forward and backward
    teapotPosZ += teapotSpeed;

    // If the teapot reaches the front or back limit, reverse direction
    if (teapotPosZ >= 1.0f || teapotPosZ <= -10.0f)
    {
        teapotSpeed = -teapotSpeed; // Reverse the movement direction
    }

     // Update rotation angle (rotate the teapot over time)
    rotationAngle += 0.5f;  // Adjust this value to control the speed of rotation
    if (rotationAngle > 360.0f) {
        rotationAngle -= 360.0f;  // Keep the angle within 0-360 degrees
    }

    // Change the color dynamically by modifying the RGB values
    red = (sin(timeElapsed) + 1.0f) / 2.0f;   // Generates a value between 0 and 1
    green = (sin(timeElapsed + 2.0f) + 1.0f) / 2.0f; // Offset by 2 for smooth color cycling
    blue = (sin(timeElapsed + 4.0f) + 1.0f) / 2.0f; // Offset by 4 for different timing
    timeElapsed += colorChangeSpeed;


    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Reset model view matrix and set camera
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 5.0f,   // Camera position
              0.0f, 0.0f, -1.0f,  // Look-at point
              0.0f, 1.0f, 0.0f);  // Up vector

    // Save the current transformation state
    glPushMatrix();
    // Apply translation to move the teapot along the z-axis
    glTranslatef(0.0f, 0.0f, teapotPosZ);
    // Apply rotation to the teapot
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);  // Rotate on the y-axis

    // Set the teapot's color using dynamic RGB values
    glColor3f(red, green, blue);
    // Draw the teapot
    glutWireTeapot(1.0);
    // Restore the previous transformation state
    glPopMatrix();
    
    // Swap buffers (double buffering)
    glutSwapBuffers();
}

void printInfo() {
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version: %s\n", glGetString(GL_VERSION));
}

int main(int argc, char** argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI");

    // Register callbacks
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutDisplayFunc(renderScene);

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Optionally print out some info about the graphics card
    printInfo();

    // Enter the GLUT main loop
    glutMainLoop();

    return 1;
}
