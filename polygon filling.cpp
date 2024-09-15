#include <GL/glut.h>
#include<math.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

int w=640,h=480;
int X1,Y1,flag=0;
float boundaryColor[3]={0,0,0}, interiorColor[3]={1,1,1}, fillColor[3];
float readPixel[3];


void setPixel(int x,int y)          //Function to plot points
{
        glColor3fv(fillColor);
        glBegin(GL_POINTS);
        glVertex2f(x,y);
        glEnd();
        glFlush();
}

void getPixel(int x, int y, float *color)   //Function to get pixel information
{
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,color);
}
int sign(float s)       //Function to determine sign (+ve/-ve/0)
{
    if(s<0)
        return -1;
    else if(s>0)
        return 1;
    else
        return 0;
}

void Bresenham(int X1,int Y1,int X2,int Y2)                   //Function to draw
{

    float x,y,dx,dy,s1,s2,interchange,e;
    x=X1,y=Y1;                  //1- Initialize variables

    dx=abs(X2-X1);
    dy=abs(Y2-Y1);

    s1=sign(X2-X1);
    s2=sign(Y2-Y1);

    if(dx>=dy)                 //2-interchanged based on slope
    {
        float t=dx;
        dx=dy;
        dy=t;
        interchange=1;
    }
    else
        interchange=0;

    e=2*dy-dx;
    glBegin(GL_POINTS);

    for(int i=1;i<=dx;i++)      //3- Main Loop for Bresenham's line Algo
    {
        glVertex2f(x,y);
        while(e>=0)
        {
            if(interchange==1)
                x=x+s1;
            else
                y=y+s2;
            e=e-(2*dx);
        }
        if(interchange==1)
            y=y+s2;
        else
            x=x+s1;
        e=e+(2*dy);
    }
    glVertex2f(x,y);
    glEnd();
    glFlush();
}
void display()          //Function to display polygon
  {
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0f,0.0f,0.0f);

  	glLoadIdentity();
  	gluOrtho2D(0,640,0,480);

    glClear(GL_COLOR_BUFFER_BIT);
    Bresenham(300,200,350,250);
   Bresenham(350,250,400,200);
   Bresenham(400,200,350,150);
   Bresenham(350,150,300,200);
   }
   void boundaryFill(int x, int y){
   getPixel(x,y,readPixel);
   if( readPixel[0]!=boundaryColor[0] && readPixel[1]!=boundaryColor[1] && readPixel[2]!=boundaryColor[2])
   { setPixel(x,y);
        boundaryFill(x+1,y);
        boundaryFill(x,y+1);
        boundaryFill(x-1,y);
        boundaryFill(x,y-1);
        glFlush();
   }
   }
   void floodFill(int x, int y){
   getPixel(x,y,readPixel);
   if (readPixel[0]==interiorColor[0] && readPixel[1]==interiorColor[1] && readPixel[2]==interiorColor[2]){
   setPixel(x,y);
   floodFill(x+1,y);
        floodFill(x,y+1);
        floodFill(x-1,y);
        floodFill(x,y-1);
        glFlush();
        }
        }
        void mouse(int btn,int state,int x,int y)   //Function to create mouse interface
  {
       if((btn==GLUT_LEFT_BUTTON)&&(state==GLUT_DOWN))
       {
                 X1=x;
                 Y1=480-y;
                if(flag==1)
                    boundaryFill(X1,Y1);

                else if(flag==2)
                    floodFill(X1,Y1);
       }
  }
  void menu(int item){
if (item==1){
flag=1;
fillColor[0]=0;
fillColor[1]=1;
fillColor[2]=2;
}
else if (item==2){
flag=2;
fillColor[0]=1;
fillColor[1]=0.5;
fillColor[2]=0.8;
}
else if(item==3){
exit(0);
}
}
 int main(int argc,char** argv)
  {
       glutInit(&argc,argv);
       glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
       glutInitWindowSize(w,h);
       glutCreateWindow("Polygon Filling");
       glutCreateMenu(menu);
            glutAddMenuEntry("Boundary Fill",1);
            glutAddMenuEntry("FloodFill",2);
            glutAddMenuEntry("Exit",3);
        glutAttachMenu(GLUT_RIGHT_BUTTON);      //Attaching menu to right mouse click
       glutDisplayFunc(display);
       glutMouseFunc(mouse);
       glutMainLoop();
       return 0;
  }
