// practice.cpp : Defines the entry point for the console application.
//

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "stdafx.h"
#include<GL/glut.h>
#include <cmath>

GLdouble x=1,y=600,x3=300,x4=300,y5=350,y6=350;
int flag=0,i,m_x,m_y;
void init()
{
	glClearColor(0,0,0,0);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1,0.0,1,-1,1);
	glutPostRedisplay();
}
void update1()
{
	if(flag==1)
	{
		if(x<600 && y>300)
		{
			x=x+0.07;
			y=y-0.07;
		}
		else
		{
			flag=0;
			
			x=0;
			y=600;
		}

	}
}
void update2()
{
	printf("asdfghjklpoiuytrewqzxcvbnm\n");
	if(flag==0)
	{
		if(x3>1)
		{
			x3-=0.07;
			x4=x3;
			y5+=0.07;
			y6=y5;
		}
		else
		{
			x3=300;x4=300;y5=300;y6=300;
			flag=1;
		}
	}
}
void ball1()
{
	glColor3f(1.0,0.0,0.0);
	glPushMatrix();
		glTranslated(x,300,0);
		glutSolidSphere(10,20,20);
	glPopMatrix();
}
void ball2()
{
	glColor3f(1.0,0.0,0.0);
	glPushMatrix();
		glTranslated(y,300,0);
		glutSolidSphere(10,20,20);
	glPopMatrix();
}
void ball3()
{
	glColor3f(0.0,1.0,0.0);
	glPushMatrix();
		glTranslated(x3,350,0);
		glutSolidSphere(3,20,20);
	glPopMatrix();
}
void ball4()
{
	glColor3f(1.0,0.0,0.0);
	glPushMatrix();
		glTranslated(x4,250,0);
		glutSolidSphere(3,20,20);
	glPopMatrix();
}
void ball5()
{
	glColor3f(1.0,0.0,0.0);
	glPushMatrix();
		glTranslated(y5,350,0);
		glutSolidSphere(3,20,20);
	glPopMatrix();
}
void ball6()
{
	glColor3f(1.0,0.0,0.0);
	glPushMatrix();
		glTranslated(y6,250,0);
		glutSolidSphere(3,20,20);
	glPopMatrix();
}
void ball_main()
{
	printf("flag==%d\n",flag);
	if(flag==1)
	{
		ball1();
		ball2();
		update1();
	}
	else
	{
		
		ball3();
		ball4();
		ball5();
		ball6();
		update2();
	}

}
void text(int x1,int y1,char *s)
{
	glColor3f(0.4,0.6,1.0);
	glRasterPos2d(x1,y1);
	for(i=0;i<20;i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,s[i]);
}

float bx = 0.0, by = 0.55;
bool right =  true;

void move() {
	static float y = by - 0.55;
	y = y + 3.14/10.0;
	//bx = y*0.1;
	//by = sin(y)*0.1 + 0.55;

	if(right) {
		bx += 0.0315;
		if(bx > 1.1) {
			right = false;
		} else {
			by = sin(y)*0.1 + 0.55;
		}
	} else {
		bx -= 0.0315;
		if(bx < -0.1) {
			right = true;
		} else {
			by = sin(y)*0.1 + 0.55 - 0.1;
		}
	}
	for(int i=0;i<0x9000000;i++);
	glutPostRedisplay();
}

void display()
{
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	init();

	glPushMatrix();
	glTranslatef(bx,by,0);
	glutSolidSphere(0.04, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0,0.5,0);
	glLineWidth(5.0);
	glBegin(GL_LINE_STRIP);
	float j = 0.0f;
	for(int i=0;i<1000;i++, j = j+3.14/10.0) {
		glVertex2f(j*0.1, sin(j)*0.1);
		//printf("%d %f", j, sin(j));
	}
	glEnd();
	glPopMatrix();

	move();

	glutSwapBuffers();
}
void mouse(int button,int state,int x,int y)
{
	if(state==GLUT_DOWN)
	{
		switch(button)
		{
		case GLUT_LEFT_BUTTON:
			printf("mouse->x=%d y=%d\n",x,600-y);
			break;
		case GLUT_RIGHT_BUTTON:
			printf("mouse->x=%d y=%d\n",x,600-y);
			break;
		
		}
		m_x=x;m_y=600-y;
	}
}
//void ballll()
//{
//	glColor3f(0.0,0.0,1.0);
//	glPushMatrix();
//		glTranslated(m_x,m_y,-20);
//		glutSolidSphere(10,20,20);
//	glPopMatrix();
//}
void motion(int x, int y)
{
	//y=600-y;
	printf("motion-mouse->x=%d y=%d\n",x,600-y);
	m_x=x;
	m_y=600-y;

	//ballll();
	
}
void keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
	case 27: exit(1);
			break;
	default:break;
	}
}
void reshape(int w,int h)
{
	glViewport(0,0,w,h);
	printf("%d %d",w,h);
}
int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Practice");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}

