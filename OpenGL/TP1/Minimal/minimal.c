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

void setVideoMode() {
  if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  tailleVirtuelle();

  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapBuffers();
}

void tailleVirtuelle() { 
  printf("New width: %d  New height: %d\n", WINDOW_WIDTH, WINDOW_HEIGHT);
  printf("Window resizing\n");
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1., 1., -1., 1.);
}


int main(int argc, char** argv) {

    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    /* Désactivation du double buffering. A faire avant ouverture de la fenetre ! */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

    setVideoMode();

    /* Titre de la fenêtre */
    SDL_WM_SetCaption("le swag de l'OpenGL :3", NULL);

    /* Boucle d'affichage */
    int loop = 1;
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();

        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Echange du front et du back buffer : mise à jour de la fenêtre */
        SDL_GL_SwapBuffers();

        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            /* L'utilisateur ferme la fenêtre quand il appuie sur la touche q*/
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == 'q') {
                loop = 0;
                break;
            }

            switch(e.type) {
            /*la fenetre prend une couleur correspondant aux coordonnées du clic*/
              case SDL_MOUSEBUTTONDOWN:
                glClearColor(e.button.x/(float)WINDOW_WIDTH,
                e.button.y/(float)WINDOW_HEIGHT, 0, 1);
                break;

              /* same mais quand le curseur se déplace dans la fenêtre*/
              case SDL_MOUSEMOTION:
                glClearColor(e.button.x/(float)WINDOW_WIDTH,
                e.button.y/(float)WINDOW_HEIGHT, 0, 1);
                break;

            /*si on redimentionne la fenêtre*/
            case SDL_VIDEORESIZE:
              WINDOW_WIDTH = e.resize.w;
              WINDOW_HEIGHT = e.resize.h;
              setVideoMode();
              break;
            }

        }

        /* Calcul du temps écoulé */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;

        /* Si trop peu de temps s'est écoulé, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* Liberation des ressources associées à la SDL */
    SDL_Quit();

    return EXIT_SUCCESS;
}
