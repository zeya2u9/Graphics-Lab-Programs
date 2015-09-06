//just_draw.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<Windows.h>

#ifdef __APPLE__
#include<GLUT/glut.h>
#include<openGL/openGL.h>

#else
#include<GL/glut.h>
#endif
#include<stdio.h>
float temp_x,temp_y,ball_pos[1][2];
int flag=1,count=0,i=0,flagg=0;
GLdouble ox,oy,oz,*worldX,*worldY,*worldZ,amp;
GLfloat x1=-1.0,x2=1.0,y1=0.0;

 GLboolean isLeftKeyPressed,isRightKeyPressed;
 GLboolean leftButton,rightButton,middleButton;
 GLboolean hold,release;
void init()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_FLAT);
}
void reshape (int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
}
void drawPoints(GLfloat x,GLfloat y)
{
    glColor3f(0.0,0.5,0.0);    
   
	glPointSize(5.0);
    glBegin(GL_POINTS);
		glColor3f(0.0,0.8,0.0);   
		glVertex2f(x, y);
	glEnd();
	glFlush();	
}
//Mouse activities
void Mouse(int button,int state,int x,int y)
{
	if(state == GLUT_DOWN)
	{
		flagg=1;
	switch (button) {
        case GLUT_LEFT_BUTTON:
            leftButton = true;
			if(!rightButton)
				rightButton=false;
			printf("\nleft button has been pressed\nAnd mouse position is: (x,y)=(%d , %d)",x,y);
            break;
        case GLUT_RIGHT_BUTTON:
           rightButton = true;
			if(!leftButton)
				leftButton=false;
			printf("\nRight button has been pressed\nAnd mouse position is: (x,y)=(%d , %d)",x,y);
            break;
		}
	}
	else
	{
		
		flag=0;
		printf("\nMouse released  Total points=%d",count);
	}
}
//Motion activities
void MMotion(int x,int y)
{
	printf("\nMotionn (x,y)=(%d,%d)",x,y);
	temp_x=(float)x;
	temp_y=(float)y;

	if (flagg==1) {
	GLint viewport[4]; //var to hold the viewport info
        GLdouble modelview[16]; //var to hold the modelview info
        GLdouble projection[16]; //var to hold the projection matrix info
        GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates
        GLdouble worldX, worldY, worldZ; //variables to hold world x,y,z coordinates
 
        glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); //get the modelview info
        glGetDoublev( GL_PROJECTION_MATRIX, projection ); //get the projection matrix info
        glGetIntegerv( GL_VIEWPORT, viewport ); //get the viewport info
	winX = (float)x;
    winY = (float)viewport[3] - (float)y;
	winZ = 0;
	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &worldX,&worldY,&worldZ);
	x1=GLfloat(worldX);
	y1=GLfloat(worldY);
	ball_pos[1][0]=x1;
	ball_pos[1][1]=y1;
	i++;
	printf("\nHERE IS X=%f AND Y=%f",x1,y1);
 }
	count++;
}
void update()
{

}

void display()
{
    init();
	glColor3f(0.0,1.0,0.0);
	x1=ball_pos[1][0];
	y1=ball_pos[1][1];
	drawPoints(x1,y1);
	update();
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutCreateWindow("Drawing_Pane");

    glutDisplayFunc(display);
    glutIdleFunc(display);   
    glutReshapeFunc(reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(MMotion);   
	glutMainLoop();
    
    return(0);
}
