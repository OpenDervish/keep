#include<math.h>
#include <GL/glut.h>
GLsizei winWidth = 500, winHeight = 500; // Initial display-window size.
float ya = 50, xa = 10;
int yflag = 1, xflag = 1;
void init(void)
{
	// Set display-window color.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);

}
void draw()
{
	double x[4], y1[4], y2[4], y3[4], y4[4];
	double xt[200], yt1[200], yt2[200], yt3[200], yt4[200];
	int i = 0;
	double u = 0;
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	x[0] = 100; x[1] = 200; x[2] = 200; x[3] = 300 + xa;
	y1[0] = 450; y1[1] = 450 + ya; y1[2] = 450 - ya; y1[3] = 450;
	y2[0] = 400; y2[1] = 400 + ya; y2[2] = 400 - ya; y2[3] = 400;
	y3[0] = 350; y3[1] = 350 + ya; y3[2] = 350 - ya; y3[3] = 350;
	for (u = 0; u <= 1; i++, u += 0.02)
	{
		//Pu=p0(1-u)3+p13u(1-u)2+p23 u2(1-u)+p3u3
		xt[i] = x[0] * pow((1 - u), 3) + x[1] * 3 * u*pow(1 - u, 2) + x[2] * 3 * u*u*(1 - u) + x[3] * pow(u, 3);
		yt1[i] = y1[0] * pow((1 - u), 3) + y1[1] * 3 * u*pow(1 - u, 2) + y1[2] * 3 * u*u*(1 - u) + y1[3] * pow(u, 3);
		yt2[i] = y2[0] * pow((1 - u), 3) + y2[1] * 3 * u*pow(1 - u, 2) + y2[2] * 3 * u*u*(1 - u) + y2[3] * pow(u, 3);
		yt3[i] = y3[0] * pow((1 - u), 3) + y3[1] * 3 * u*pow(1 - u, 2) + y3[2] * 3 * u*u*(1 - u) + y3[3] * pow(u, 3);
	}
	glColor3f(1, 0, 0);
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i < 200; i++)
	{
		glVertex2d(xt[i], yt1[i]);
		glVertex2d(xt[i], yt2[i]);
	}
	glEnd();
	glColor3f(0, 1, 0);
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i < 200; i++)
	{
		glVertex2d(xt[i], yt2[i]);
		glVertex2d(xt[i], yt3[i]);
	}
	glEnd();
	//draw the pole
	glColor3f(1, 1, 1);
	glRecti(90, 450, 100, 50);
	glFlush();

}

void idfun()
{
	if (ya > -50 && yflag == 1)
		ya = ya - 0.2;
	if (ya <= -50 && yflag == 1)
		yflag = 0;

	if (ya < 50 && yflag == 0)
		ya = ya + 0.2;
	if (ya >= 50 && yflag == 0)
		yflag = 1;
	if (xa > -10 && xflag == 1)
		xa = xa - 0.2;
	if (xa <= -10 && xflag == 1)
		xflag = 0;
	if (xa < 10 && xflag == 0)
		xa = xa + 0.2;
	if (xa >= 10 && xflag == 0)
		xflag = 1;

	glutPostRedisplay();

}
int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Wire-Frame Quadric Surfaces");
	init();
	glutDisplayFunc(draw);
	glutIdleFunc(idfun);
	glutMainLoop();
}
