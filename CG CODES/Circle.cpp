#include <GL/glut.h>
#include <iostream>

using namespace std;

int radius = 100;
int center_x = 0, center_y = 0;

void plot_pixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void bresenham_circle(int r, int h, int k) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while (x <= y) {
        plot_pixel(x + h, y + k);
        plot_pixel(-x + h, y + k);
        plot_pixel(x + h, -y + k);
        plot_pixel(-x + h, -y + k);
        plot_pixel(y + h, x + k);
        plot_pixel(-y + h, x + k);
        plot_pixel(y + h, -x + k);
        plot_pixel(-y + h, -x + k);

        if (d <= 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw axes
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2i(-350, 0);
        glVertex2i(350, 0);
        glVertex2i(0, -350);
        glVertex2i(0, 350);
    glEnd();
    
    // Draw circle
    glColor3f(1.0, 0.0, 0.0);
    bresenham_circle(radius, center_x, center_y);
    
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-350, 350, -350, 350);
    glPointSize(2.0);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        center_x = x - 350;
        center_y = 350 - y;
        glutPostRedisplay();
    }
}

void menu(int choice) {
    switch(choice) {
        case 1: radius = 100; break;
        case 2: radius = 50; break;
        case 3: radius = 150; break;
        case 4: radius = 75; break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Bresenham Circle");
    
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    
    glutCreateMenu(menu);
    glutAddMenuEntry("Simple Circle", 1);
    glutAddMenuEntry("Olympic Ring", 2);
    glutAddMenuEntry("Concentric Circles", 3);
    glutAddMenuEntry("Spiral", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    glutMainLoop();
    return 0;
}