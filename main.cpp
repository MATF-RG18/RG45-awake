#include <stdlib.h>
#include <math.h>

#include <vector>
#include <algorithm>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include<stdbool.h>
#include <vector>
#include <GL/glut.h>
static bool keyBuffer[128];

using namespace std;

float ugao = 0.0;

float linix=0.0f;
float liniz=-1.0f;
float liniy=-10.0f;
float x1=0.0f, z1=0.0f;
GLdouble ykor=2.0;
GLdouble korj=1.0f;
GLdouble korjz=0;
float deltaAngle = 0.0f;
float deltaAngley = 0.0f;
int i = 0;
int xrot=1;
int yrot=0;
int l = 0;
static void on_keyPress(unsigned char key, int x, int y);
static void on_keyRelease(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
void mouseMove(int x, int y);
void kretanje();
void stairsFunc(int n);
void kolizija();
void wallShatter();
void troSpin();
void quaSpin();

int main(int argc, char **argv)
{

  GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 0.5 };

  GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 0.5  };

  GLfloat light_specular[] = { 0.8, 0.8, 0.8, 0.5  };

  GLfloat ambient_coeffs[] = { 0.5 , 0.5 , 0.5 , 0.5  };

  GLfloat diffuse_coeffs[] = { 0.5 , 0.5 , 0.5 , 0.5  };

  GLfloat specular_coeffs[] = { 0.5 , 0.5 , 0.5 , 0.5  };

  GLfloat shininess = 20;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glutGameModeString("1366x768:32@60");
    glutEnterGameMode();
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

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    //init_resources();
    /*skybox*/


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
  if(korjz == 0)
  {
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
  }
  else
  {
    if(keyBuffer[119])
    {
      x1+=linix*fraction;
      ykor+=liniy*fraction;
    }
    if(keyBuffer[97])
    {
      fraction = 0.05f;
      x1+=deltaAngle*fraction*(-liniy);
      ykor+=deltaAngle*fraction*linix;
    }
    if(keyBuffer[115])
    {
      x1-=linix*fraction;
      ykor-=liniy*fraction;
    }
    if(keyBuffer[100])
    {
      fraction = 0.05f;
      x1-=deltaAngle*fraction*(-liniy);
      ykor-=deltaAngle*fraction*linix;
    }
  }
  glutPostRedisplay();
}


void mouseMove(int x, int y) {
  //std::cout << "x: " << x << " y: " << y << std::endl;
  yrot=y;
  if(y<=495)
    glutWarpPointer(x,496);
  if(x>=1311 || x<=55)
    glutWarpPointer(1366/2,y);
  if(y>=760)
    glutWarpPointer(x,759);
  if(korj == 1.0f)
  {
    xrot = x;
		deltaAngle = x * 0.01f;
    deltaAngley = y *0.01f;
    if(deltaAngley < 5)
      deltaAngley = 5;
		linix = sin(ugao + deltaAngle);
		liniz = -cos(ugao + deltaAngle);
    liniy = -tan(ugao + deltaAngley);
  }
  else if(korj == -1.0f)
  {
    xrot = x;
		deltaAngle = -x * 0.01f;
    deltaAngley = y *0.01f;
    if(deltaAngley < 5)
      deltaAngley = 5;
		linix = sin(ugao + deltaAngle);
		liniz = -cos(ugao + deltaAngle);
    liniy = tan(ugao + deltaAngley);
  }
  else if(korjz == 1.0f)
  {
    xrot = x;
		deltaAngle = y * 0.01f;
    deltaAngley = x *0.01f;
    // if(deltaAngley < 1)
    //   deltaAngley = 6;
		liniy = sin(ugao + deltaAngley);
		linix = -cos(ugao + deltaAngley);
    liniz = -tan(ugao + deltaAngle);
  }
}

static void on_reshape(int width, int height)
{
    glutWarpPointer(1366/2,600);
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80, (float) width / height, 1, 400);

}

