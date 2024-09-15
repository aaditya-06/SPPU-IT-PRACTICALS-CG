
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

using namespace std;

int option, drawoption;
int sign(int s)
{
	if(s < 0)
		return -1;
	else if(s>0)
		return 1;
	else
		return 0;
}
void drawBresenhamLine(int x1, int y1, int x2, int y2, int s)
{
    int interchange, e,temp;
    int i = 0, t = 0;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int s1 = sign(x2 - x1);
    int s2 = sign(y2 - y1);
    int x = x1;
    int y = y1;

    if (dy > dx)
    {
        temp = dx;
	dx = dy;
	dy = temp;
        interchange = 1;
    }
    else
    {
        interchange = 0;
    }
    e = 2 * dy - dx;

    glBegin(GL_POINTS);
    switch (s)
    {
    case 1:
        glPointSize(1.0);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        break;

    case 2:
        if (i % 20 == 0)
        {
            glPointSize(1.0);
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
            break;
        }
    case 3:
        if (i % 15 == 0)
        {
            if (t == 0)
            {
                t = 1;
            }
            else
            {
                t = 0;
            }
        }
        if (t == 0)
        {
            glPointSize(1.0);
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
        }
        break;

    case 4:
        glBegin(GL_POINTS);
        glPointSize(3.0);
        glVertex2i(x, y);
        glEnd();
        break;
    }
    glEnd();

    for( int i = 0; i<dx ; i++)
    {
        glBegin(GL_POINTS);
        switch (s)
        {
        case 1:
            glPointSize(1.0);
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
            break;

        case 2:
            if (i % 20 == 0)
            {
                glPointSize(1.0);
                glBegin(GL_POINTS);
                glVertex2i(x, y);
                glEnd();
                break;
            }
        case 3:
            if (i % 15 == 0)
            {
                if (t == 0)
                {
                    t = 1;
                }
                else
                {
                    t = 0;
                }
            }
            if (t == 0)
            {
                glPointSize(1.0);
                glBegin(GL_POINTS);
                glVertex2i(x, y);
                glEnd();
            }
            break;

        case 4:
            glPointSize(3.0);
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
            break;
        }
        glEnd();

      	while(e>=0)
        {
            if (interchange == 1)
                x = x+s1;
            else
                y = y+s2;
            e = e-2 * dx;
        }

        if (interchange == 1)
            y = y+s2;
        else
            x = x+s1;

        e = e + 2 * dy;
   }
}

void display()
{
    glFlush();
}

void init()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f,0.0f,0.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
}

void inputKeyboard(unsigned char key, int mouseX, int mouseY)
{
    switch (key)
    {
    case 27:
        exit(0);
    }
}

void inputMouse(int button, int state, int x, int y)
{
    static int x1, x2, y1, y2;
    static int pt = 0;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (pt == 0)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_LINES);
            glVertex2i(-500.0, 0);
            glVertex2i(500.0, 0);
            glVertex2i(0, -500.0);
            glVertex2i(0, 500.0);
            glEnd();
            pt++;
        }
        else
        {
            if (pt == 1)
            {
                 if (drawoption == 1)
                {

                     // glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    drawBresenhamLine(-200, -200, -200, 200, 1);
    drawBresenhamLine(-200, 200, 200, 200, 1);
    drawBresenhamLine(200, 200, 200, -200, 1);
    drawBresenhamLine(200, -200, -200, -200, 1);

	drawBresenhamLine(0, -200, -200, 0, 1);
    drawBresenhamLine(-200, 0, 0, 200, 1);
    drawBresenhamLine(0, 200, 200, 0, 1);
    drawBresenhamLine(200, 0, 0, -200, 1);

    drawBresenhamLine(-100, -100, -100, 100, 1);
    drawBresenhamLine(-100, 100, 100, 100, 1);
    drawBresenhamLine(100, 100, 100, -100, 1);
    drawBresenhamLine(100, -100, -100, -100, 1);
   	glFlush();
                }
                else
                {
                    glClear(GL_COLOR_BUFFER_BIT);
                    glBegin(GL_LINES);
                    glVertex2i(-500.0, 0);
                    glVertex2i(500.0, 0);
                    glVertex2i(0, -500.0);
                    glVertex2i(0, 500.0);
                    glEnd();
                    x1 = x;
                    y1 = y;
                    pt++;
                }
            }
            else if (pt == 2)
            {
                x2 = x;
                y2 = y;

                drawBresenhamLine(-500 + 2 * x1, 500 - 2 * y1, -500 + 2 * x2, 500 - 2 * y2, option);
                pt = 0;
            }
        }
    }
    glFlush();
}

void menu(int choice)
{

     if (choice == 1)
    {
        option = 1;
        drawoption = 0;
    }
    else if (choice == 2)
    {
        option = 2;
        drawoption = 0;
    }
    else if (choice == 3)
    {
        option = 3;
        drawoption = 0;
    }
    else if (choice == 4)
    {
        option = 4;
        drawoption = 0;
    }
    else if (choice == 5)
    {
        option = 1;
        drawoption = 1;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Line Drawing Algorithms");
    glutMouseFunc(inputMouse);
    glutKeyboardFunc(inputKeyboard);
    init();
    glutDisplayFunc(display);
    glutCreateMenu(menu);
    glutAddMenuEntry("Bresenham Simple", 1);
    glutAddMenuEntry("Bresenham Dotted", 2);
    glutAddMenuEntry("Bresenham Dashed", 3);
    glutAddMenuEntry("Bresenham SOLID", 4);
    glutAddMenuEntry("Bresenham Object", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;
}

