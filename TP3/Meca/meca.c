#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NB_COTES_CERCLE 100


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
  gluOrtho2D(-150., 150., -150., 150.);
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

void drawRoundedSquare() {
  glPushMatrix();
      glTranslatef(-0.3, 0.3, 0);
      glScalef(0.2, 0.2, 0);
      drawFilledCircle();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0.3, 0.3, 0);
      glScalef(0.2, 0.2, 0);
      drawFilledCircle();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0.3, -0.3, 0);
      glScalef(0.2, 0.2, 0);
      drawFilledCircle();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(-0.3, -0.3, 0);
      glScalef(0.2, 0.2, 0);
      drawFilledCircle();
    glPopMatrix();
  glPushMatrix();
    glScalef(0.6, 1, 0);
    drawSquare();
  glPopMatrix();
  glPushMatrix();
    glScalef(1, 0.6, 0);
    drawSquare();
  glPopMatrix();
}

void drawFirstArm() {
  glColor3ub(255, 255, 0);
  glPushMatrix();
    glRotatef(45, 0.0, 0.0, 1.0);
    glPushMatrix();
      glScalef(20, 20, 0);
      drawCircle();
    glPopMatrix();
      glPushMatrix();
      glTranslatef(60, 0, 0);
        glScalef(10, 10, 0);
        drawCircle();
      glPopMatrix();
      glBegin(GL_LINES);
        glVertex2f( 0, 20);
        glVertex2f( 60, 10);
        glVertex2f( 0, -20);
        glVertex2f( 60, -10);
      glEnd();
    glPopMatrix();
}

void drawSecondArm() {
  glColor3ub(255, 0, 255);
  glPushMatrix();

    glRotatef(-10, 0.0, 0.0, 1.0);
    glPushMatrix();
      glScalef(46, 6, 0);
      drawSquare();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(-20, 0, 0);
      glScalef(10, 10, 0);
      drawRoundedSquare();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(20, 0, 0);
      glScalef(10, 10, 0);
      drawRoundedSquare();
    glPopMatrix();
  glPopMatrix();

}

void drawThirdArm() {
  glColor3ub(0, 255, 255);
  glPushMatrix();

    glRotatef(35, 0.0, 0.0, 1.0);
    glPushMatrix();
      glScalef(40, 4, 0);
      drawSquare();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(-20, 0, 0);
      glScalef(6, 6, 0);
      drawRoundedSquare();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(20, 0, 0);
      glScalef(4, 4, 0);
      drawFilledCircle();
    glPopMatrix();
  glPopMatrix();

}

int main() {
  /* Initialisation de la SDL */
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
      fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
      return EXIT_FAILURE;
  }

  setVideoMode();

  /* Titre de la fenêtre */
  SDL_WM_SetCaption("Mecanique", NULL);

  /* Boucle d'affichage */
  int loop = 1;
  int rotate1 = 45;
  int rotate2 = -10;
  int rotate3 = 35;
  int rotate4 = -45;
  int rotate5 = 5;
  while(loop) {
    /*drawFirstArm();
    drawSecondArm();
    drawThirdArm();*/

    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
      glRotatef(rotate1++, 0.0, 0.0, 1.0);
      drawFirstArm();
      glPushMatrix();
        glTranslatef(42.5, 42.5, 0);
        glRotatef(rotate2++, 0.0, 0, 1.0);
        glTranslatef(20, -3, 0);
        drawSecondArm();
        glPushMatrix();
          glTranslatef(20, -4, 0);
          glRotatef(rotate3++, 0.0, 0.0, 1.0);
          glTranslatef(17, 12, 0);
          drawThirdArm();
        glPopMatrix();
        glPushMatrix();
          glTranslatef(20, -4, 0);
          glRotatef(rotate4+2, 0.0, 0.0, 1.0);
          glTranslatef(17, 12, 0);
          drawThirdArm();
        glPopMatrix();
        glPushMatrix();
          glTranslatef(20, -4, 0);
          glRotatef(rotate5+4, 0.0, 0.0, 1.0);
          glTranslatef(17, 12, 0);
          drawThirdArm();
        glPopMatrix();
      glPopMatrix();
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
