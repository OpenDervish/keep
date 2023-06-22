#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
float tri[3][2]={{10,10},{20,30},{30,10}};
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
    float x=0,y=0;
    for(int i=0;i<3;i++)
    {
        x=tri[i][0];
        y=tri[i][1];
        tri[i][0]=xr+(x-xr)*cos(angle)-(y-yr)*sin(angle);
        tri[i][1]=yr+(y-yr)*cos(angle)+(x-xr)*sin(angle);
    }
}

void disp()
{
    if(flag==0)
    {
        glClearColor(1,1,1,1);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1,0,0);
        draw_tri();
        flag=1;
    }

    else
    {
        rotate_tri();
        glColor3f(0,1,0);
        draw_tri();
        flag=0;
    }
    
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

/*
#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

int xr, yr;
float angle;
float vertex[3][2] = { { 20, 20 }, { 40,60 }, { 60,20 } };
void drawTriangle();
void display();

void drawTriangle()
{
	glBegin(GL_TRIANGLES);
	glVertex2fv(vertex[0]);
	glVertex2fv(vertex[1]);
	glVertex2fv(vertex[2]);
	glEnd();
	glFlush();
}

void display()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	drawTriangle();

	for (int i = 0; i < 3; i++)
	{
		int x = vertex[i][0];
		int y = vertex[i][1];
		vertex[i][0] = xr + (x - xr) * cos(angle) - (y - yr) * sin(angle);
		vertex[i][1] = yr + (x - xr) * sin(angle) + (y - yr) * cos(angle);
	}

	glColor3f(0, 1, 0);
	drawTriangle();
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Rotate Triangle");
	gluOrtho2D(0, 150, 0, 150);

	printf("Enter Reference Point: ");
	scanf_s("%d %d", &xr, &yr);
	printf("Enter Angle in Degree: ");
	scanf_s("%f", &angle);

	angle = ((angle * 22) / 7) / 180; // Coverting to Radian
	glutDisplayFunc(display);
	glutMainLoop();
}
*/