static void on_display(void)
{

    kolizija();
    std::cout << "x: " << x1 << " z: " << z1 <<" y: "<<ykor <<std::endl;
    kretanje();
    i = i + 1;
    if(i==360)
      i=0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x1,ykor,z1,
              x1+linix,ykor+liniy,z1+liniz,
              0.0f,korj,korjz);
    GLfloat light_position[] = { 10, 5, 15, 1 };
    GLfloat light_position2[] = { 0, 40, 0, 1 };
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
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
      stairsFunc(16);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-39.5,39,-39.5);
      glRotatef(90, 0, 0, 1);
      glRotatef(90, 1, 0, 0);
      stairsFunc(10);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(26,0.5,-39.5);
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
      glTranslatef(39.5,35.5,25);
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
      glTranslatef(-2.5,35,25);
      glRotatef(90, 0, 1, 0);
      glScalef(4,1,44.5);
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
      glTranslatef(-11,35,-8);
      glRotatef(90, 0, 1, 0);
      glScalef(4,1,50);
      glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
      glTranslatef(16,35,-7);
      glScalef(4,1,60);
      glutSolidCube(1);
    glPopMatrix();
    /*Portal1-izlaz*/
    glPushMatrix();
      glTranslatef(-39,17.5,25);
      glRotatef(90,1,0,0);
      glRotatef(90,0,0,1);
      glBegin(GL_QUADS);
        glVertex3d(-4, 0, -4);
        glVertex3d(4, 0,-4);
        glVertex3d(4, 0,4);
        glVertex3d(-4, 0,4);
      glEnd();
    glPopMatrix();
    /*Portal1-izlaz*/
    /*Portal1-ulaz*/
    glPushMatrix();
      glTranslatef(-39,17.5,8);
      glRotatef(90,1,0,0);
      glRotatef(90,0,0,1);
      glBegin(GL_QUADS);
        glVertex3d(-4, 0, -4);
        glVertex3d(4, 0,-4);
        glVertex3d(4, 0,4);
        glVertex3d(-4, 0,4);
      glEnd();
    glPopMatrix();
    /*Portal1-ulaz*/

    /*Portal2-izlaz*/
    glPushMatrix();
      glTranslatef(39,55,25);
      glRotatef(90,1,0,0);
      glRotatef(90,0,0,1);
      glRotatef(180,0,0,1);
      glBegin(GL_QUADS);
        glVertex3d(-4, 0, -4);
        glVertex3d(4, 0,-4);
        glVertex3d(4, 0,4);
        glVertex3d(-4, 0,4);
      glEnd();
    glPopMatrix();
    /*Portal2-izlaz*/
    /*Portal2-ulaz*/
    glPushMatrix();
      glTranslatef(39,13.5,25);
      glRotatef(90,1,0,0);
      glRotatef(180,0,0,1);
      glRotatef(90,0,0,1);
      glBegin(GL_QUADS);
        glVertex3d(-4, 0, -4);
        glVertex3d(4, 0,-4);
        glVertex3d(4, 0,4);
        glVertex3d(-4, 0,4);
      glEnd();
    glPopMatrix();
    /*Portal2-ulaz*/

    /*Portal3-izlaz*/
    glPushMatrix();
      glTranslatef(26,17,-39);
      glRotatef(90,1,0,0);
      glRotatef(180,0,0,1);
      glBegin(GL_QUADS);
        glVertex3d(-4, 0, -4);
        glVertex3d(4, 0,-4);
        glVertex3d(4, 0,4);
        glVertex3d(-4, 0,4);
      glEnd();
    glPopMatrix();
    /*Portal3-izlaz*/
    /*Portal3-ulaz*/
    glPushMatrix();
      glTranslatef(-39,55,-8);
      glRotatef(90,1,0,0);
      glRotatef(90,0,0,1);
      glBegin(GL_QUADS);
        glVertex3d(-4, 0, -4);
        glVertex3d(4, 0,-4);
        glVertex3d(4, 0,4);
        glVertex3d(-4, 0,4);
      glEnd();
    glPopMatrix();
    /*Portal3-ulaz*/

    /*Portal4-izlaz*/
    glPushMatrix();
      glTranslatef(-39,20,-8);
      glRotatef(90,1,0,0);
      glRotatef(90,0,0,1);
      glBegin(GL_QUADS);
        glVertex3d(-4, 0, -4);
        glVertex3d(4, 0,-4);
        glVertex3d(4, 0,4);
        glVertex3d(-4, 0,4);
      glEnd();
    glPopMatrix();
    /*Portal4-izlaz*/
    /*Portal4-ulaz*/
    glPushMatrix();
      glTranslatef(-39,22,-19);
      glRotatef(90,1,0,0);
      glRotatef(90,0,0,1);
      glBegin(GL_QUADS);
        glVertex3d(-4, 0, -4);
        glVertex3d(4, 0,-4);
        glVertex3d(4, 0,4);
        glVertex3d(-4, 0,4);
      glEnd();
    glPopMatrix();
    /*Portal4-ulaz*/


    glPushMatrix();
      glTranslatef(0,60,100);
      glRotatef(i,0,1,0);
      quaSpin();
      glutSolidSphere(7, 50, 50);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,60,100);
      glRotatef(i,1,0,0);
      quaSpin();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,60,100);
      glRotatef(i,0,0,1);
      quaSpin();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,60,100);
      glRotatef(i,0,1,1);
      quaSpin();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,60,100);
      glRotatef(i,1,0,1);
      quaSpin();
    glPopMatrix();

    wallShatter();

    glutSwapBuffers();
}

