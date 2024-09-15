#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

int radius_simple,radius_concentric,radius_spiral,radius_olympic,centerX, centerY, numofcircles;
int type;// 1: Simple circle, 2: Olympic Ring, 3: Concentric circles, 4: Spiral;

void plot_pixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void bresenham_circle_simple(int r, int h, int k)
{
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while (x <= y)
	{
        plot_pixel(x + h, y + k);
        plot_pixel(-x + h, -y + k);
        plot_pixel(y + h, x + k);
        plot_pixel(-y + h, -x + k);
        plot_pixel(-y + h, x + k);
        plot_pixel(y + h, -x + k);
        plot_pixel(-x + h, y + k);
        plot_pixel(x + h, -y + k);

        if (d <= 0)
		{
            d = d + 4 * x + 6;
        }
		else
		{
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void olympic_circle(int centerX, int centerY,int radius)
{        // Draw the rings with different colors
    glColor3f(0.0, 0.0, 1.0); // Blue
    bresenham_circle_simple(radius,centerX - 100, centerY);
    glColor3f(1.0, 0.0, 0.0); // Red
    bresenham_circle_simple(radius,centerX, centerY);
    glColor3f(0.0, 1.0, 0.0); // Green
    bresenham_circle_simple(radius,centerX + 100, centerY);
    glColor3f(1.0, 1.0, 0.0); // Yellow
    bresenham_circle_simple(radius,centerX - 50, centerY - 50);
    glColor3f(1.0, 0.5, 0.0); // Orange
    bresenham_circle_simple(radius,centerX + 50, centerY - 50);
}

void bresenham_concentric_circles(int numcircles, int h, int k)
{

    for (int i = 1; i <= numcircles; i++)
	{
        bresenham_circle_simple(i * radius_concentric, h, k);
    }
}

void upperhalf(int centerX, int centerY, int radius)
{
    int d = 3 - 2 * radius;
    int x = 0;
    int y = radius;

    while (x < y)
	{
        plot_pixel(x + centerX, y + centerY);
        plot_pixel(y + centerX, x + centerY);
        plot_pixel(-y + centerX, x + centerY);
        plot_pixel(-x + centerX, y + centerY);

        if (d <= 0)
		{
            d = d + 4 * x + 6;
            x += 1;
        }
		else
		{
            d = d + 4 * (x - y) + 10;
            x += 1;
            y -= 1;
        }
    }
}

void lowerhalf(int centerX, int centerY, int radius)
{
    int d = 3 - 2 * radius;
    int x = 0;
    int y = radius;

    while (x < y)
	{
        plot_pixel(-x + centerX, -y + centerY);
        plot_pixel(-y + centerX, -x + centerY);
        plot_pixel(y + centerX, -x + centerY);
        plot_pixel(x + centerX, -y + centerY);

        if (d <= 0)
		{
            d = d + 4 * x + 6;
            x += 1;
        }
		else
		{
            d = d + 4 * (x - y) + 10;
            x += 1;
            y -= 1;
        }
    }
}

void drawSpiral(int centerX, int centerY, int radius)
{
    for (int i = 0; i < 4; i++)
	{
        upperhalf(centerX, centerY, radius);
        centerX += 20;
        radius += 20;

        lowerhalf(centerX, centerY, radius);
        centerX -= 20;
        radius += 20;
    }
}



void menu(int option)
{
   type = option;
   if(type == 1)
   {
        cout <<"Enter radius of circle: ";
        cin >> radius_simple;
   }
   else if(type == 2)
   {
        cout <<"Enter radius of circle: ";
        cin >> radius_olympic;
   }
   else if(type == 3)
   {
        cout <<"Enter radius increment of circle: ";
        cin >> radius_concentric;
        cout <<"Enter Number of circles: ";
        cin >> numofcircles;
   }
   else
   {
        cout <<"Enter radius of circle: ";
        cin >> radius_spiral;
   }
}

int cnt = 0;
int oldx, oldy;
int newx, newy;

void mouse(int button, int state, int x, int y)



 {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            int xi = x - 350;
            int yi = 350 - y;

            cout << xi << "\t" << yi << "\n";

                glPointSize(2.0f);
                glColor3f(1.0, 0.0, 0.0);

                glBegin(GL_POINTS);
                glVertex2i(xi,yi);
                glEnd();
                glColor3f(1.0, 0.0, 0.0);

                if(type == 1)
				{
                    bresenham_circle_simple(radius_simple,xi,yi);
                }
                else if(type == 2)
				{
                    olympic_circle(xi,yi,radius_olympic);
				}
                else if(type == 3)
				{
                    bresenham_concentric_circles(numofcircles,xi,yi);
				}
                else
				{
                    drawSpiral(xi,yi,radius_spiral);
				}
                glFlush();

            }
        }
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_LINES);               //draw axes
        glVertex2i(-350, 0);
        glVertex2i(350, 0);
        glVertex2i(0,-350);
        glVertex2i(0, 350);
    glEnd();

    glFlush();
}
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);

    gluOrtho2D(-700 / 2, 700 / 2, -700 / 2, 700 / 2);
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

