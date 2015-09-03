#ifdef __APPLE__
#include<GLUT/glut.h>
#include<openGL/openGL.h>

#else
#include<GL/glut.h>
#endif
#include<stdio.h>

float x1=-2.0,x2=2.0;
int flag=1;
 GLboolean isLeftKeyPressed,isRightKeyPressed;
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
    
    glTranslatef(x1,0.0,-5.0);
    
    glutSolidSphere(0.4,20,20);
    
    glPopMatrix();
}




void keyPressed(int key, int x, int y) {
    
    switch (key) {
        case GLUT_KEY_LEFT:
            isLeftKeyPressed = true;
            if (!isRightKeyPressed) {
                flag=0;
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

void update()
{
    if(flag==1)
    {
        x1+=0.00005;
        x2-=0.00005;
        /*if(x1>-0.35)
            flag=0;*/
    }
    else
    {
        x1-=0.00005;
        x2+=0.00005;
        /*if(x1<-2.0)
            flag=1;*/
    }
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
    
    glutSpecialFunc(keyPressed);
    //glutSpecialFunc(handleSpecialKeypress);
    glutSpecialUpFunc(handleSpecialKeyReleased);    
	glutMainLoop();
    
    return(0);
}