#include<GL/glut.h>
#include<stdio.h>
#include<math.h>

float tri[3][2]={{30,30},{40,50},{50,40}};
float angle,xr,yr;
int flag=0;

void draw_tri()
{
    glBegin(GL_TRIANGLES);
        glVertex2fv(tri[0]);
        glVertex2fv(tri[1]);
        glVertex2fv(tri[2]);
    glEnd();
    glFlush();
}

void rotate_tri()
{
    
}

void disp()
{
    float x=0,y=0;
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1,0,0);
    draw_tri();

    for(int i=0;i<3;i++)
    {
        x=tri[i][0];
        y=tri[i][1];
        tri[i][0]=xr+(x-xr)*cos(angle)-(y-yr)*sin(angle);
        tri[i][1]=yr+(y-yr)*cos(angle)+(x-xr)*sin(angle);
    }

    glColor3f(0,1,0);
    draw_tri();
}
void init()
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
    glutCreateWindow("Trianle Rotation");
    printf("Enter fixed point\n");
    scanf("%f %f",&xr,&yr);
    printf("Enter angle\n");
    scanf("%f",&angle);
    angle=angle*(22/7)/180;
    init();
    glutDisplayFunc(disp);
    glutMainLoop();
}
