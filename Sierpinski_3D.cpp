#include<stdio.h>
#include<GL/glut.h>
float a[3]={0,1,0};
float b[3]={0.5,-0.5,0};
float c[3]={-0.5,-0.5,0};
float d[3]={0,0,1};
int n;

void draw_tri(float *a,float *b,float *c)
{
    glBegin(GL_TRIANGLES);
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
    glEnd();
}
void draw_tetra(float *a,float *b,float *c,float *d)
{
    glColor3f(1,1,1);
    draw_tri(a,b,c);
    glColor3f(1,0,0);
    draw_tri(a,d,c);
    glColor3f(0,1,0);
    draw_tri(a,b,d);
    glColor3f(0,0,1);
    draw_tri(b,d,c);
}

void divide_tetrahedron(float *a,float *b,float *c,float *d,int n)
{
    float ab[3],bc[3],cd[3],ad[3],bd[3],ac[3];
    if(n>0)
    {
        for(int i=0;i<3;i++)
        {
            ab[i]=(a[i]+b[i])/2;
            bc[i]=(b[i]+c[i])/2;
            cd[i]=(c[i]+d[i])/2;
            ad[i]=(a[i]+d[i])/2;
            bd[i]=(b[i]+d[i])/2;
            ac[i]=(a[i]+c[i])/2;
        }
        divide_tetrahedron(a,ab,ac,ad,n-1);    
        divide_tetrahedron(ac,bc,c,cd,n-1);    
        divide_tetrahedron(ab,b,bc,bd,n-1);    
        divide_tetrahedron(ad,bd,cd,d,n-1);    
    }

    else
    {
        draw_tetra(a,b,c,d);
    }
}

void disp()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    divide_tetrahedron(a,b,c,d,n);
    glFlush();
}
void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1,1,-1,1,-1,1);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("3D Sierpinski");

    init();
    printf("Enter n value\n");
    scanf("%d",&n);
    glutDisplayFunc(disp);
    glutMainLoop();
}