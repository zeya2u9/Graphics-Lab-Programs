// Mouse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#ifdef __APPLE__
#include<GLUT/glut.h>
#include<openGL/openGL.h>

#else
#include<GL/glut.h>
#endif
#include<stdio.h>

float temp_x,temp_y,ball_pos[60][2];
int flag=1,count=0,i=0,flagg=0;
GLdouble ox,oy,oz,*worldX,*worldY,*worldZ,amp,x1=-2.0,x2=2.0,y1=0.0;

 GLboolean isLeftKeyPressed,isRightKeyPressed;
 GLboolean leftButton,rightButton,middleButton;
 GLboolean hold,release;
/*void initRendering()
{
    glEnable(GL_DEPTH_TEST);
}*/

void reshape(int w,int h)
{
    glViewport(0,0,w,h);   
    glMatrixMode(GL_PROJECTION);    
    glLoadIdentity(); 
    gluPerspective(45,w/h,1,200);
    
}
void drawBall1()
{
    glColor3f(1.0,0.0,0.0);    
    glPushMatrix();    
    glTranslated(x1,y1,-5.0);
    glutSolidSphere(0.4,20,20);    
    glPopMatrix();
}

void keyPressed(int key, int x, int y) {
    
    switch (key) {
        case GLUT_KEY_LEFT:
            isLeftKeyPressed = true;
            if (!isRightKeyPressed) {
                flag=1;
            }
            break;
        case GLUT_KEY_RIGHT:
            isRightKeyPressed = true;
            if (!isLeftKeyPressed) {
                flag=1;
            }
            break;
    }
}

void handleSpecialKeyReleased(int key, int x, int y) {
   
    switch (key) {
        case GLUT_KEY_LEFT:
            isLeftKeyPressed = false;
            break;
        case GLUT_KEY_RIGHT:
            isRightKeyPressed = false;
            break;
    }
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
		//i=0;
		/*printf("\nTemp_x= %f",temp_x);
		if(temp_x<=300)
			temp_x=temp_x-300;
		else
			temp_x=temp_x-300;
		printf("Ball position_(x1,x2)=(%f,%f) and tepm_x=%f",x1,x2,temp_x);*/
		
	}
}
//Motion activities
void MMotion(int x,int y)
{
	printf("\nMotionn (x,y)=(%d,%d)",x,y);
	temp_x=(float)x;
	temp_y=(float)y;

	/*x1=x1/600;
	y1=1.0-y1/600;*/

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
 
	//get the world coordinates from the screen coordinates
       // gluUnProject( winX, winY, winZ, modelview, projection, viewport, &worldX,&worldY,&worldZ);
		//printf("worldX=%f worldY=%f worldZ=%f",worldX,worldY,worldZ);
		/*near_x=worldX;
		near_y=worldY;*/
		winZ=0.6;
		gluUnProject( winX, winY, winZ, modelview, projection, viewport, &worldX,&worldY,&worldZ);
		//far_x=worldX;
		//far_y=worldY;
	x1=2*worldX;
	y1=2*worldY;
	printf("\nHERE IS X=%f AND Y=%f",x1,y1);
 }
	
	/*if(temp_x<300 && temp_y<300)
	{
		x1-=temp_x/150000;
		y1+=temp_y/150000;
	}
	else if(temp_x>300 && temp_y<300)
	{
		x1+=temp_x/150000;
		y1+=temp_y/150000;
	}
	if(temp_x>300 && temp_y>300)
	{
		x1-=temp_x/150000;
		y1-=temp_y/150000;
	}
	else
	{
		x1+=temp_x/150000;
		y1-=temp_y/150000;
	}
		printf("\nlast point (x1,y1)=(%f,%f)",x1,y1);
	//i++;*/
	count++;
}
void update()
{
		/*if(flag==1)
		{
		x1=ball_pos[0][0];
		y1=ball_pos[0][1];
		}
		//i++;
    /*if(flag==1)
    {
        x1+=0.0005;
        x2-=0.0005;
        /*if(x1>-0.35)
            flag=0;*/
    /*}
    else
    {
        x1-=0.0005;
        x2+=0.0005;
        /*if(x1<-2.0)
            flag=1;*/
   // }
	//printf("Ball position_(x1,x2)=(%f,%f)",x1,x2);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    
    //glShadeModel(GL_SMOOTH);
    drawBall1();
    update();
    
    glutSwapBuffers();
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    
    glutInitWindowSize(600,600);
    
    glutCreateWindow("Collision Window");
    
    //initRendering();
    
    glutDisplayFunc(display);
    
    glutIdleFunc(display);
    
    glutReshapeFunc(reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(MMotion);
    
    glutSpecialFunc(keyPressed);
    //glutSpecialFunc(handleSpecialKeypress);
    glutSpecialUpFunc(handleSpecialKeyReleased);    
	glutMainLoop();
    
    return(0);
}
