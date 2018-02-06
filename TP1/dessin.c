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

int main(int argc, char** argv) {

    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    /* Désactivation du double buffering */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

    /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL |
      SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    /* Titre de la fenêtre */
    SDL_WM_SetCaption("appli dessin", NULL);

    /* Boucle d'affichage */
    int loop = 1;
    while(loop) {
      /* Placer ici le code de dessin */
      glClear(GL_COLOR_BUFFER_BIT);

      /* Echange du front et du back buffer : mise à jour de la fenêtre */
      SDL_GL_SwapBuffers();

      /* Nettoyage de la fenêtre */
      glClear(GL_COLOR_BUFFER_BIT);

      /* Placer ici le code de dessin */
      SDL_Event ev;
      while(SDL_PollEvent(&ev)) {
        if(ev.type == SDL_MOUSEBUTTONDOWN) {
          glColor3ub(255, 255, 255);
          glBegin(GL_POINTS);
          glVertex2f(-1 + 2. * 200 /WINDOW_WIDTH, -(-1 + 2. * 100 /WINDOW_HEIGHT));
          glVertex2f(ev.button.x, ev.button.y);
          printf("Point dessiné\n");
          glEnd();
        }

        /* Echange du front et du back buffer : mise à jour de la fenêtre */
        SDL_GL_SwapBuffers();


      /* Pour quitter le programme */
      if(ev.type == SDL_KEYDOWN && ev.key.keysym.sym == 'q') {
        loop = 0;
        break;
      }
    }
  }
  /* Liberation des ressources associées à la SDL */
    SDL_Quit();
    return EXIT_SUCCESS;
}
