#include<stdio.h>
#include<GL/glut.h>
float sq[4][2]={{250,100},{150,200},{250,300},{350,200}};
float get[4][4]={{100,200,250,-1},{100,200,250,1},{200,300,150,1},{200,300,350,-1}};
float aet[4][3];

int iaet;
int ymax;
int sc;
int np=4;   //number of points of polygon

void plot_pixel(float x1,float x2)
{
    float reach=x1;
    while(reach<x2)
    {
        glBegin(GL_POINTS);
            glVertex2f(reach,sc);
        glEnd();
        glFlush();
        reach++;
    }
}

void update_aet()
{
    for(int i=0;i<iaet;i++)
    {
        aet[i][1]=aet[i][1]+aet[i][2];
    }
}

void add_aet()
{
    for(int i=0;i<np;i++)
    {
        if(sc==get[i][0])
        {
            aet[iaet][0]=get[i][1];
            aet[iaet][1]=get[i][2];
            aet[iaet][2]=get[i][3];

            if(aet[iaet][0]>ymax)
            {
                ymax=aet[iaet][0];
            }
            iaet++;
        }
    }
}

void fill()
{
    iaet=0;
    ymax=0;
    sc=get[0][0];
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<3;j++)
        {
            aet[i][j]=0;
        }
    }
    //Above lines required for changing menu options
    
    float x[2]={0,0};
    int i;
    do
    {
        i=0;
        add_aet();
        //Always use if
        if(aet[0][0]>sc)
        {
            x[i]=aet[0][1];
            i++;
        }

        if(aet[1][0]>sc)
        {
            x[i]=aet[1][1];
            i++;
        }

        if(aet[2][0]>sc)
        {
            x[i]=aet[2][1];
            i++;
        }

        if(aet[3][0]>sc)
        {
            x[i]=aet[3][1];
            i++;
        }

        plot_pixel(x[0],x[1]);
        update_aet();
        sc++;
    }while(ymax>=sc);
}

void draw_square()
{
    glBegin(GL_LINE_LOOP);
        glVertex2fv(sq[0]);
        glVertex2fv(sq[1]);
        glVertex2fv(sq[2]);
        glVertex2fv(sq[3]);
    glEnd();
    glFlush();
}

void disp()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    draw_square();
    fill();
    //glFlush();
}
void menu(int ch)
{
    //Always use if not else-if
    if(ch==0)
        glColor3f(1,0,0);
    else if(ch==1)
        glColor3f(0,1,0);
    else if(ch==2)
        glColor3f(0,0,1);

    glutPostRedisplay();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutCreateWindow("Scanline Algorithm");
    init();

    glutCreateMenu(menu);
    glutAddMenuEntry("Red",0);
    glutAddMenuEntry("Green",1);
    glutAddMenuEntry("Blue",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glColor3f(1,0,0);   //default color->RED
    glutDisplayFunc(disp);
    glutMainLoop();
    return 0;
}