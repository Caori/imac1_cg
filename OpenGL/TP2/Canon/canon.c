#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NB_COTES_CERCLE 100

/*#include "list.h"*/


/* Dimensions de la fenêtre */
float WINDOW_WIDTH = 400.0;
float WINDOW_HEIGHT = 400.0;

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

  glClear(GL_COLOR_BUFFER_BIT);
}


void drawSquare(int x, int y) {
  glBegin(GL_QUADS);
    glColor3ub(0, 0, 255);
    /*pour centrer le carré sur l'endroit ou on clique
    glVertex2f((-1 + 2.*x/WINDOW_WIDTH) -0.1, (-(-1 + 2. *y/WINDOW_HEIGHT)) -0.1);
    glVertex2f((-1 + 2.*x/WINDOW_WIDTH) -0.1, (- (-1 + 2. *y/WINDOW_HEIGHT)) +0.1);
    glVertex2f((-1 + 2.*x/WINDOW_WIDTH) +0.1, (- (-1 + 2. * y/WINDOW_HEIGHT)) +0.1);
    glVertex2f((-1 + 2.*x/WINDOW_WIDTH) +0.1, (- (-1 + 2. * y/WINDOW_HEIGHT)) -0.1);
    */
    glVertex2f( -0.5, -0.5);
    glVertex2f( -0.5, +0.5);
    glVertex2f( +0.5, +0.5);
    glVertex2f( +0.5, -0.5);
  glEnd();
}

void drawLandmark() {
  glBegin(GL_LINES);
    glColor3ub(0, 255, 0);
    glVertex2f(-0.1, 0);
    glVertex2f(0.1, 0);
    glColor3ub(255, 0, 0);
    glVertex2f(0, -0.1);
    glVertex2f(0, 0.1);
  glEnd();
}

void drawCircle(int x, int y) {
  glBegin(GL_LINES);
    glColor3ub(255, 0, 0);
    float pi = 3.14159;
    for(int i = 0; i < NB_COTES_CERCLE; i++) {
      glVertex2f((cos(2*pi*i/NB_COTES_CERCLE)), (sin(2*pi*i/NB_COTES_CERCLE)));
      glVertex2f((cos(2*pi*(i+1)/NB_COTES_CERCLE)), (sin(2*pi*(i+1)/NB_COTES_CERCLE)));
    }
  glEnd();
}


int main(int argc, char** argv) {
    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    /* Désactivation du double buffering */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

    setVideoMode();

    /* Titre de la fenêtre */
    SDL_WM_SetCaption("Formes canoniques", NULL);

    /* Boucle d'affichage */
    int mode = 0;
    int loop = 1;
    while(loop) {

      /* Placer ici le code de dessin */
      SDL_Event e;
      while(SDL_PollEvent(&e)) {
        /* fermer la fenêtre*/
        if(e.type == SDL_QUIT) {
          loop = 0;
          break;
        }

        if(e.type == SDL_KEYUP) {
            if(e.key.keysym.sym == SDLK_s)  /* mode carré */
              mode = 1;
            if(e.key.keysym.sym == SDLK_l)  /* mode repère */
              mode = 2;
            if(e.key.keysym.sym == SDLK_c)  /* mode cercle */
              mode = 3;
        }

        if(e.type == SDL_MOUSEBUTTONDOWN) {
            switch(mode) {
              case 1:
                drawSquare(e.button.x, e.button.y);
                break;
              case 2:
                drawLandmark();
                break;
              case 3:
                drawCircle(e.button.x, e.button.y);
                break;
            }
          }
          SDL_GL_SwapBuffers();
        }
      }
  /* Liberation des ressources associées à la SDL */
    SDL_Quit();
    return EXIT_SUCCESS;
}
