#include <gl\glut.h>
#include <math.h>
#include "Ball.h"
#include "vars.h"
#include "Brick.h"

float r_x=50.0, r_y=290.0, r_w=80, r_h=8.0;
int mouse_x;

Ball ball(r_y, 5);
Brick brick[10][15];

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.2, 0.8, 0.1);
	glRectf(r_x, r_y, r_x+r_w, r_y+r_h);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		for(float i=0; i<2*3.14; i+=3.14/4)
		{
			glVertex2f(ball.x+ball.r*sin(i), ball.y+ball.r*cos(i));
		}
	glEnd();
	glColor3f(0.1, 0.2, 0.8);
	glBegin(GL_QUADS);
		for(int i=0; i<10; i++)
		{
			for(int j=0; j<15; j++)
			{
				Brick &b=brick[i][j];
				if(b.active)
				{
					glVertex2f(b.col*b.w+1, b.row*b.h+1);
					glVertex2f(b.col*b.w+b.w-1, b.row*b.h+1);
					glVertex2f(b.col*b.w+b.w-1, b.row*b.h+b.h-1);
					glVertex2f(b.col*b.w+1, b.row*b.h+b.h-1);
				}
			}
		}
	glEnd();
	glutSwapBuffers();
}

void Timer(int)
{
	Draw();
	if(ball.active)
		ball.move();
	glutTimerFunc(33, Timer, 0);
}

void MousePress(int button, int state, int x, int y)
{
	if(button==GLUT_LEFT_BUTTON && !ball.active)
	{
		ball.active=true;
		ball.dx=4;
		ball.dy=-4;
	}
}

void Mouse(int ax, int ay)
{
	mouse_x=ax;
	r_x=ax-r_w/2;
	if(!ball.active)
	{
		ball.x=r_x+r_w/2;
		ball.y=r_y-ball.r;
	}
}

void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, 300, 300, 0, 1, 0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Acranoid");
	glutDisplayFunc(Draw);
	glutTimerFunc(33, Timer, 0);
	glutPassiveMotionFunc(Mouse);
	glutMouseFunc(MousePress);
	Init();
	for(int i=0; i<10; i++)
		for(int j=0; j<15; j++)
		{
			brick[i][j].active=true;
			brick[i][j].col=j;
			brick[i][j].row=i;
		}
	glutMainLoop();
	return 0;
}
