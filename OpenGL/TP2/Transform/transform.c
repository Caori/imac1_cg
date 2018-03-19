#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define NB_COTES_CERCLE 100


/* Dimensions de la fenêtre */
float WINDOW_WIDTH = 800.0;
float WINDOW_HEIGHT = 600.0;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


void tailleVirtuelle() {
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-4., 4., -3., 3.);
}


void setVideoMode() {
  if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }

  tailleVirtuelle();


}


void drawSquare() {
  glBegin(GL_QUADS);
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

double frand_a_b(double a, double b){
  return ( rand()/(double)RAND_MAX ) * (b-a) + a;
}


int main(int argc, char** argv) {
    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    setVideoMode();

    /* Titre de la fenêtre */
    SDL_WM_SetCaption("Formes canoniques", NULL);

    /* Boucle d'affichage */
    int loop = 1;
    while(loop) {
      /*glClear(GL_COLOR_BUFFER_BIT);*/

      /* Placer ici le code de dessin */
      glColor3ub(255, 0, 0);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      drawLandmark();

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(1,2,0);
      glColor3ub(200, 100, 0);
      drawCircle();

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glColor3ub(255, 0, 0);
      glTranslatef(2,0,0);
      glRotatef(45, 0.0, 0.0, 1.0);
      drawSquare();

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glColor3ub(150, 0, 105);
      glRotatef(45, 0.0, 0.0, 1.0);
      glTranslatef(2,0,0);
      drawSquare();

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glColor3ub(150, 0, 105);
      glScalef(0.5,0.5,0);
      srand(time(NULL));
      glTranslatef(frand_a_b(-5, 5),frand_a_b(-5, 5),0);
      drawCircle();

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glColor3ub(120, 110, 0);
      drawSquare();

      SDL_Event e;
      while(SDL_PollEvent(&e)) {
        /* fermer la fenêtre*/
        if(e.type == SDL_QUIT) {
          loop = 0;
          break;
        }

        if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
          float x = (e.button.x/WINDOW_WIDTH)*8 - 4;
          float y = (e.button.y/WINDOW_HEIGHT)*6 - 3;
          glTranslatef(x, -y, 0);
          printf("%f, %f\n", x, y);
          drawSquare();
        }
        if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT) {
          printf("clic droit\n");
          if(e.type == SDL_MOUSEBUTTONDOWN && e.type == SDL_MOUSEMOTION) { //marche pas ???
            printf("la souris bouge\n");
            float x = (e.button.x/WINDOW_WIDTH)*8 - 4;
            float y = (e.button.y/WINDOW_HEIGHT)*6 - 3;
            glRotatef(x, 0.0, 0.0, 1.0);
            printf("%f, %f\n", x, y);
            drawSquare();
          }
        }
      }
        SDL_GL_SwapBuffers();
    }
  /* Liberation des ressources associées à la SDL */
    SDL_Quit();
    return EXIT_SUCCESS;
}
