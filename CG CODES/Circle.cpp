#include <GL/glut.h>
#include <iostream>

using namespace std;

int r;

void E_way(int x, int y) {
    glBegin(GL_POINTS);
        glVertex2i(x + 320, y + 240);
        glVertex2i(y + 320, x + 240);
        glVertex2i(y + 320, -x + 240);
        glVertex2i(x + 320, -y + 240);
        glVertex2i(-x + 320, -y + 240);
        glVertex2i(-y + 320, -x + 240);
        glVertex2i(-y + 320, x + 240);
        glVertex2i(-x + 320, y + 240);
    glEnd();
    glFlush();
}

void B_circle() {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while (x <= y) {
        E_way(x, y);
        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // white background
    glColor3f(1.0, 0.0, 0.0);         // red drawing color
    gluOrtho2D(0, 640, 0, 480);       // coordinate system
    glClear(GL_COLOR_BUFFER_BIT);     // clear screen
    glFlush();
}

int main(int argc, char **argv) {
    cout << "Enter Radius: ";
    cin >> r;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Bresenham Circle");

    init();
    glutDisplayFunc(B_circle);
    glutMainLoop();

    return 0;
}