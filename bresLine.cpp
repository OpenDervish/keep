#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
int x1,yi,x2,y2;

void setPixel(int x,int y)
{
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
}

void bresLow()
{
    int dx=fabs(x2-x1);
    int dy=fabs(y2-yi);
    int p=2*dy-dx;
    int two_dy_dx=2*(dy-dx);
    int x,y;
    if(x1>x2)
    {
        x=x2;
        y=y2;
        x2=x1;
    }

    else
    {
        x=x1;
        y=yi;
    }

    setPixel(x,y);
    while(x<x2)
    {
        x++;
        if(p<0)
        {
            p+=2*dy;
        }

        else
        {
            y++;
            p+=two_dy_dx;
        }
        setPixel(x,y);
    }
}

void bresHigh()
{
    int dx=fabs(x2-x1);
    int dy=fabs(y2-yi);
    int p=2*dx-dy;
    int two_dx_dy=2*(dx-dy);
    int x,y;
    if(yi>y2)
    {
        x=x2;
        y=y2;
        y2=yi;
    }

    else
    {
        x=x1;
        y=yi;
    }

    setPixel(x,y);
    while(y<y2)
    {
        y++;
        if(p<0)
        {
            p+=2*dx;
        }

        else
        {
            x++;
            p+=two_dx_dy;
        }
        setPixel(x,y);
    }
}


void findSlope()
{
    if(fabs(y2-yi)<fabs(x2-x1))
    {
        bresLow();
    }

    else
    {
        bresHigh();
    }
}

void disp()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    glPointSize(2);
    findSlope();
    glFlush();
}

void  init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,100,0,100);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutCreateWindow("Bresenham's Algorithm");

    init();
    printf("Enter start points\n");
    scanf("%d %d",&x1,&yi);
    printf("Enter end points\n");
    scanf("%d %d",&x2,&y2);
    glutDisplayFunc(disp);
    glutMainLoop();
    return 0;
}
