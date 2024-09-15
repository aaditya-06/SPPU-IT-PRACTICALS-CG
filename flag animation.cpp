#include<GL/glut.h>
#include<iostream>
#include<cmath>

using namespace std;

#define w 1300
#define h 1300


int flagPosition = 450; // Initial position of the flag
bool flagMovingDown = true; // Flag to indicate if the flag is moving down or not

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(3.0);
    glLineWidth(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void drawPole()
{
    glLineWidth(5.0);
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5); // Gray color for the pole
    glVertex2i(-10, -250);
    glVertex2i(-10, 550);
    glVertex2i(10, 550);
    glVertex2i(10, -250);
    glEnd();
}

void drawBase()
{
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5); // Gray color for the base
    glVertex2i(-350, -600);
    glVertex2i(-350, -425);
    glVertex2i(350, -425);
    glVertex2i(350, -600);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5); // Gray color for second base
    glVertex2i(-100, -425);
    glVertex2i(-100, -250);
    glVertex2i(100, -250);
    glVertex2i(100, -425);
    glEnd();
}

void drawFlag()
{
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.6, 0.2); // Saffron color
    glVertex2f(10, flagPosition);
    glVertex2f(350, flagPosition);
    glVertex2f(350, flagPosition - 100);
    glVertex2f(10, flagPosition - 100);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0); // White color
    glVertex2f(10, flagPosition - 101);
    glVertex2f(350, flagPosition - 101);
    glVertex2f(350, flagPosition - 201);
    glVertex2f(10, flagPosition - 201);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.8, 0.0); // Green color
    glVertex2f(10, flagPosition - 202);
    glVertex2f(350, flagPosition - 202);
    glVertex2f(350, flagPosition - 302);
    glVertex2f(10, flagPosition - 302);
    glEnd();


}

void drawBackground()
{
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.8, 1.0); // Light blue color for the sky
    glVertex2i(-w / 2, h / 2);
    glVertex2i(-w / 2, -250);
    glVertex2i(w / 2, -250);
    glVertex2i(w / 2, h / 2);
    glEnd();
}

void drawMountains()
{
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.4, 0.0); // Dark green color for mountains

    // First mountain
    glVertex2i(-700, -250);
    glVertex2i(-500, -250);
    glVertex2i(-600, 50);

    // Second mountain
    glVertex2i(-400, -250);
    glVertex2i(-200, -250);
    glVertex2i(-300, 100);

    // Third mountain
    glVertex2i(100, -250);
    glVertex2i(300, -250);
    glVertex2i(200, 150);

    // Fourth mountain
    glVertex2i(400, -250);
    glVertex2i(600, -250);
    glVertex2i(500, 200);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawBackground();
    drawMountains();
    drawPole();
    drawBase();
    drawFlag();
    glFlush();
}

void timer(int value)
{
    if (flagMovingDown)
    {
        flagPosition -= 1; // Move the flag down

        // Check if the flag has reached the bottom of the pole
        if (flagPosition <= -250)
        {
            flagMovingDown = false; // Stop the flag from moving down
        }
    }
    else
    {
        flagPosition += 1; // Move the flag up

        // Check if the flag has reached the top of the pole
        if (flagPosition >= 450)
        {
            flagMovingDown = true; // Start the flag moving down again
        }
    }

    glutPostRedisplay(); // Mark the window for redisplay

    // Set the timer function to be called again after 10 milliseconds
    glutTimerFunc(10, timer, 0);
}
int main(int argc, char** argv){
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("India Flag Hoisting");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(10, timer, 0); // Start the timer function
    glutMainLoop();
    return 0;
}