void troSpin()
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
}

void quaSpin()
{

  glPushMatrix();
    glTranslatef(22,0,0);
    glScalef(1, 12, 1);
    glutSolidCube(4);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-22,0,0);
    glScalef(1, 12, 1);
    glutSolidCube(4);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0,-22.1,0);
    glRotatef(90,0,0,1);
    glScalef(1, 11.9, 1);
    glutSolidCube(4);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0,22.1,0);
    glRotatef(90,0,0,1);
    glScalef(1, 11.9, 1);
    glutSolidCube(4);
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
/*Base floor*/
/*Scene box*/
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
/*Scene box*/
/*Prve stepenice*/
  if(x1<=-23.0f && z1 < 10.5 && z1 > 6 && ykor <=17.5)
    ykor =-(x1+22)+1;

  if(x1<=-23.0f && z1 <= 11.5 && z1 >=9.5 && ykor < 17)
    z1=9.5;
  if(x1<=-23.0f && z1 <= 12.5 && z1>=12 && ykor < 3)
      z1=12.5;
  if(x1<=-23.0f && z1 <= 6.5 && z1 >=5.5 && ykor < 17)
    z1=6.5;
  if(x1<=-23.0f && z1 <= 4.5 && z1>=4 && ykor < 3)
    z1=4;
/*Prve stepenice*/
  if(x1 >=36 && z1 <= 12.5 && z1>=9 && ykor < 3)
    z1 = 12.5;
  if(x1 >=36 && z1 <= -24 && z1>=-25.2 && ykor < 3)
    z1 = -25.2;
  if(x1 >=35.7 && z1 <= 12.3 && z1>=-25.2 && ykor < 3)
    x1 = 35.7;
/*Druge stepenice*/
  if(x1 <=27.5 && x1 >= 24.3 && z1 <= -24.5 && ykor >= 2 && ykor <= 19)
     ykor =-(z1+23.5)+1;
  if(x1 >=27 && x1 <= 27.5 && z1 <= -24.5 && ykor >= 2 && ykor <= 19)
    x1=27;
  if(x1 <=24.8 && x1 >= 24.3 && z1 <= -24.5 && ykor >= 2 && ykor <= 19)
    x1=24.8;
  if(x1 <=22.5 && x1>=22 && z1 <= -24.5 && ykor < 3)
    x1=22;
  if(x1 <=29.9 && x1>=29.4 && z1 <= -24.5 && ykor < 3)
    x1=29.9;
/*Druge stepenice*/

/*Base floor*/
/* Naopako */
/* Prve stepenice naopako */
  if(x1<=-23.0f && z1 >=23.5 && z1<=27 && ykor >=18 && ykor <=32)
    ykor =(x1+56)-1;
