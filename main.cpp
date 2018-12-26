#include <stdlib.h>
#include <math.h>
#include "image.h"
#include "include/irrKlang.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include  <stdbool.h>
#include <vector>
#include <cstring>
#include <string>
#include <GL/glut.h>
#define FILENAME0 "skybox/top.bmp"
#define FILENAME1 "skybox/back.bmp"
#define FILENAME2 "skybox/left.bmp"
#define FILENAME3 "skybox/front.bmp"
#define FILENAME4 "skybox/right.bmp"
#define FILENAME5 "skybox/bottom.bmp"
#define FILENAME6 "skybox/moon.bmp"
/*Bafer za tastaturu*/
static bool keyBuffer[128];
/*Nizovi za teksture*/
static GLuint names[7];
static GLuint portalTex[8];

using namespace std;
float ugao = 0.0;
irrklang::ISoundEngine* engine;
int pause = 0;
/*Rotacije i kretanje*/
float linix=0.0f;
float liniz=-1.0f;
float liniy=-10.0f;
float x1=0.0f, z1=0.0f;
/*Normale kamere*/
GLdouble ykor=2.0;
GLdouble korj=1.0f;
GLdouble korjz=0;

float deltaAngle = 0.0f;
float deltaAngley = 0.0f;
float i = 0;
int texNum = 0;
int crt = 0;
int xrot=1;
int yrot=0;
int l = 0;
static void teksture(void);
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
void portali_draw();
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
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);
    glutGameModeString("1366x768:32@60");
    if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
        glutEnterGameMode();
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutIdleFunc(on_display);
    glutKeyboardFunc(on_keyPress);
    glutKeyboardUpFunc(on_keyRelease);
    glutPassiveMotionFunc(mouseMove);
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    engine = irrklang::createIrrKlangDevice();
    engine->setSoundVolume(0.5f);
    if(!engine)
      return 0;
    teksture();

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

    engine->play2D("gemno.mp3", true);
    glutMainLoop();

    engine->drop();
    return 0;
}

