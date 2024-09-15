#include <iostream>
#include <GL/glut.h>

int clicks = 0;
GLfloat points[4][2];
bool curveDrawn = false;

void drawPoint(GLfloat x, GLfloat y) {
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}

void drawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
    glFlush();
}

void midpointSubdivision(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4) {
    GLfloat xAB = (x1 + x2) / 2;
    GLfloat yAB = (y1 + y2) / 2;
    GLfloat xBC = (x2 + x3) / 2;
    GLfloat yBC = (y2 + y3) / 2;
    GLfloat xCD = (x3 + x4) / 2;
    GLfloat yCD = (y3 + y4) / 2;
    GLfloat xABC = (xAB + xBC) / 2;
    GLfloat yABC = (yAB + yBC) / 2;
    GLfloat xBCD = (xBC + xCD) / 2;
    GLfloat yBCD = (yBC + yCD) / 2;
    GLfloat xABCD = (xABC + xBCD) / 2;
    GLfloat yABCD = (yABC + yBCD) / 2;

    if ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) > 4 || (x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2) > 4 || (x4 - x3) * (x4 - x3) + (y4 - y3) * (y4 - y3) > 4) {
        midpointSubdivision(x1, y1, xAB, yAB, xABC, yABC, xABCD, yABCD);
        midpointSubdivision(xABCD, yABCD, xBCD, yBCD, xCD, yCD, x4, y4);
    }
    else {
        drawLine(x1, y1, xABCD, yABCD);
        drawLine(xABCD, yABCD, x4, y4);
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        points[clicks][0] = GLfloat(x);
        points[clicks][1] = GLfloat(600 - y);
        clicks++;

        drawPoint(GLfloat(x), GLfloat(600 - y));

        if (clicks == 4) {
            // Draw lines between consecutive points
            drawLine(points[0][0], points[0][1], points[1][0], points[1][1]);
            drawLine(points[1][0], points[1][1], points[2][0], points[2][1]);
            drawLine(points[2][0], points[2][1], points[3][0], points[3][1]);

            // Draw Bezier curve using midpoint subdivision
            midpointSubdivision(points[0][0], points[0][1], points[1][0], points[1][1],
                points[2][0], points[2][1], points[3][0], points[3][1]);


        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (curveDrawn) {
        // Redraw all points if curve is drawn
        for (int i = 0; i < 4; ++i) {
            drawPoint(points[i][0], points[i][1]);
        }
    }

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 600, 0, 600);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bezier Curve - Midpoint Subdivision");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}