/* Prve stepenice naopako */
if((x1 <= 14 || x1>=18)&& z1 <=23.7 && z1>=19 && ykor >=17.7 && ykor <=32)
  z1 = 23.8;

if(z1 >=26.8 && ykor >=17.5 && ykor <=32)
  z1 = 26.7;

/*Druge stepenice naopako*/
  if(x1>=19.0f && z1 >=23.5 && z1<=27 && ykor >=12 && ykor <=32)
    ykor =(-x1+50)+1;
  if(x1 >= 22 && ykor <=25 && ykor >=12 && z1 >=26.8 && korj == -1.0f)
    z1 = 26.7;
  if(x1 >= 22 && ykor <=25 && ykor >=12 && z1 <=23.7 && korj == -1.0f)
    z1 = 23.8;
/*Druge stepenice naopako*/
if((z1 >=-5.9 || z1 <= -9.8) && x1 <= 14.5 && x1 >= 12 && z1 <=23.7 && ykor >=17.5 && ykor <=32)
  x1 = 14.5;

if(x1 >= 17 && z1 <=23.7 && ykor >=17.5 && ykor <=32)
  x1 = 17;

if(z1 >= -10.7 && z1 <= -9.7 && x1 <= 14.3 && z1 <=23.7 && ykor >=17.5 && ykor <=32)
  z1=-9.7;

if(z1 >= -6.2 && x1 <= 14.3 && z1 <=23.7 && ykor >=17.5 && ykor <=32)
    z1=-6.2;
/*Trece stepenice naopako*/
if(z1 >= -9.8 && z1 <= -6.1 && x1 <= -28.5 && z1 <=23.7 && ykor >=17.5 && ykor <=32)
    ykor =(x1+61.5)-1;
/*Trece stepenice naopako*/

/*Cetvrte stepenice naopako*/
if(x1 >= 14.5 && x1 <= 17.5 && z1 <=-34.7 && ykor >=17.5 && ykor <=32)
  ykor =(z1+67.5)-1;
/*Cetvrte stepenice naopako*/
/* Naopako */

/*Gornji sprat*/
if(x1>=21 && z1 >=23.5 && z1<=27 && ykor >=38 && ykor <= 100)
  ykor =(x1+18)-1;
if(x1 >= 22 && ykor >=36 && z1 >=26.8 )
  z1 = 26.7;
if(x1 >= 22 && ykor >=36 &&  z1 <=23.7 )
  z1 = 23.8;
if((z1 >=-5.9 || z1 <= -9.8) && x1 <= 14.5 && x1 >= 12 && z1 <=23 && ykor >=36)
  x1 = 14.5;

if(x1 >= 17 && z1 <=23.4 && ykor >=36)
  x1 = 17;

if(z1 <= -9.7 && x1 <= 14.3 && z1 <=23.7 && ykor >=36)
  z1=-9.7;

  if(z1 >= -6.2 && x1 <= 14.3 && z1 <=23 && ykor >=36)
      z1=-6.2;

if((x1 <= 14 || x1>=18)&& z1 <=23.7 && z1>=19 && ykor >=36)
    z1 = 23.8;

if(z1 >=26.8 && ykor >=36)
    z1 = 26.7;

if(z1 >= -9.8 && z1 <= -6.1 && x1 <= -21.7 && z1 <=23.4 && ykor >=36)
    ykor =-(x1-15.3)+1;

if(x1 >= 14.5 && x1 <= 17.5 && z1 <=-27.2 && ykor >=36)
  ykor =-(z1-10)+1;

/*Gornji sprat*/


