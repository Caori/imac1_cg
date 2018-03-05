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
  gluOrtho2D(-1., 1., -1., 1.);
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

void drawSquare() {
  glBegin(GL_QUADS);
    glVertex2f( -0.5, -0.5);
    glVertex2f( -0.5, +0.5);
    glVertex2f( +0.5, +0.5);
    glVertex2f( +0.5, -0.5);
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


int main() {
  /* Initialisation de la SDL */
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
      fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
      return EXIT_FAILURE;
  }

  setVideoMode();

  /* Titre de la fenêtre */
  SDL_WM_SetCaption("Clock", NULL);

  /* Boucle d'affichage */
  int loop = 1;

  while(loop) {
    int angle1 = 0;
    int angle2 = 0;
    int secPos = -90;
    int minPos = 45;
    int hourPos = 45;

    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);

    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3ub(255, 255, 255);
    drawFilledCircle();
    glColor3ub(0, 0, 0);

    //gradations des heures
    for(int i = 0; i < 12; i++) {
      angle1 = angle1+30;
      glPushMatrix();
        glRotatef(angle1, 0.0, 0.0, 1.0);
        glPushMatrix();
          glScalef(0.1, 0.01, 1);
          glTranslatef(-9, 0, 0);
          drawSquare();
        glPopMatrix();
      glPopMatrix();
    }

    //gradation des minutes
    for(int i = 0; i < 60; i++) {
      angle2 = angle2+6;
      glPushMatrix();
        glRotatef(angle2, 0.0, 0.0, 1.0);
        glPushMatrix();
          glScalef(0.05, 0.005, 1);
          glTranslatef(-18, 0, 0);
          drawSquare();
        glPopMatrix();
      glPopMatrix();
    }

    //aiguille des secondes
    glPushMatrix();
    glRotatef(secPos-(timeinfo->tm_sec)*6 , 0.0, 0.0, 1.0);
      glScalef(0.9, 0.005, 1);
      glTranslatef(-0.5, 0, 0);
      drawSquare();
    glPopMatrix();

    //aiguille des minutes
    glPushMatrix();
    glRotatef(secPos-(timeinfo->tm_min)*6, 0.0, 0.0, 1.0);
      glScalef(0.7, 0.008, 1);
      glTranslatef(-0.5, 0, 0);
      drawSquare();
    glPopMatrix();

    //aiguille des heures
    glPushMatrix();
    glRotatef(secPos-(timeinfo->tm_hour)*30, 0.0, 0.0, 1.0);
      glScalef(0.5, 0.01, 1);
      glTranslatef(-0.5, 0, 0);
      drawSquare();
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
