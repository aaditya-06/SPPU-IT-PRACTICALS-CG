#include <GL/gl.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

float angle = 0.0; // Initialize angle variable
float rotation_speed = -2; // Set rotation speed (degrees per frame)
float bx = 10;

void circle(GLfloat r, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = r * cos(angle);
        float y = r * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();

    // Inner circle (grey)
    glColor3ub(150, 150, 150); // Grey color for inner circle
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = (r - 4) * cos(angle); // Adjust the radius for inner circle
        float y = (r - 4) * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();

    // Draw spokes
    int num_spokes = 6; // Number of spokes
    glColor3ub(255,255,255); // White color for spokes
    for (int i = 0; i < num_spokes; ++i)
    {
        float angle_spoke = i * (360.0f / num_spokes) * 3.1416 / 180.0f;
        glBegin(GL_LINES);
        glVertex2f(cx, cy);
        // Calculate the endpoint on the inner circle instead of the outer circle
        float inner_x = (r - 4) * cos(angle_spoke);
        float inner_y = (r - 4) * sin(angle_spoke);
        glVertex2f(cx + inner_x, cy + inner_y);
        glEnd();
    }
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 500, 0.0, 500); // window size
}

void hills() {
    // Hills 1
    glColor3ub(184, 134, 11);
    glBegin(GL_POLYGON);
    glVertex2d(-40, 300);
    glVertex2d(200, 300);
    glVertex2d(100, 450);
    glEnd();

    // Hills 2
    glColor3ub(218, 165, 32);
    glBegin(GL_POLYGON);
    glVertex2d(150, 300);
    glVertex2d(350, 300);
    glVertex2d(250, 450);
    glEnd();

    // Hills 3
    glColor3ub(184, 134, 11);
    glBegin(GL_POLYGON);
    glVertex2d(300, 300); // Adjust x-coordinate for third hill
    glVertex2d(500, 300); // Adjust x-coordinate for third hill
    glVertex2d(400, 450); // Adjust y-coordinate for third hill
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the hills
    hills();

    //Ground Color (Green)
    glColor3ub(0, 255, 0);
    glBegin(GL_POLYGON);
    glVertex2d(0, 0);
    glVertex2d(500, 0);
    glVertex2d(500, 300); // Increase the height to cover a larger area
    glVertex2d(0, 300);
    glEnd();

    // Road
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2d(0, 100); // Lower the road position
    glVertex2d(500, 100);
    glVertex2d(500, 200); // Increase the height of the road
    glVertex2d(0, 200);
    glEnd();

    // Road Border
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(0, 110); // Lower the border position
    glVertex2d(500, 110);
    glVertex2d(500, 190); // Adjust the height of the border
    glVertex2d(0, 190);
    glEnd();

    glPushMatrix();
    glTranslatef(bx, 0, 0);

    // Enlarge the car
    glScalef(1.5, 1.5, 1.0); // Scale the car uniformly by a factor of 1.5

    // Car body
    glColor3ub(255, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(410, 100);
    glVertex2d(490, 100);
    glVertex2d(485, 130);
    glVertex2d(410, 130);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(420, 130);
    glVertex2d(475, 130);
    glVertex2d(465, 160);
    glVertex2d(430, 160);
    glEnd();

    // Car windows
    glColor3ub(220, 220, 220);
    glBegin(GL_POLYGON);
    glVertex2d(425, 130);
    glVertex2d(445, 130);
    glVertex2d(445, 150);
    glVertex2d(430, 150);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(450, 130);
    glVertex2d(470, 130);
    glVertex2d(465, 150);
    glVertex2d(450, 150);
    glEnd();

    // Car wheels
    glPushMatrix();
    glTranslatef(465, 100, 0);
    glRotatef(angle, 0, 0, 1); // Rotate the wheel
    glColor3ub(0, 0, 0); // Black color for wheel
    circle(14, 0, 0); // Use equal radii for perfect circle
    glPopMatrix();

    glPushMatrix();
    glTranslatef(430, 100, 0);
    glRotatef(angle, 0, 0, 1); // Rotate the wheel
    glColor3ub(0, 0, 0); // Black color for wheel
    circle(14, 0, 0); // Use equal radii for perfect circle
    glPopMatrix();

    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void timerFunc(int value) {
    angle += rotation_speed;
    bx += 1;
    if (bx > 0)
        bx = -500;
    glutPostRedisplay();
    glutTimerFunc(1, timerFunc, 0); // 16 milliseconds for ~60 fps
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(300, 50);
    glutCreateWindow("A Moving Car Scenario");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timerFunc, 0); // Start the timer immediately
    glutMainLoop();
    return 0;
}