/*Portal1-Teleport*/
if(x1 >= -39 && x1 <= -38 && ykor >= 5 && ykor <= 20 && z1 >=6 && z1<=10)
{
  z1 = 25;
  korj = -1.0f;
  ykor=18.5;
  linix=-linix;
  liniz=liniz;
  liniy=-liniy;
  x1 = -37;
}
if(x1 >= -39 && x1 <= -38 && ykor >= 17.7 && ykor<=20 && z1 >=23 && z1<=28)
{
  z1 = 8;
  korj = 1.0f;
  ykor= 17.2;
  linix=-linix;
  liniz=liniz;
  liniy=-liniy;
  x1 = -37;
}
/*Portal2-Teleport*/
if(x1 <= 38.5 && x1 >= 37.5 && ykor >= 12 && ykor<=30 && z1 >=23 && z1<=28)
{
  z1 = 25;
  korj = 1.0f;
  ykor=53;
  linix=-linix;
  liniy=-liniy;
  x1 = 37;

}
if(x1 <= 38.5 && x1 >= 37.5 && ykor >= 52 && z1 >=23 && z1<=28)
{
  z1 = 25;
  korj = -1.0f;
  ykor= 13.5;
  linix=-linix;
  liniy=-liniy;
  x1 = 37;
}
/*Portal2-Teleport*/

/*Portal3-Teleport*/
if(x1 <= 28 && x1 >= 25 && ykor >= 15 && ykor<=19 && z1 <=-38)
{
  z1 = -8;
  ykor=53;
  linix = sin((xrot+164)*0.01f);
  liniz = -cos((xrot+164)*0.01f);
  glutWarpPointer(xrot+164,yrot);
  x1 = -37;

}
if(x1 >= -38.5 && x1 <= -37.5 && ykor >= 54 && z1 <=-6 && z1>=-10)
{
  z1 = -37;
  ykor=16;
  linix = sin((xrot-164)*0.01f);
  liniz = -cos((xrot-164)*0.01f);
  glutWarpPointer(xrot-164,yrot);
  x1 = 26;
}
/*Portal3-Teleport*/


/*Portal4-Teleport*/
if(x1 >= -38.5 && x1 <= -37.5 && ykor <= 23 && ykor >= 17 && z1 <=-6 && z1>=-10)
{
  korj = 0;
  korjz= 1;
  z1 = -19;
  ykor=21;
  x1 = -37;

  linix = sin((xrot+164)*0.01f);
  liniy = -cos((xrot+164)*0.01f);
  glutWarpPointer(xrot+164,yrot);

}
if(x1 >= -38.5 && x1 <= -37.5 && ykor <= 23 && ykor >= 18 && z1 <=-17 && z1>=-21)
{
  korjz=0;
  korj=-1;
  z1 = -8;
  ykor=19;
  linix = sin((xrot-164)*0.01f);
  liniz = -cos((xrot-164)*0.01f);
  glutWarpPointer(xrot-164,yrot);
  x1 = -37;
}
/*Portal4-Teleport*/


}

void wallShatter()
{
    glBegin(GL_QUADS);
      glVertex3d(40, 0,40);
      glVertex3d(20, 0,40);
      glVertex3d(16, 32,40);
      glVertex3d(22,32,40);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3d(20, 0,40);
      glVertex3d(-36, 0,40);
      glVertex3d(-12, 15,40);
      glVertex3d(8,15,40);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3d(-40, 0,40);
      glVertex3d(-40, 56,40);
      glVertex3d(-24, 52,40);
      glVertex3d(-16,32,40);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3d(-16, 56,40);
      glVertex3d(-40, 68,40);
      glVertex3d(-40, 80,40);
      glVertex3d(-32,80,40);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3d(0, 60,40);
      glVertex3d(-8, 60,40);
      glVertex3d(-34, 80,40);
      glVertex3d(4,80,40);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3d(24, 64,40);
      glVertex3d(8, 60,40);
      glVertex3d(0, 80,40);
      glVertex3d(24,80,40);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3d(40, 68,40);
      glVertex3d(32, 64,40);
      glVertex3d(20, 80,40);
      glVertex3d(40,80,40);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3d(20, 40,40);
      glVertex3d(8, 56,40);
      glVertex3d(40, 64,40);
      glVertex3d(40,56,40);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3d(40, 24,40);
      glVertex3d(32, 20,40);
      glVertex3d(24, 32,40);
      glVertex3d(40,52,40);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3d(40, 0,40);
      glVertex3d(32, 16,40);
      glVertex3d(36, 16,40);
      glVertex3d(40,24,40);
    glEnd();
}
