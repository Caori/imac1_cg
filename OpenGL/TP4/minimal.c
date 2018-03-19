#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1., 1.);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}

const char* stars = "logo_imac_400x400.jpg";

int main(int argc, char** argv) {

    // Initialisation de la SDL
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    // Ouverture d'une fenêtre et création d'un contexte OpenGL
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    SDL_WM_SetCaption("td04", NULL);
    resizeViewport();

    // Chargement et traitement de la texture
    SDL_Surface* image = IMG_Load(filename);
    if(image == NULL) {
      printf("Erreur lors du chargement de l'image.\n");
      exit(0);
    }

    GLuint textureID;
    glGenTextures(1, &textureID); //initie la texture
    glBindTexture(GL_TEXTURE_2D, textureID); //attache la texture à un point de bind

    //change la valeur du paramètre MIN_FILTER de la texure à GL_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //envoie les données à la carte graphique w:width h:height
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h,
    0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    // Libération des données CPU
    SDL_FreeSurface(image);

    //debind la texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // Boucle de dessin
    int loop = 1;
    glClearColor(0.1, 0.1, 0.1 ,1.0);
    while(loop) {

        Uint32 startTime = SDL_GetTicks();

        glClear(GL_COLOR_BUFFER_BIT);

        // code de dessin
        glEnable(GL_TEXTURE_2D); //active le texturing
        glBindTexture(GL_TEXTURE_2D, textureID); //bind la texture

        glBegin(GL_QUADS);
          glTexCoord2f(0, 0);
          glVertex2f(-0.5, 0.5);
          glTexCoord2f(1, 0);
          glVertex2f(0.5, 0.5);
          glTexCoord2f(1, 1);
          glVertex2f(0.5, -0.5);
          glTexCoord2f(0, 1);
          glVertex2f(-0.5, -0.5);
        glEnd();

        glDisable(GL_TEXTURE_2D); //désactive le texturing
        glBindTexture(GL_TEXTURE_2D, 0); //debind la texture
        // Fin du code de dessin

        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            switch(e.type) {

                case SDL_QUIT:
                    loop = 0;
                    break;

                case SDL_VIDEORESIZE:
                    WINDOW_WIDTH = e.resize.w;
                    WINDOW_HEIGHT = e.resize.h;
                    resizeViewport();

                default:
                    break;
            }
        }

        SDL_GL_SwapBuffers();
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    // Libération des données GPU
    glDeleteTextures(1, &textureID);

    // Liberation des ressources associées à la SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}
