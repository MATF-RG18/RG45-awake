#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static bool keyBuffer[128];

float ugao = 0.0;

float linix=0.0f;
float liniz=-1.0f;
float liniy=1.0f;
float x1=0.0f, z1=5.0f;

float deltaAngle = 0.0f;
float deltaAngley = 0.0f;
int xOrigin = -1;

static void on_keyPress(unsigned char key, int x, int y);
static void on_keyRelease(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
void mouseMove(int x, int y);
void kretanje();
void stairsFunc(int n);
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
}

static void on_reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, (float) width / height, 1, 100);
}

static void on_display(void)
{

    /*if(z1>=-10.0f && z1<=-10.2f && x1>=1 && x1<=9)
    {
        z1=-3.8;
        x1=-10;
    }
    if(z1>=-4.0f && z1<=-4.2f && x1>=-14 && x1<=-6)
    {
        z1=-9.8;
        x1=5;
    }*/
    kretanje();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x1,2.0f,z1,
              x1+linix,liniy,z1+liniz,
              0.0f,1.0f,0.0f);

    GLfloat light_position[] = { 0, 0, 0, 1 };
    light_position[0] = 10;
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);


    glPushMatrix();
      glRotatef(180,1,0,0);
      glBegin(GL_QUADS);
        glVertex3d(-20, 0, -20);
        glVertex3d(20, 0,-20);
        glVertex3d(20, 0,20);
        glVertex3d(-20, 0,20);
      glEnd();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0,20,0);
      glBegin(GL_QUADS);
        glVertex3d(-20, -20, -20);
        glVertex3d(-20, 20,-20);
        glVertex3d(-20, 20,20);
        glVertex3d(-20, -20,20);
      glEnd();
    glPopMatrix();


    glPushMatrix();
      glTranslatef(0,20,0);
      glBegin(GL_QUADS);
        glVertex3d(-20, -20, -20);
        glVertex3d(20, -20,-20);
        glVertex3d(20, 20,-20);
        glVertex3d(-20, 20,-20);
      glEnd();
    glPopMatrix();

    glColor3f(0.2, 0.2, 0.2);

    glPushMatrix();
      glRotatef(90, 0, 1, 0);
      glTranslatef(-8,0.5,-19.8);
      stairsFunc(13);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-20,18,-19.8);
      glRotatef(90, 0, 0, 1);
      glRotatef(90, 1, 0, 0);
      stairsFunc(15);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-20,34,-19.8);
      glRotatef(90, 0, 0, 1);
      glRotatef(90, 1, 0, 0);
      stairsFunc(10);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(16,0.5,-20);
      stairsFunc(12);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-19.5,35,15);
      glRotatef(90, 0, 1, 0);
      glRotatef(180, 0, 0, 1);
      stairsFunc(13);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(16,35,-19.5);
      glRotatef(180, 0, 0, 1);
      stairsFunc(5);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(5.5,35,15);
      glRotatef(90, 0, 1, 0);
      glScalef(4,1,20);
      glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(16,35,0);
      glScalef(4,1,34);
      glutSolidCube(1);
    glPopMatrix();

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

    glutSwapBuffers();
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
