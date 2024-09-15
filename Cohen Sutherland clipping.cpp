#include <iostream>
#include <GL/glut.h>

#define outcode int
double xmin = 100, ymin = 100, xmax = 200, ymax = 200; // clipping window
double xvmin = 300, yvmin = 300, xvmax = 400, yvmax = 400; // view port
double x0, y0, x1, y1;
const int RIGHT = 8;
const int LEFT = 2;
const int TOP = 4;
const int BOTTOM = 1;
int n = 0;
GLfloat obj[100][2];

void myinit()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

outcode ComputeOutCode(double x, double y);

void CohenSutherland(double x0, double y0, double x1, double y1)
{
    outcode outcode0, outcode1, outcodeOut;
    bool accept = false, done = false;
    outcode0 = ComputeOutCode(x0, y0);
    outcode1 = ComputeOutCode(x1, y1);
    do
    {
        if (!(outcode0 | outcode1))    //!outcode0 | outcode1=0
        {
            accept = true; // Line is completely visible
            done = true;
        }
        else if (outcode0 & outcode1)
            done = true; // Line is completely invisible
        else // Line is partially visible
        {
            double x, y;
            outcodeOut = outcode0 ? outcode0 : outcode1;        //if (outcode0 != 0) { outcodeOut = outcode0;} else {outcodeOut = outcode1;}
            if (outcodeOut & TOP)
            {
                x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
                y = ymax;
            }
            else if (outcodeOut & BOTTOM)
            {
                x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
                y = ymin;
            }
            else if (outcodeOut & RIGHT)
            {
                y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
                x = xmax;
            }
            else
            {
                y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
                x = xmin;
            }
            if (outcodeOut == outcode0)
            {
                x0 = x;
                y0 = y;
                outcode0 = ComputeOutCode(x0, y0);
            }
            else
            {
                x1 = x;
                y1 = y;
                outcode1 = ComputeOutCode(x1, y1);
            }
        }
    } while (!done);
    if (accept)
    {
        double sx = (xvmax - xvmin) / (xmax - xmin);
        double sy = (yvmax - yvmin) / (ymax - ymin);
        double vx0 = xvmin + (x0 - xmin) * sx;
        double vy0 = yvmin + (y0 - ymin) * sy;
        double vx1 = xvmin + (x1 - xmin) * sx;
        double vy1 = yvmin + (y1 - ymin) * sy;
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2d(vx0, vy0);
        glVertex2d(vx1, vy1);
        glEnd();
    }
}

outcode ComputeOutCode(double x, double y)
{
    outcode code = 0; // Assign region code
    if (y > ymax)
        code |= TOP;
    else if (y < ymin)
        code |= BOTTOM;
    if (x > xmax)
        code |= RIGHT;
    else if (x < xmin)
        code |= LEFT;
    return code;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
   glBegin(GL_LINE_LOOP); // Draw clipping window
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP); // Draw viewport
    glVertex2f(xvmin, yvmin);
    glVertex2f(xvmax, yvmin);
    glVertex2f(xvmax, yvmax);
    glVertex2f(xvmin, yvmax);
    glEnd();

    glFlush();
}

void myKeyboard(unsigned char key, int mousex, int mouseY)
{
    switch (key)
    {
    case 27:
        exit(0); // Press ESC key to exit
    }
}

void myMouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            obj[n][0] = x;
            obj[n][1] = 500 - y;
            glBegin(GL_POINTS);
            glVertex2f(obj[n][0], obj[n][1]);
            glEnd();
            n++;
            glFlush();
        }
        else if (button == GLUT_RIGHT_BUTTON)
        {
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < n; i++)
                glVertex2f(obj[i][0], obj[i][1]);
            glEnd();
            glFlush();

            for (int i = 0; i < n; i++)
            {
                int j = (i + 1) % n;
                CohenSutherland(obj[i][0], obj[i][1], obj[j][0], obj[j][1]);
            }
            glFlush();
            n = 0;
        }
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Cohen-Sutherland polygon Clipping");
    glutMouseFunc(myMouse);
    glutKeyboardFunc(myKeyboard);
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
    return 0;
}

