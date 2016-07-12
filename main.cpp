#include <iostream>
#include <windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <gl/glut.h>
#include <math.h>
using namespace std;
const double PI=3.14159;
float k2=0,k=0,k3=0;
int pos=0;

void Circle(int Kat){
glBegin(GL_TRIANGLES);
    for(float f = 0; f<=(2*PI);)
        {
            glVertex3f(0,0,0);
            glVertex3f( cos(f)*.5, sin(f)*.5, 0);
            f+=2*PI/(float)Kat;
            glVertex3f( cos(f)*.5, sin(f)*.5, 0);
        }
glEnd();
}
void Lines(float  x,float y, float xx, float yy,float width)
{
    glLineWidth(width);
    glBegin(GL_LINES);

        glVertex2f(x,y);
        glVertex2f(xx,yy);
    glEnd();
}
void Square()
{
    glBegin(GL_TRIANGLES);
    glVertex3f(-.5,-.5,0);
    glVertex3f(.5,-.5,0);
    glVertex3f(.5,.5,0);
    glVertex3f(-.5,.5,0);
    glVertex3f(-.5,-.5,0);
    glVertex3f(.5,.5,0);
    glEnd();
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
	glColor3f(0.5,0.5,0.5);
	glScalef(20,20,0);
	Square();
	glPopMatrix();


    glPushMatrix();     //tarcza
    glColor3f(1,1,1);
    Circle(36);
    glPopMatrix();


    glPushMatrix();     //kółko
    glColor3f(0,0,0);
    glScalef(0.12,0.12,0);
    Circle(36);
    glPopMatrix();

    glPushMatrix();        //wskazówka i robaczek
        glColor3f(0,0,0);
        glRotatef(-k,0,0,1);
        glTranslatef(0,0.25,0);
        glPushMatrix();
            glScalef(0.05,0.4,0);
            Square();
        glPopMatrix();

        glPushMatrix();     //robaczek
            glPushMatrix();
            glColor3f(1,0.3,0.3);
                glTranslatef(-0.025,-0.2,0);
                    if(k2<=0.4)
                    glTranslatef(0,k2,0);
                    else
                    glTranslatef(0,0.4+k3,0);
            glScalef(0.01,0.01,0);
            Circle(36);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();


    glPushMatrix();        //wskazówka minutowa
        glColor3f(0,0,0);
        glRotatef(-60*k,0,0,1);
        glTranslatef(0,0.25,0);
        glPushMatrix();
            glScalef(0.02,0.4,0);
            Square();
        glPopMatrix();
    glPopMatrix();


    glutSwapBuffers();


}
void Idle()
{
    k+=0.1;

    if(k2<=0.4)
    {
        k3=0;
        k2+=0.001;
    }

    else
    {
        if(k3>=-0.4)
            k3-=0.001;
        else
            k2=0;
    }




    glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500,100);
	glutInitWindowSize(900,900);
	glutCreateWindow("Koparka");
	glutDisplayFunc(renderScene);
	glutIdleFunc(Idle);
	glutMainLoop();
}
