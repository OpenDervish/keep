//1
#include<stdio.h>
#include<GL/glut.h>

float v[8][3]={{-1,-1,1},{-1,1,1},{1,1,1},{1,-1,1},
               {-1,-1,-1},{-1,1,-1},{1,1,-1},{1,-1,-1}};
float col[][3]={{0,0,1},{0,1,1},{1,1,1},{1,0,1},
                {0,0,0},{0,1,0},{1,1,0},{1,0,0}};
float theta[]={0,0,0};
int flag=2;
float viewer[3]={0,0,2};

void myreshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<=h)
    {
        glFrustum(-2,2,-2*GLfloat(h)/GLfloat(w),2*GLfloat(h)/GLfloat(w),2,20);
    }

    else
    {
        glFrustum(-2*GLfloat(h)/GLfloat(w),2*GLfloat(h)/GLfloat(w),-2,2,2,20);
    }
    glMatrixMode(GL_MODELVIEW);
}

void key(unsigned char k,int x,int y)
{
    if(k=='x')
        viewer[0]--;
    if(k=='X')
        viewer[0]++;
    if(k=='y')
        viewer[1]--;
    if(k=='Y')
        viewer[1]++;
    if(k=='z')
        viewer[2]--;
    if(k=='Z')
        viewer[2]++;
    glutPostRedisplay();
}

void mymouse(int b,int s,int x,int y)
{
    if(s==GLUT_DOWN)
    {
        if(b==GLUT_LEFT_BUTTON)
            flag=0;
        if(b==GLUT_MIDDLE_BUTTON)
            flag=1;
        if(b==GLUT_RIGHT_BUTTON)
            flag=2;
    }
    theta[flag]++;
    if(theta[flag]>=360)
        theta[flag]=0;
    glutPostRedisplay();
}

void drawPoly(int a,int b,int c,int d)
{
    glBegin(GL_POLYGON);
        glColor3fv(col[a]);
        glVertex3fv(v[a]);
        glColor3fv(col[b]);
        glVertex3fv(v[b]);
        glColor3fv(col[c]);
        glVertex3fv(v[c]);
        glColor3fv(col[d]);
        glVertex3fv(v[d]);
    glEnd();
}

void colorCube()
{
    drawPoly(0,1,2,3);  //front
    drawPoly(4,5,6,7);  //back
    drawPoly(1,5,6,2);  //top
    drawPoly(4,0,3,7);  //bottom
    drawPoly(4,5,1,0);  //left
    drawPoly(3,2,6,7);  //right
}

void disp()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();       //VVVVVVVVVV IMP
    glEnable(GL_DEPTH_TEST);
    gluLookAt(viewer[0],viewer[1],viewer[2],0,0,0,0,1,0);
    glRotatef(theta[0],1,0,0);
    glRotatef(theta[1],0,1,0);
    glRotatef(theta[2],0,0,1);
    colorCube();
    glutSwapBuffers();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2,2,-2,2,2,20);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Cube");
    init();
    glutDisplayFunc(disp);
    glutKeyboardFunc(key);
    //glutIdleFunc(idle);
    glutMouseFunc(mymouse);
    glutReshapeFunc(myreshape);
    glutMainLoop();
    return 0;
}