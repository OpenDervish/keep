#ifndef snvl0
#define snvl0
#include<GL/glut.h>
#define maxx 10			//no of rows in board
#define maxy 10			//no of cols in board
#define dx 70			//x dist of each sqaure in board
#define dy 70			//y dist of each square in board
#define x0 350			//Begin x of board
#define y2 30			//Begin y of board
#define speed 5			//speed of movement of pawns
GLfloat x[maxx+1]={0},y[maxy+1]={0};
//GLfloat p1=x0-40,p2=x0-50,p3=x0-40,p4=x0-30,q1=y2+30,q2=y2+40,q3=y2+50,q4=y2+40;

extern void rect();
extern void Cylinder_draw();
extern void cyl();
class pawns
{
	private:
		float p1,p2,p3,p4,q1,q2,q3,q4,oy,m,c,col1;
		int add,up,tmp,t,flag;
	public:
		pawns(GLfloat,GLfloat,GLfloat,GLint tmp);
		void distance(int);
		void updatey();
		void disp();
		void init(int r);
		void check();
		int check100();
		void tryy(int i);
		void try2(int i);	
};
#endif
