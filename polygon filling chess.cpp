#include <iostream>
#include <math.h>
#include <GL/glut.h>

using namespace std;

float R = 0, G = 0, B = 0;
int Algo;
float x1, y11, x2, y2, length, dx, dy, x, y;

int Sign(int x) {
    if (x > 0)
        return 1;
    else if (x < 0)
        return -1;
    else
        return 0;
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
}

void setpixel(float x, float y) {
//glColor3fv(fillcolor);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void DDA(float x1, float y11, float x2, float y2) {
    glColor3f(1, 0, 0);
    if (abs(x2 - x1) >= abs(y2 - y11)) {
        length = abs(x2 - x1);
    } else {
        length = abs(y2 - y11);
    }

    dx = (x2 - x1) / length;
    dy = (y2 - y11) / length;

    x = x1 + 0.5 * Sign(dx);
    y = y11 + 0.5 * Sign(dy);

    setpixel(x, y);

    int i = 1;
    while (i <= length) {
        x = x + dx;
        y = y + dy;
        i = i + 1;

        setpixel(x, y);
    }
}

void B_display(void) {
    DDA(40, 40, 100, 40);
    DDA(100, 40, 100, 100);
    DDA(100, 100, 40, 100);
    DDA(40, 100, 40, 40);
    DDA(60, 40, 60, 100);
    DDA(80, 40, 80, 100);
    DDA(40, 60, 100, 60);
    DDA(40, 80, 100, 80);
}

void boundaryFill(int x, int y, float* fillColor, float* bc) {
    float color[3];
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, color);

    if ((color[0] != bc[0] || color[1] != bc[1] || color[2] != bc[2]) &&
        (fillColor[0] != color[0] || fillColor[1] != color[1] || fillColor[2] != color[2])) {
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();
        boundaryFill(x + 1, y, fillColor, bc);
        boundaryFill(x - 1, y, fillColor, bc);
        boundaryFill(x, y + 1, fillColor, bc);
        boundaryFill(x, y - 1, fillColor, bc);
    }
}

void floodFill(int x, int y, float* newCol, float* oldcol) {
    float pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixel);

    if(oldcol[0]==pixel[0] && oldcol[1]==pixel[1] && oldcol[2]==pixel[2]){
        glBegin(GL_POINTS);
        glColor3f(newCol[0], newCol[1], newCol[2]);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        floodFill(x, y + 1, newCol, oldcol);
        floodFill(x + 1, y, newCol, oldcol);
        floodFill(x, y - 1, newCol, oldcol);
        floodFill(x - 1, y, newCol, oldcol);
    }
}

void mouse(int button, int state, int x, int y) {
    y = 480 - y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float bcol[] = {1, 0, 0};
        float oldcol[] = {0, 0, 0};
        float newCol[] = {R, G, B};

        if (Algo == 1) {
            boundaryFill(x, y, newCol, bcol);
        }
        if (Algo == 2) {
            floodFill(x, y, newCol, oldcol);
        }
    }
}

void Menu(int value) {
    switch (value) {
        case 1:
            R = 0, G = 1, B = 0; // Green
            break;
        case 2:
            R = 1, G = 1, B = 0; // Yellow
            break;
        case 3:
            R = 1, G = 0, B = 1; // Pink (for flood fill)
            break;
        case 4:
            R = 0, G = 1, B = 1; // Cyan (for flood fill)
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {

    cout << "\n \t Select the Algorithm ";
    cout << "\n \t 1. Boundary Fill Algorithm ";
    cout << "\n \t 2. Flood Fill Algorithm \n \t";
    cin >> Algo;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("A4");

    init();

    glutCreateMenu(Menu);
    if (Algo == 1) {
        glutAddMenuEntry("Color 1 Green", 1);
        glutAddMenuEntry("Color 2 Yellow", 2);
    } else if (Algo == 2) {
        glutAddMenuEntry("Color 1 Pink", 3);
        glutAddMenuEntry("Color 2 Cyan", 4);
    }
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    if (Algo == 1 || Algo == 2) {
        glutDisplayFunc(B_display);
    }

    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}