/*Ucitavanje tekstura*/
static void teksture(void)
{
  Image * image;
  glEnable(GL_TEXTURE_2D);

  glTexEnvf(GL_TEXTURE_ENV,
            GL_TEXTURE_ENV_MODE,
            GL_REPLACE);

  image = image_init(0, 0);
  image_read(image, FILENAME0);

  glGenTextures(7, names);

  glBindTexture(GL_TEXTURE_2D, names[0]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,image->width, image->height, 0,GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

  image_read(image, FILENAME1);
  glBindTexture(GL_TEXTURE_2D, names[1]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,image->width, image->height, 0,GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

  image_read(image, FILENAME2);
  glBindTexture(GL_TEXTURE_2D, names[2]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,image->width, image->height, 0,GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

  image_read(image, FILENAME3);
  glBindTexture(GL_TEXTURE_2D, names[3]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,image->width, image->height, 0,GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

  image_read(image, FILENAME4);
  glBindTexture(GL_TEXTURE_2D, names[4]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,image->width, image->height, 0,GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

  image_read(image, FILENAME5);
  glBindTexture(GL_TEXTURE_2D, names[5]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,image->width, image->height, 0,GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

  image_read(image, FILENAME6);
  glBindTexture(GL_TEXTURE_2D, names[6]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,image->width, image->height, 0,GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

  glGenTextures(8, portalTex);
  for(int i =0; i < 8;i++)
    {
        std::string line;
        line += "skybox/portal/";
        line += std::to_string(i);
        line += ".bmp";
        char* imete = new char[line.length()+1];
        std::strcpy(imete,line.c_str());
        image_read(image, imete);
        glBindTexture(GL_TEXTURE_2D, portalTex[i]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,image->width, image->height, 0,GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    }

  glBindTexture(GL_TEXTURE_2D, 0);
  image_done(image);
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
    case 109:
        if(pause == 0)
        {
            engine->setAllSoundsPaused(true);
            pause = 1;
        }
        else
        {
            engine->setAllSoundsPaused(false);
            pause = 0;
        }
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
/*Kretanje*/
void kretanje()
{
  float fraction = 0.2f;
  if(z1 >= 240)
    fraction = 0;
  if(korjz == 0)
  {
    if(keyBuffer[119])
    {
      x1+=linix*fraction;
      z1+=liniz*fraction;
    }
    if(keyBuffer[97])
    {
      if(z1 <= 240)
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
      if(z1 <= 240)
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

/*Kontrola kamere*/
void mouseMove(int x, int y) {
  std::cout << "x: " << x << " y: " << y << std::endl;
  yrot=y;
  if(y<=495)
    glutWarpPointer(x,496);
  if(x>=1300 || x<=55)
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
    gluPerspective(80, (float) width / height, 1, 1500);

}
/*on_display*/
static void on_display(void)
{
    glDisable(GL_TEXTURE_2D);
    kolizija();
    //std::cout << "x: " << x1 << " z: " << z1 <<" y: "<<ykor <<std::endl;
    kretanje();
    i = i + 0.75;
    if(i==360)
      i=0;
    if(texNum == 8)
      texNum = 0;
    if(crt == 3)
      crt=0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-36,18.5,25,
              36,18.5,25,
              0,-1,0);

    glLoadIdentity();
    gluLookAt(x1,ykor,z1,
              x1+linix,ykor+liniy,z1+liniz,
              0.0f,korj,korjz);
    GLfloat light_position[] = { 10, 5, 15, 1 };
    GLfloat light_position2[] = { 0, 40, 0, 1 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
    glDisable(GL_CULL_FACE);
    /*Prostorija*/
    glPushMatrix();
      glRotatef(180,1,0,0);
      glRotatef(180,0,1,0);
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
      glRotatef(180,1,0,0);
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
    glEnable(GL_CULL_FACE);
    /*Prostorija*/

    /*Stepenice*/
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
      glTranslatef(37.5,25,0);
      glRotatef(180, 0, 1, 0);
      glScalef(1.5,1,1);
      stairsFunc(20);
    glPopMatrix();
    /*Stepenice*/

    /*Putevi*/
    glPushMatrix();
      glTranslatef(-2.5,35,25);
      glRotatef(90, 0, 1, 0);
      glScalef(4,1,44.5);
      glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(39.55,25,-30);
      glScalef(10,1,20);
      glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(39.55,10,-11.4);
      glScalef(10,30,24);
      glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(39.5,22,5.5);
      glScalef(10,45,10);
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

    glPushMatrix();
      glTranslatef(-15.5,22,-35);
      glRotatef(-270,0,0,1);
      glScalef(10,1,10);
      glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-23,39,-35);
      glRotatef(-270,0,0,1);
      glScalef(10,1,10);
      glutSolidCube(1);
    glPopMatrix();
    /*Putevi*/

    /*Portali*/
    glDisable(GL_LIGHTING);
    glColor3f(0,0,0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, portalTex[texNum]);
    portali_draw();
    glBindTexture(GL_TEXTURE_2D, 0);
    if(crt == 2)
      texNum++;
    crt++;
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    /*Portali*/
    /*Mjesec*/
    glPushMatrix();
      glTranslatef(0,60,100);
      glRotatef(i,0,1,0);
      glDisable(GL_LIGHTING);
      glColor3f(0,0,0);
      quaSpin();
      glEnable(GL_TEXTURE_2D);
      GLUquadricObj *mjesec = gluNewQuadric();
      gluQuadricDrawStyle(mjesec, GLU_FILL);
      gluQuadricTexture(mjesec, GL_TRUE);
  		glBindTexture(GL_TEXTURE_2D, names[6]);
  		gluQuadricNormals(mjesec, GLU_SMOOTH);
  		gluSphere(mjesec,10,100,100);
      glDisable(GL_TEXTURE_2D);
      glEnable(GL_LIGHTING);
    glPopMatrix();
    glDisable(GL_LIGHTING);
    glPushMatrix();
      glTranslatef(0,60,100);
      glRotatef(i,1,0,0);
      quaSpin();
    glPopMatrix();
    /*Mjesec*/
    /*Omotac*/
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
    glEnable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
    /*Omotac*/
    wallShatter();


    glDisable(GL_LIGHTING);
    glPushMatrix();
      glColor3f(0.2,0.2,0.2);
      glTranslatef(0,48,250);
      glScalef(6,0,6);
      glutSolidCube(1);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    /*Skybox top*/
    glBindTexture(GL_TEXTURE_2D, names[0]);
      glBegin(GL_QUADS);
          glTexCoord2f(0, 0);
          glVertex3f(512, 512, 512);

          glTexCoord2f(1, 0);
          glVertex3f(512, 512, -512);

          glTexCoord2f(1, 1);
          glVertex3f(-512, 512,-512);

          glTexCoord2f(0, 1);
          glVertex3f(-512, 512,512);
      glEnd();
    /*Skybox top*/

    /*Skybox back*/
    glBindTexture(GL_TEXTURE_2D, names[1]);
      glBegin(GL_QUADS);
          glTexCoord2f(0, 0);
          glVertex3f(512, -512, 512);

          glTexCoord2f(1, 0);
          glVertex3f(512,512,512);

          glTexCoord2f(1, 1);
          glVertex3f(-512,512,512);

          glTexCoord2f(0, 1);
          glVertex3f(-512, -512, 512);
      glEnd();
    /*Skybox back*/

    /*Skybox left*/
    glBindTexture(GL_TEXTURE_2D, names[4]);
      glBegin(GL_QUADS);
          glTexCoord2f(0, 0);
          glVertex3f(-512, -512, 512);

          glTexCoord2f(1, 0);
          glVertex3f(-512, 512,512);

          glTexCoord2f(1, 1);
          glVertex3f(-512, 512,-512);

          glTexCoord2f(0, 1);
          glVertex3f(-512, -512, -512);
      glEnd();
    /*Skybox left*/

    /*Skybox front*/
    glBindTexture(GL_TEXTURE_2D, names[3]);
      glBegin(GL_QUADS);
          glTexCoord2f(0, 0);
          glVertex3f(512, -512, -512);

          glTexCoord2f(1, 0);
          glVertex3f(512, 512,-512);

          glTexCoord2f(1, 1);
          glVertex3f(-512, 512,-512);

          glTexCoord2f(0, 1);
          glVertex3f(-512, -512, -512);
      glEnd();
    /*Skybox front*/

    /*Skybox right*/
    glBindTexture(GL_TEXTURE_2D, names[2]);
      glBegin(GL_QUADS);
          glTexCoord2f(0, 0);
          glVertex3f(512, -512, -512);

          glTexCoord2f(1, 0);
          glVertex3f(512, 512,-512);

          glTexCoord2f(1, 1);
          glVertex3f(512, 512,512);

          glTexCoord2f(0, 1);
          glVertex3f(512, -512, 512);
      glEnd();
    /*Skybox right*/

    /*Skybox bottom*/
    glBindTexture(GL_TEXTURE_2D, names[5]);
      glBegin(GL_QUADS);
          glTexCoord2f(0, 0);
          glVertex3f(512, -512, 512);

          glTexCoord2f(1, 0);
          glVertex3f(512, -512,-512);

          glTexCoord2f(1, 1);
          glVertex3f(-512, -512,-512);

          glTexCoord2f(0, 1);
          glVertex3f(-512, -512, 512);
      glEnd();
    /*Skybox bottom*/


    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glutSwapBuffers();
}

/*Omotac*/
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
/*Omotac*/
/*Stepenice*/
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
/*Stepenice*/
/*Kolizija*/
void kolizija()
{
/*Base floor*/
/*Scene box*/
if(ykor < 2.0)
  ykor = 2.0;
if(z1>=38.0f && z1<= 40.0f)
    z1=38;
if(z1<=-38.0f)
    z1=-38;
if(x1>=38.0f)
    x1=38;
if(x1<=-38.0f)
    x1=-38;
/*Scene box*/
/*Prve stepenice*/
  if(x1<=-23.0f && z1 <= 10.5 && z1 >= 6 && ykor <=17.5)
    ykor =-(x1+22)+1;

  if(x1<=-23.0f && z1 <= 10 && z1 >=9.5 && ykor < 17 && ykor > 2.1)
    z1=9.5;
  if(x1<=-23.0f && z1 <= 12.5 && z1>=12 && ykor < 3)
      z1=12.5;
  if(x1<=-23.0f && z1 <= 6.5 && z1 >=5.5 && ykor < 17 && ykor > 2.1)
    z1=6.5;
  if(x1<=-23.0f && z1 <= 4.5 && z1>=4 && ykor < 3)
    z1=4;
/*Prve stepenice*/
  if(x1 >=33 && z1 <= 12.5 && z1>=9 && ykor < 3)
    z1 = 12.5;
  if(x1 >=33 && z1 <= -24 && z1>=-25.2 && ykor < 3)
    z1 = -25.2;
  if(x1 >=32.5 && z1 <= 12.3 && z1>=-25.2 && ykor < 3)
    x1 = 32.5;
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
if((x1 <= 14 || x1>=18)&& z1 <=24 && z1>=23 && ykor >=17.7 && ykor <=32)
  z1 = 24;

if(z1 >=26.5 && z1<=27.5 && ykor >=17.5 && ykor <=32)
  z1 = 26.5;

/*Druge stepenice naopako*/
  if(x1>=19.0f && z1 >=23.5 && z1<=27 && ykor >=12 && ykor <=32)
    ykor =(-x1+50)+1;
  if(x1 >= 22 && ykor <=25 && ykor >=12 && z1 >=26.8 && korj == -1.0f)
    z1 = 26.7;
  if(x1 >= 22 && ykor <=25 && ykor >=12 && z1 <=23.7 && z1 >=23.4 && korj == -1.0f)
    z1 = 23.8;
/*Druge stepenice naopako*/
if((z1 >=-5.9 || z1 <= -9.8) && x1 <= 14.5 && x1 >= 12 && z1 <=23.7 && ykor >=17.5 && ykor <=32)
  x1 = 14.5;

if(x1 >= 17 && x1<=19 && z1 <=23.7 && ykor >=17.5 && ykor <=32)
  x1 = 17;

if(z1 >= -11.7 && z1 <= -9.7 && x1 <= 14.3 && z1 <=23.7 && ykor >=17.5 && ykor <=32)
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
if(x1>=21 && z1 >=23 && z1<=28 && ykor >=38 && ykor <= 100)
  ykor =(x1+18)-1;
if(x1 >= 22 && ykor >=36 && z1 >=26.8 && z1 <= 28)
  z1 = 26.7;
if(x1 >= 22 && ykor >=36 &&  z1 <=23.7 && z1 >=23.3)
  z1 = 23.8;
if((z1 >=-5.9 || z1 <= -9.8) && x1 <= 14.5 && x1 >= 12 && z1 <=23 && ykor >=36)
  x1 = 14.5;

if(x1 >= 17 && x1<=19 && z1 <=23.4 && ykor >=36)
  x1 = 17;

if(z1>=-11 && z1 <= -9.7 && x1 <= 14.3  && z1 <=23.7 && ykor >=36)
  z1=-9.7;

  if(z1 >= -6.2 && x1 <= 14.3 && z1 <=23 && ykor >=36)
      z1=-6.2;

if((x1 <= 14 || x1>=18)&& z1 <=23.7 && z1 >= 23 && ykor >=36)
    z1 = 23.8;

if(z1 >=26.8 && z1 <=28 && ykor >=36)
    z1 = 26.7;

if(z1 >= -9.8 && z1 <= -6.1 && x1 <= -21.7 && z1 <=23.4 && ykor >=36)
    ykor =-(x1-15.3)+1;

if(x1 >= 14.5 && x1 <= 17.5 && z1 <=-27.2 && ykor >=36)
  ykor =-(z1-10)+1;

/*Gornji sprat*/

/*Kosi svet*/
if(x1 <= -20 && z1 <= -18 && ykor <= 23.5 && ykor >=20)
  z1 = -(x1+56)-1;
if(x1 <= -15 && z1 <= -18 && ykor >= 23 && ykor <=23.5)
  ykor = 23;
if(x1 <= -15 && z1 <= -18 && ykor >= 20 && ykor <=20.5)
  ykor = 20.5;
if(x1 >=-16.5 && z1 <= -18 && ykor <= 23.5 && ykor >=20)
  x1=-16.5;

if(x1 <= -27 && z1 <= -18 && ykor >= 37 && ykor <=41)
  z1 = -(x1+63)-1;
if(x1 <= -15 && z1 <= -18 && ykor >= 40.5 && ykor <=41)
  ykor = 40.5;
if(x1 <= -15 && z1 <= -18 && ykor >= 37 && ykor <=37.5)
  ykor = 37.5;

/*Kosi svet*/

if(x1 <= 34 && x1 >= 33 && ykor >=20 && z1 <=12)
  x1=34;
if(z1 <= 11 && z1 >= 10.5  && ykor >=45)
  z1=10.5;

/*Stepenice cilj*/
if(ykor <= 49 && ykor >16 && x1>=33 && z1 <= -1 && z1 >= -20)
  ykor = (z1+51)-1;
/*Stepenice cilj*/


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

/*Portal5-Teleport*/
if(x1 >= -17.5 && x1 <= -17 && ykor <= 25 && ykor >= 19 && z1 <=-35)
{
  z1 = -37;
  ykor=39;
  x1 = -26;

  linix = sin((xrot+2*164)*0.01f);
  liniy = -cos((xrot+2*164)*0.01f);
  glutWarpPointer(xrot+2*164,yrot);
}
if(x1 >= -25 && x1 <= -24.5 && ykor <= 40 && ykor >= 35 && z1 <=-35)
{
  z1 = -37;
  ykor=22.5;
  x1 = -18;

  linix = sin((xrot-2*164)*0.01f);
  liniy = -cos((xrot-2*164)*0.01f);
  glutWarpPointer(xrot-2*164,yrot);
}
/*Portal5-Teleport*/

/*Portal6-Teleport*/
if(x1 <= 38.5 && x1 >= 37.5 && ykor >= 48 && z1 <=9 && z1>=1)
{
  korj = 0;
  korjz= 1;
  z1 = -26.5;
  ykor=38.5;
  x1 = -37;

  linix = sin((xrot+164)*0.01f);
  liniy = -cos((xrot+164)*0.01f);
  glutWarpPointer(xrot+164,yrot);

}
if(x1 >= -38.5 && x1 <= -38 && ykor <= 40 && ykor >= 35 && z1 <=-25)
{
  korjz=0;
  korj=1;
  z1 = 6;
  ykor=48;
  linix = sin((xrot-164)*0.01f);
  liniz = -cos((xrot-164)*0.01f);
  glutWarpPointer(xrot-164,yrot);
  x1 = 37;
}
/*Portal6-Teleport*/

/*Portal7-Teleport*/
if(x1 >= 14 && x1 <= 18 && ykor >= 24 && ykor <= 29 && z1 >=-38.5 && z1<=-38)
{
  korj = 1.0f;
  ykor=48;
  linix = sin((xrot+2*165)*0.01f);
  liniz = -cos((xrot+2*165)*0.01f);
  glutWarpPointer(xrot+2*165,yrot);
  liniy=-liniy;
  z1 = -37.2;
}
if(x1 >= 14 && x1 <= 18 && ykor >= 48 && ykor<=50 && z1 >=-38.5 && z1<=-38)
{
  korj = -1.0f;
  ykor= 29;
  linix = sin((xrot-2*165)*0.01f);
  liniz = -cos((xrot-2*165)*0.01f);
  glutWarpPointer(xrot-2*165,yrot);
  liniy=-liniy;
  z1 = -37.2;
}
/*Portal7-Teleport*/

/*Portal8-Teleport*/
if(x1 >= 34 && x1 <= 38 && ykor >= 29 && ykor <= 33 && z1 >=-38.5 && z1<=-38)
{
  ykor=50;
  x1 = 0;
  z1 = 250;
}
/*Portal8-Teleport*/
}
/*Kolizija*/
/*Polomljen zid*/
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
/*Polomljen zid*/
/*Iscrtavanje portala*/
void portali_draw()
{
  /*Portal1-izlaz*/
  glPushMatrix();
    glTranslatef(-39.9,17.5,25);
    glRotatef(90,0,1,0);
    GLUquadricObj *port = gluNewQuadric();
    gluQuadricDrawStyle(port , GLU_FILL);
    gluQuadricTexture(port , GL_TRUE);
    gluQuadricNormals(port , GLU_SMOOTH);
    gluDisk(port,0,5,100,100);
  glPopMatrix();
  /*----------------------*/
  /*Portal1-izlaz*/
  /*Portal1-ulaz*/
  glPushMatrix();
    glTranslatef(-39.9,17.5,8);
    glRotatef(90,0,1,0);
    gluDisk(port,0,5,100,100);
  glPopMatrix();
  /*Portal1-ulaz*/

  /*Portal2-izlaz*/
  glPushMatrix();
    glTranslatef(39.9,55,25);
    glRotatef(-90,0,1,0);
    gluDisk(port,0,5,100,100);
  glPopMatrix();
  /*Portal2-izlaz*/
  /*Portal2-ulaz*/
  glPushMatrix();
    glTranslatef(39.9,13.5,25);
    glRotatef(-90,0,1,0);
    gluDisk(port,0,5,100,100);
  glPopMatrix();
  /*Portal2-ulaz*/

  /*Portal3-izlaz*/
  glPushMatrix();
    glTranslatef(26,17,-39.9);
    gluDisk(port,0,5,100,100);
  glPopMatrix();
  /*Portal3-izlaz*/
  /*Portal3-ulaz*/
  glPushMatrix();
    glTranslatef(-39.9,55,-8);
    glRotatef(90,0,1,0);
    gluDisk(port,0,5,100,100);
  glPopMatrix();
  /*Portal3-ulaz*/

  /*Portal4-izlaz*/
  glPushMatrix();
    glTranslatef(-39.9,20,-8);
    glRotatef(90,0,1,0);
    gluDisk(port,0,5,100,100);
  glPopMatrix();
  /*Portal4-izlaz*/
  /*Portal4-ulaz*/
  glPushMatrix();
    glTranslatef(-39.9,22,-19);
    glRotatef(90,0,1,0);
    gluDisk(port,0,5,100,100);
  glPopMatrix();
  /*Portal4-ulaz*/

  /*Portal5-izlaz*/
  glPushMatrix();
    glTranslatef(-24,39,-35);
    glRotatef(-90,0,1,0);
    gluDisk(port,0,5,100,100);
  glPopMatrix();
  /*Portal5-izlaz*/
  /*Portal5-ulaz*/
  glPushMatrix();
    glTranslatef(-16.5,22,-35);
    glRotatef(-90,0,1,0);
    gluDisk(port,0,5,100,100);
  glPopMatrix();
  /*Portal5-ulaz*/
  /*Portal6-izlaz*/
  glPushMatrix();
    glTranslatef(-39.9,39,-25);
    glRotatef(90,0,1,0);
    gluDisk(port,0,5,100,100);
  glPopMatrix();
  /*Portal6-izlaz*/
  /*Portal6-ulaz*/
  glPushMatrix();
    glTranslatef(39.9,49,6);
    glRotatef(-90,0,1,0);
    gluDisk(port,0,5,100,100);
  glPopMatrix();
  /*Portal6-ulaz*/

  /*Portal7-izlaz*/
  glPushMatrix();
    glTranslatef(16,50,-39.9);
    gluDisk(port,0,5,100,100);
  glPopMatrix();
  /*Portal7-izlaz*/
  /*Portal7-ulaz*/
  glPushMatrix();
    glTranslatef(16,25,-39.9);
    gluDisk(port,0,5,100,100);
  glPopMatrix();
  /*Portal7-ulaz*/

  /*Portal8-ulaz*/
  glPushMatrix();
    glTranslatef(36,30,-39.9);
    gluDisk(port,0,5,100,100);
  glPopMatrix();
  /*Portal8-ulaz*/
}
/*Iscrtavanje portala*/
