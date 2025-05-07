#include <GL/glut.h>
#include <iostream>

// Clipping window boundaries
GLfloat xMin = -0.5, xMax = 0.5, yMin = -0.5, yMax = 0.5;

// Original line endpoints
GLfloat x_start = -0.8, y_start = -0.6, x_end = 0.7, y_end = 0.4;

// Region code bit masks
const int Left = 1, Right = 2, Bottom = 4, Top = 8;

int Clip_Flag = 0;
int Draw_Flag = 1;

// Function to get region code
int Get_Code(GLfloat x, GLfloat y) {
    int code = 0;
    if (x < xMin) code |= Left;
    if (x > xMax) code |= Right;
    if (y < yMin) code |= Bottom;
    if (y > yMax) code |= Top;
    return code;
}

// Cohen–Sutherland line clipping algorithm
void Clip(GLfloat &x0, GLfloat &y0, GLfloat &x1, GLfloat &y1) {
    int code1 = Get_Code(x0, y0);
    int code2 = Get_Code(x1, y1);

    bool done = false;

    while (!done) {
        if ((code1 | code2) == 0) {
            // Trivially accepted
            Draw_Flag = 1;
            done = true;
        } else if ((code1 & code2) != 0) {
            // Trivially rejected
            Draw_Flag = 0;
            done = true;
        } else {
            // Needs clipping
            int out_code = code1 ? code1 : code2;
            float x, y;

            if (out_code & Top) {
                x = x0 + (x1 - x0) * (yMax - y0) / (y1 - y0);
                y = yMax;
            } else if (out_code & Bottom) {
                x = x0 + (x1 - x0) * (yMin - y0) / (y1 - y0);
                y = yMin;
            } else if (out_code & Right) {
                y = y0 + (y1 - y0) * (xMax - x0) / (x1 - x0);
                x = xMax;
            } else if (out_code & Left) {
                y = y0 + (y1 - y0) * (xMin - x0) / (x1 - x0);
                x = xMin;
            }

            // Replace outside point with intersection
            if (out_code == code1) {
                x0 = x;
                y0 = y;
                code1 = Get_Code(x0, y0);
            } else {
                x1 = x;
                y1 = y;
                code2 = Get_Code(x1, y1);
            }
        }
    }
}

// Drawing function
void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping rectangle
    glColor3f(1, 1, 1); // white box
    glBegin(GL_LINE_LOOP);
        glVertex2f(xMin, yMin);
        glVertex2f(xMax, yMin);
        glVertex2f(xMax, yMax);
        glVertex2f(xMin, yMax);
    glEnd();

    // Copy original line endpoints (so original values remain intact)
    GLfloat x0 = x_start, y0 = y_start, x1 = x_end, y1 = y_end;

    // Perform clipping if user pressed a key
    if (Clip_Flag) {
        Draw_Flag = 1; // Reset draw flag
        Clip(x0, y0, x1, y1);
    }

    // Draw line (original or clipped)
    if (Draw_Flag) {
        glColor3f(1, 0, 0); // red line
        glBegin(GL_LINES);
            glVertex2f(x0, y0);
            glVertex2f(x1, y1);
        glEnd();
    }

    glFlush();
}

// Keyboard input handler
void Key(unsigned char key, int x, int y) {
    if (key == 'c' || key == 'C') {
        Clip_Flag = 1;
        glutPostRedisplay();
    }
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Cohen-Sutherland Line Clipping (C++)");

    // Setup viewing
    glClearColor(0, 0, 0, 1);          // black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);          // 2D coordinate system

    glutDisplayFunc(Draw);
    glutKeyboardFunc(Key);

    glutMainLoop();
    return 0;
}
