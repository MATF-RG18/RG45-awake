#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include<stdbool.h>
static bool keyBuffer[128];

float ugao = 0.0;

float linix=0.0f;
float liniz=-1.0f;
float liniy=1.0f;
float x1=0.0f, z1=0.0f;
GLdouble ykor=2.0;
float deltaAngle = 0.0f;
float deltaAngley = 0.0f;
int xOrigin = -1;
int i = 0;

static void on_keyPress(unsigned char key, int x, int y);
static void on_keyRelease(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
void mouseMove(int x, int y);
void kretanje();
void stairsFunc(int n);
void ObjectFunc();
void kolizija();

int main(int argc, char **argv)
{

  GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };

  GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };

  GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

  GLfloat ambient_coeffs[] = { 0.7, 0.7, 0.7, 1 };

  GLfloat diffuse_coeffs[] = { 1, 1, 1, 1 };

  GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

  GLfloat shininess = 30;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutIdleFunc(on_display);
    glutKeyboardFunc(on_keyPress);
    glutKeyboardUpFunc(on_keyRelease);
    glutPassiveMotionFunc(mouseMove);
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2);
    glutSetCursor(GLUT_CURSOR_NONE);
    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);


    //init_resources();
    glutMainLoop();

    return 0;
}

static void on_keyPress(unsigned char key, int x, int y)
{

    switch (key) {
    case 27:
        exit(0);
        break;
    case 32:
        glutFullScreen();
        break;
    case 119:
        keyBuffer[119]=true;
        break;
    case 97:
        keyBuffer[97]=true;
        break;
    case 115:
        keyBuffer[115]=true;
        break;
    case 100:
        keyBuffer[100]=true;
        break;
    }
}

static void on_keyRelease(unsigned char key, int x, int y)
{
    float fraction = 0.5f;
    switch (key) {
    case 119:
        keyBuffer[119]=false;
        break;
    case 97:
        keyBuffer[97]=false;
        break;
    case 115:
        keyBuffer[115]=false;
        break;
    case 100:
        keyBuffer[100]=false;
        break;
    }
}

void kretanje()
{
  float fraction = 0.2f;
  if(keyBuffer[119])
  {
    x1+=linix*fraction;
    z1+=liniz*fraction;
  }
  if(keyBuffer[97])
  {
    fraction = 0.05f;
    x1-=deltaAngle*fraction*(-liniz);
    z1-=deltaAngle*fraction*linix;
  }
  if(keyBuffer[115])
  {
    x1-=linix*fraction;
    z1-=liniz*fraction;
  }
  if(keyBuffer[100])
  {
    fraction = 0.05f;
    x1+=deltaAngle*fraction*(-liniz);
    z1+=deltaAngle*fraction*linix;
  }
  glutPostRedisplay();
}


void mouseMove(int x, int y) {

		deltaAngle = x * 0.01f;
    deltaAngley = y *0.01f;
		linix = sin(ugao + deltaAngle);
		liniz = -cos(ugao + deltaAngle);
      liniy = -tan(ugao + deltaAngley);
    if(liniy > 20)
      liniy = 20;
    if(liniy < -20)
      liniy = -20;
}

static void on_reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, (float) width / height, 1, 400);

}

