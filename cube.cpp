#include<stdio.h>
#include<GL/glut.h>

float cube[8][3]={{-0.5,-0.5,0.5},{-0.5,0.5,0.5},{0.5,0.5,0.5},{0.5,-0.5,0.5},
                  {-0.5,-0.5,-0.5},{-0.5,0.5,-0.5},{0.5,0.5,-0.5},{0.5,-0.5,-0.5}};
float color[8][3]={{0,0,1},{0,1,1},{1,1,1},{1,0,1},{0,0,0},{0,1,0},{1,1,0},{1,0,0}};
float theta[3]={0,0,0};
int flag=0;

void idle()
{
    theta[flag]++;
    if(theta[flag]>=360)
    {
        theta[flag]=0;
    }

    for(int delay=0;delay<10000000;delay++);
    glutPostRedisplay();
}
void mouse(int btn,int state,int x,int y)
{
    if(state==GLUT_DOWN)
    {
        if(btn==GLUT_LEFT_BUTTON)
            flag=0;
        if(btn==GLUT_MIDDLE_BUTTON)
            flag=1;
        if(btn==GLUT_RIGHT_BUTTON)
            flag=2;
    }
}

void draw_poly(int a,int b,int c,int d)
{
    glBegin(GL_POLYGON);
        glColor3fv(color[a]);
        glVertex3fv(cube[a]);
        glColor3fv(color[b]);
        glVertex3fv(cube[b]);
        glColor3fv(color[c]);
        glVertex3fv(cube[c]);
        glColor3fv(color[d]);
        glVertex3fv(cube[d]);
    glEnd();
    
}

void draw_cube()
{
    draw_poly(0,1,2,3); //front
    draw_poly(4,5,6,7); //back
    draw_poly(3,2,6,7); //right
    draw_poly(4,5,1,0); //left
    draw_poly(1,5,6,2); //top
    draw_poly(4,0,3,7); //bottom
}

void disp()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(theta[0],1,0,0);
    glRotatef(theta[1],0,1,0);
    glRotatef(theta[2],0,0,1);
    draw_cube();
    glutSwapBuffers();
    //glFlush();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2,2,-2,2,-2,2);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Cube Spin");

    init();
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(disp);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}