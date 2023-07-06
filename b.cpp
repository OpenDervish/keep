#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
float ya=50,xa=10;
int xflag=1,yflag=1;

void idle()
{
    if(ya>-50 && yflag==1)
        ya-=0.2;
    if(ya<=-50 && yflag==1)
        yflag=0;
    if(ya<50 && yflag==0)
        ya+=0.2;
    if(ya>=50 && yflag==0)
        yflag=1;
    if(xa>-10 && xflag==1)
        xa-=0.2;
    if(xa<=-10 && xflag==1)
        xflag=0;
    if(xa<10 && xflag==0)
        xa+=0.2;
    if(xa>=10 && xflag==0)
        xflag=1;
    glutPostRedisplay();
}

void disp()
{
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    double x[4],y1[4],y2[4],y3[4];
    double xt[200],yt1[200],yt2[200],yt3[200];
    double u=0;
    int i=0;

    x[0]=100,x[1]=200,x[2]=200,x[3]=300+xa;
    y1[0]=450,y1[1]=450+ya;y1[2]=450-ya,y1[3]=450;
    y2[0]=400,y2[1]=400+ya;y2[2]=400-ya,y2[3]=400;
    y3[0]=350,y3[1]=350+ya;y3[2]=350-ya,y3[3]=350;

    for(i=0,u=0;u<=1;i++,u+=0.02)
    {
        xt[i]=x[0]*pow((1-u),3)+x[1]*3*u*pow((1-u),2)+x[2]*3*pow(u,2)*(1-u)+x[3]*pow(u,3);
        yt1[i]=y1[0]*pow((1-u),3)+y1[1]*3*u*pow((1-u),2)+y1[2]*3*pow(u,2)*(1-u)+y1[3]*pow(u,3);
        yt2[i]=y2[0]*pow((1-u),3)+y2[1]*3*u*pow((1-u),2)+y2[2]*3*pow(u,2)*(1-u)+y2[3]*pow(u,3);
        yt3[i]=y3[0]*pow((1-u),3)+y3[1]*3*u*pow((1-u),2)+y3[2]*3*pow(u,2)*(1-u)+y3[3]*pow(u,3);
    }

    glColor3f(1,0,0);
    glBegin(GL_QUAD_STRIP);
    for(int i=0;i<200;i++)
    {
        glVertex2f(xt[i],yt1[i]);
        glVertex2f(xt[i],yt2[i]);
    }
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_QUAD_STRIP);
    for(int i=0;i<200;i++)
    {
        glVertex2f(xt[i],yt2[i]);
        glVertex2f(xt[i],yt3[i]);
    }
    glEnd();

    glColor3f(1,1,1);
    glRecti(90,450,100,50);
    glFlush();
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("Bezier Curve-Flag");
    init();
    glutDisplayFunc(disp);
    glutIdleFunc(idle);
    glutMainLoop();
}