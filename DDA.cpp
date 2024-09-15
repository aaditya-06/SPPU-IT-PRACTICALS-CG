
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

using namespace std;

int option, lineoption, drawoption;

void drawLine(int xx1, int yy1, int xx2, int yy2, int s)
{
    float x, y, dx, dy, length;
    int i, t = 0;
    dx = abs(xx2 - xx1);
    dy = abs(yy2 - yy1);

    if (dx > dy)
    {
        length = dx;
    }
    else
    {
        length = dy;
    }

    dx = (xx2 - xx1) / length;
    dy = (yy2 - yy1) / length;

    x = xx1;
    y = yy1;
    i = 1;
    glPointSize(1.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();

    while (i <= length)
    {
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
        x = x + dx;
        y = y + dy;
        i++;
    }
}

void display()
{
    glFlush();
}

void init()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
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
	static int x1, y1,x2,y2;
	static int pt = 0;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
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
                    glBegin(GL_POINTS);
                    drawLine(x, y, x+200, y, 1);
                    drawLine(x, y, x+40, y-40, 1);
                    drawLine(x+40, y-40, x+160, y-40, 1);
                    drawLine(x+160, y-40, x+200, y, 1);
                    drawLine(x+120, y, x+160, y+100, 1);
                    drawLine(x+200, y, x+160, y+100, 1);
                    glEnd();
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
                drawLine(-500 + 2 * x1, 500 - 2 * y1, -500 + 2 * x2, 500 - 2 * y2, option);

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
    glutAddMenuEntry("DDA Simple", 1);
    glutAddMenuEntry("DDA Dotted", 2);
    glutAddMenuEntry("DDA Dashed", 3);
    glutAddMenuEntry("DDA SOLID", 4);
    glutAddMenuEntry("DDA Object", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;
}