static void on_display(void)
{
    kolizija();
    //std::cout << "x: " << x1 << "z: " << z1 <<std::endl;
    kretanje();
    i = i + 1;
    if(i==360)
      i=0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x1,ykor,z1,
              x1+linix,ykor+liniy,z1+liniz,
              0.0f,1.0f,0.0f);
    GLfloat light_position[] = { 0, 0, 0, 1 };
    light_position[0] = 10;
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);


        /*
        glPushMatrix();
          glScalef(-1,-1,-1);
          glutSolidSphere(100, 100, 100);
        glPopMatrix();
        */

    glPushMatrix();
      glRotatef(180,1,0,0);
      glBegin(GL_QUADS);
        glVertex3d(-40, 0, -40);
        glVertex3d(40, 0,-40);
        glVertex3d(40, 0,40);
        glVertex3d(-40, 0,40);
      glEnd();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,40,0);
      glBegin(GL_QUADS);
        glVertex3d(-40, -40, -40);
        glVertex3d(-40, 40,-40);
        glVertex3d(-40, 40,40);
        glVertex3d(-40, -40,40);
      glEnd();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,40,0);
      glRotatef(180,0,1,0);
      glBegin(GL_QUADS);
        glVertex3d(-40, -40, -40);
        glVertex3d(-40, 40,-40);
        glVertex3d(-40, 40,40);
        glVertex3d(-40, -40,40);
      glEnd();
    glPopMatrix();


    glPushMatrix();
      glTranslatef(0,40,0);
      glBegin(GL_QUADS);
        glVertex3d(-40, -40, -40);
        glVertex3d(40, -40,-40);
        glVertex3d(40, 40,-40);
        glVertex3d(-40, 40,-40);
      glEnd();
    glPopMatrix();

    glColor3f(0.2, 0.2, 0.2);

    glPushMatrix();
      glRotatef(90, 0, 1, 0);
      glTranslatef(-8,0.5,-39.5);
      stairsFunc(13);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-39.5,22,-39.5);
      glRotatef(90, 0, 0, 1);
      glRotatef(90, 1, 0, 0);
      stairsFunc(20);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-39.5,39,-39.5);
      glRotatef(90, 0, 0, 1);
      glRotatef(90, 1, 0, 0);
      stairsFunc(10);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(26,0.5,-38.5);
      stairsFunc(12);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-39.5,35,25);
      glRotatef(90, 0, 1, 0);
      glRotatef(180, 0, 0, 1);
      stairsFunc(13);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(39.5,35,25);
      glRotatef(-90, 0, 1, 0);
      glRotatef(180, 0, 0, 1);
      stairsFunc(17);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(39.5,35,25);
      glRotatef(-90, 0, 1, 0);
      stairsFunc(15);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(16,35,-39.5);
      glRotatef(180, 0, 0, 1);
      stairsFunc(5);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(16,35.5,-39.5);
      stairsFunc(10);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-39.5,35,-8);
      glRotatef(90, 0, 1, 0);
      glRotatef(180, 0, 0, 1);
      stairsFunc(10);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-39.5,35.5,-8);
      glRotatef(90, 0, 1, 0);
      stairsFunc(15);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(5.5,35,25);
      glRotatef(90, 0, 1, 0);
      glScalef(4,1,70);
      glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(39.5,25,0);
      glRotatef(180, 0, 1, 0);
      stairsFunc(20);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(39.5,25,-30);
      glScalef(4,1,20);
      glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(39.5,10,-11.4);
      glScalef(4,30,24);
      glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(39.5,10,5.5);
      glScalef(4,69,10);
      glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-20,35,-8);
      glRotatef(90, 0, 1, 0);
      glScalef(4,1,70);
      glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(16,35,-7);
      glScalef(4,1,60);
      glutSolidCube(1);
    glPopMatrix();
/*
    glPushMatrix();
      glTranslatef(5,4,-10);
      glRotatef(90,1,0,0);
      glRotatef(180,0,0,1);
      glBegin(GL_QUADS);
        glVertex3d(-4, 0, -4);
        glVertex3d(4, 0,-4);
        glVertex3d(4, 0,4);
        glVertex3d(-4, 0,4);
      glEnd();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-10,4,-4);
      glRotatef(90,1,0,0);
      glRotatef(90,0,0,1);
      glBegin(GL_QUADS);
        glVertex3d(-4, 0, -4);
        glVertex3d(4, 0,-4);
        glVertex3d(4, 0,4);
        glVertex3d(-4, 0,4);
      glEnd();
    glPopMatrix();
*/
    glPushMatrix();
      glTranslatef(0,40,90);
      glRotatef(i,0,1,0);
      ObjectFunc();
    glPopMatrix();


    glutSwapBuffers();
}

void ObjectFunc()
{
    glPushMatrix();
      glTranslatef(11,0,0);
      glRotatef(30,0,0,1);
      glScalef(1, 12, 1);
      glutSolidCube(4);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,-19,0);
      glRotatef(90,0,0,1);
      glScalef(1, 12, 1);
      glutSolidCube(4);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-11,0,0);
      glRotatef(-30,0,0,1);
      glScalef(1, 12, 1);
      glutSolidCube(4);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,-5,0);
      glutSolidSphere(7, 50, 50);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(21,-18,0);
      glutSolidSphere(5, 50, 50);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-21,-18,0);
      glutSolidSphere(5, 50, 50);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,18,0);
      glutSolidSphere(5, 50, 50);
    glPopMatrix();
}

void stairsFunc(int n)
{
  for(int i=0;i<n;i++)
  {
    glPushMatrix();
      glTranslatef(0,0.5*i,1.2*(n-i-1));
      glScalef(4, i+1, 1.2);
      glutSolidCube(1);
    glPopMatrix();
  }
}
void kolizija()
{
if(ykor < 2.0)
  ykor = 2.0;
if(z1>=38.0f)
    z1=38;
if(z1<=-38.0f)
    z1=-38;
if(x1>=38.0f)
    x1=38;
if(x1<=-38.0f)
    x1=-38;
if(x1<=-23.0f && z1 < 10.5 && z1 > 6)
  ykor =-(x1+22)+1;
if(ykor > 2.5 && z1 >= 10.5)
  z1=10.4;
if(x1<=-23.0f && z1 <= 11.5 && z1 >=11 )
  z1=11.5;
if(ykor > 2.5 && z1 <= 6)
  z1=6.1;
if(x1<=-23.0f && z1 >= 4.5 && z1 <=5 )
  z1=4.5;
}
