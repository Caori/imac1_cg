#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

/* Dimensions de la fenêtre */
int WINDOW_WIDTH = 400.0;
int WINDOW_HEIGHT = 400.0;

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
  /* Echange du front et du back buffer : mise à jour de la fenêtre */
  SDL_GL_SwapBuffers();
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
    SDL_WM_SetCaption("appli dessin", NULL);

    /* Boucle d'affichage */
    int loop = 1;
    while(loop) {

      /* Nettoyage de la fenêtre */
      glClear(GL_COLOR_BUFFER_BIT);

      /* Placer ici le code de dessin */
      SDL_Event e;
      while(SDL_PollEvent(&e)) {
          /* L'utilisateur ferme la fenêtre quand il appuie sur la touche q*/
          if(e.type == SDL_KEYDOWN && e.key.keysym.sym == 'q') {
              loop = 0;
              break;
          }

        switch(e.type) {
          case SDL_MOUSEBUTTONDOWN:
            glBegin(GL_POINTS);
              glColor3ub(255, 0, 0);
              glVertex2f(-1 + 2. * e.button.x / WINDOW_WIDTH, - (-1 + 2. * e.button.y / WINDOW_HEIGHT));
            glEnd();
            SDL_GL_SwapBuffers();
          break;

        }
      }
    }
  /* Liberation des ressources associées à la SDL */
    SDL_Quit();
    return EXIT_SUCCESS;
}
