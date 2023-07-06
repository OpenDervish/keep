//2
#include<stdio.h>
#include<GL/glut.h>
#define opcode int
float prev_x1,prev_y1,prev_x2,prev_y2;
float x1,y1,x2,y2;
float umin,vmin,umax,vmax;
float xmin,ymin,xmax,ymax;
enum {left=0x1,right=0x2,bottom=0x4,top=0x8};

opcode gen_opcode(int x,int y)
{
    int p=0;
    if(x<xmin)
        p|=left;
    if(x>xmax)
        p|=right;
    if(y<ymin)
        p|=bottom;
    if(y>ymax)
        p|=top;

    return p;
}

void sutherland()
{
    float m;
    int p,p1,p2;
    bool done=false,accept=false;
    int x,y;

    x1=prev_x1;
    x2=prev_x2;
    y1=prev_y1;
    y2=prev_y2;

    p1=gen_opcode(x1,y1);
    p2=gen_opcode(x2,y2);

    while(!done)
    {
        if((p1|p2)==0)
        {
            done=true;
            accept=true;
        }

        else if((p1&p2)!=0)
        {
            done=true;
        }

        else
        {
            m=(y2-y1)/(x2-x1);
            p=p1!=0? p1 : p2;
            if((p&left)!=0)
            {
                x=xmin;
                y=y1+(xmin-x1)*m;
            }

            if((p&right)!=0)
            {
                x=xmax;;
                y=y1+(xmax-x1)*m;
            }

            if((p&bottom)!=0)
            {
                y=ymin;
                x=x1+(ymin-y1)/m;
            }

            if((p&top)!=0)
            {
                y=ymax;
                x=x1+(ymax-y1)/m;
            }

            if(p==p1)
            {
                x1=x;
                y1=y;
                p1=gen_opcode(x1,y1);
            }

            if(p==p2)
            {
                x2=x;
                y2=y;
                p2=gen_opcode(x1,y1);
            }
        }
    }

    if(accept)
    {
        float sx=(umax-umin)/(xmax-xmin);
        float sy=(vmax-vmin)/(ymax-ymin);

        x1=x1*sx + umin -sx*xmin;
        y1=y1*sy + vmin -sy*ymin;
        x2=x2*sx + umin -sx*xmin;
        y2=y2*sy + vmin -sy*ymin;

        glBegin(GL_LINES);
            glVertex2f(x1,y1);
            glVertex2f(x2,y2);
        glEnd();
        glFlush();
    }
}

void disp()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin,ymin);
        glVertex2f(xmin,ymax);
        glVertex2f(xmax,ymax);
        glVertex2f(xmax,ymin);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(umin,vmin);
        glVertex2f(umin,vmax);
        glVertex2f(umax,vmax);
        glVertex2f(umax,vmin);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_LINES);
        glVertex2f(prev_x1,prev_y1);
        glVertex2f(prev_x2,prev_y2);
    glEnd();

    glColor3f(0,0,1);
    sutherland();
    glFlush();

}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,1200,0,1200);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutInitWindowSize(1200,1200);
    glutCreateWindow("Cohen-Sutherland Line Clipping");
    init();
    printf("Enter Clipping Window Diagonal Coordinates\n");
    scanf_s("%f %f %f %f",&xmin,&ymin,&xmax,&ymax);
    printf("Enter Viewing Window Diagonal Coordinates\n");
    scanf_s("%f %f %f %f",&umin,&vmin,&umax,&vmax);

    printf("Enter Line Coordinates\n");
    scanf_s("%f %f %f %f",&prev_x1,&prev_y1,&prev_x2,&prev_y2);

    glutDisplayFunc(disp);
    glutMainLoop();
    return 0;
}
