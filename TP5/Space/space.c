#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>


#define NB_COTES_CERCLE 500


/* Dimensions de la fenêtre */
float WINDOW_WIDTH = 1000.0;
float WINDOW_HEIGHT = 1000.0;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


void tailleVirtuelle() {
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-100., 100., -100., -100.);
}


void setVideoMode() {
  if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }

  tailleVirtuelle();
}

void drawLandmark() {
  glBegin(GL_LINES);
    glColor3ub(255, 0, 0);
    glVertex2f(0, 0);
    glVertex2f(1, 0);
    glColor3ub(0, 255, 0);
    glVertex2f(0, 0);
    glVertex2f(0, 1);
  glEnd();
}

void drawCircle() {
  glBegin(GL_LINES);
    float pi = 3.14159;
    for(int i = 0; i < NB_COTES_CERCLE; i++) {
      glVertex2f((cos(2*pi*i/NB_COTES_CERCLE)), (sin(2*pi*i/NB_COTES_CERCLE)));
      glVertex2f((cos(2*pi*(i+1)/NB_COTES_CERCLE)), (sin(2*pi*(i+1)/NB_COTES_CERCLE)));
    }
  glEnd();
}

void drawFilledCircle() {
  glBegin(GL_POLYGON);
    float pi = 3.14159;
    for(int i = 0; i < NB_COTES_CERCLE; i++) {
      glVertex2f((cos(2*pi*i/NB_COTES_CERCLE)), (sin(2*pi*i/NB_COTES_CERCLE)));
      glVertex2f((cos(2*pi*(i+1)/NB_COTES_CERCLE)), (sin(2*pi*(i+1)/NB_COTES_CERCLE)));
    }
  glEnd();
}

void drawTinyCircle() {
  glScalef(0.01, 0.01, 1);
  drawFilledCircle();
}

int main() {
  /* Initialisation de la SDL */
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
      fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
      return EXIT_FAILURE;
  }

  setVideoMode();

  /* Titre de la fenêtre */
  SDL_WM_SetCaption("Space", NULL);

  /* Boucle d'affichage */
  int loop = 1;

  float rotate1 = 0;
  float rotate2 = -113;
  float rotate3 = -17;
  float rotate4 = 31;
  float rotate5 = 252;
  float rotate6 = 300;
  float rotate7 = -63;
  float rotate8 = -7;

  while(loop) {

glClear(GL_COLOR_BUFFER_BIT);

    //soleil
    glColor3ub(255, 255, 0);
    glPushMatrix();
      glScalef(5, 5, 0);
      drawTinyCircle();
    glPopMatrix();

    //mercure
    glColor3ub(200, 50, 0);
    glPushMatrix();
      glScalef(0.1, 0.1, 0);
      drawCircle();
    glPopMatrix();
    glPushMatrix();
      glRotatef(rotate1++, 0.0, 0.0, 1.0);
      glTranslatef(0, -0.1, 0);
      glScalef(1, 1, 0);

      drawTinyCircle();
    glPopMatrix();

    //venus
    glColor3ub(255, 100, 0);
    glPushMatrix();
      glScalef(0.13, 0.13, 0);
      drawCircle();
    glPopMatrix();
    glPushMatrix();
      glRotatef(rotate2+=0.9, 0.0, 0.0, 1.0);
      glTranslatef(0, -0.13, 0);
      glScalef(1, 1, 0);
      drawTinyCircle();
    glPopMatrix();

    //terre
    glColor3ub(0, 200, 255);
    glPushMatrix();
      glScalef(0.16, 0.16, 0);
      drawCircle();
    glPopMatrix();
    glPushMatrix();
      glRotatef(rotate3+=0.8, 0.0, 0.0, 1.0);
      glTranslatef(0, -0.16, 0);
      glScalef(1, 1, 0);
      drawTinyCircle();
    glPopMatrix();

    //mars
    glColor3ub(255, 0, 0);
    glPushMatrix();
      glScalef(0.19, 0.19, 0);
      drawCircle();
    glPopMatrix();
    glPushMatrix();
      glRotatef(rotate4+=0.7, 0.0, 0.0, 1.0);
      glTranslatef(0, -0.19, 0);
      glScalef(1, 1, 0);
      drawTinyCircle();
    glPopMatrix();

    //jupiter
    glColor3ub(0, 50, 50);
    glPushMatrix();
      glScalef(0.3, 0.3, 0);
      drawCircle();
    glPopMatrix();
    glPushMatrix();
      glRotatef(rotate5+=0.6, 0.0, 0.0, 1.0);
      glTranslatef(0, -0.3, 0);
      glScalef(3, 3, 0);
      drawTinyCircle();
    glPopMatrix();

    //saturne
    glColor3ub(100, 200, 0);
    glPushMatrix();
      glScalef(0.5, 0.5, 0);
      drawCircle();
    glPopMatrix();
    glPushMatrix();
      glRotatef(rotate6+=0.5, 0.0, 0.0, 1.0);
      glTranslatef(0, -0.5, 0);
      glScalef(3, 3, 0);
      drawTinyCircle();
    glPopMatrix();

    //uranus
    glColor3ub(200, 0, 200);
    glPushMatrix();
      glScalef(0.7, 0.7, 0);
      drawCircle();
    glPopMatrix();
    glPushMatrix();
      glRotatef(rotate7+=0.4, 0.0, 0.0, 1.0);
      glTranslatef(0, -0.7, 0);
      glScalef(3, 3, 0);
      drawTinyCircle();
    glPopMatrix();

    //neptune
    glColor3ub(0, 0, 255);
    glPushMatrix();
      glScalef(0.9, 0.9, 0);
      drawCircle();
    glPopMatrix();
    glPushMatrix();
      glRotatef(rotate8+=0.3, 0.0, 0.0, 1.0);
      glTranslatef(0, -0.9, 0);
      glScalef(3, 3, 0);
      drawTinyCircle();
    glPopMatrix();



    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }
    }
      SDL_GL_SwapBuffers();
  }
/* Liberation des ressources associées à la SDL */
  SDL_Quit();
  return EXIT_SUCCESS;
}
