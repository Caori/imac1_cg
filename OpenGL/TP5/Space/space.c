#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
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

const char* stars_path = "Textures/stars.jpg";
const char* sun_path = "Textures/sun.jpg";
const char* mercury_path = "Textures/mercury.jpg";
const char* venus_path = "Textures/venus.jpg";
const char* earth_path = "Textures/earth.jpg";
const char* mars_path = "Textures/mars.jpg";
const char* jupiter_path = "Textures/jupiter.jpg";
const char* saturn_path = "Textures/saturn.jpg";
const char* uranus_path = "Textures/uranus.jpg";
const char* neptune_path = "Textures/neptune.jpg";
const char* moon_path = "Textures/moon.jpg";

static const unsigned char COLORS[] = {
    255, 255, 255, //0 =blanc
    0, 0, 0, //1=noir
    255, 0, 0, //2=rouge
    0, 255, 0, // 3 =vert
    0, 0, 255, //4= bleu
    255, 255, 0, //5=jaune
    0, 255, 255, // 6=cyan
    255, 0, 255, // 7=magenta
    237, 127,16, // 8=orange
    102, 0, 153, //9=violet
    150, 150, 150 //10=gris
};

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

void drawPlanet(float rayon, float distance, unsigned int couleur){
    glPushMatrix();
        glColor3ub(COLORS[couleur*3], COLORS[couleur*3+1], COLORS[couleur*3+2]);
        glTranslatef(distance, 0, 0);
        glScalef(rayon, rayon, 0);
        drawFilledCircle();
    glPopMatrix();
    glColor3ub(255, 255, 255);
}

GLuint loadTexture(const char* path) {
  // Chargement et traitement de la texture
   SDL_Surface* text_name = IMG_Load(path);
  if(text_name == NULL) {
    printf("Erreur lors du chargement de l'image.\n");
    exit(0);
  }

  GLuint textureID;
  glGenTextures(1, &textureID); //initie la texture
  glBindTexture(GL_TEXTURE_2D, textureID); //attache la texture à un point de bind

  //change la valeur du paramètre MIN_FILTER de la texure à GL_LINEAR
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  //envoie les données à la carte graphique w:width h:height
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, text_name->w, text_name->h,
  0, GL_RGB, GL_UNSIGNED_BYTE, text_name->pixels);

  // Libération des données CPU
  SDL_FreeSurface(text_name);

  glBindTexture(GL_TEXTURE_2D, 0); //bind la texture

  return textureID;
}

void drawTexturedPlanet(float rayon, float distance, GLuint texture) {
  glPushMatrix();
      glTranslatef(distance, 0, 0);
      glScalef(rayon, rayon, 0);

      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, texture);

      glBegin(GL_POLYGON);
        float pi = 3.14159;
        for(int i = 0; i < NB_COTES_CERCLE; i++) {
          glTexCoord2f((cos(2*pi*i/NB_COTES_CERCLE))/2, (sin(2*pi*i/NB_COTES_CERCLE))/2);
          glVertex2f((cos(2*pi*i/NB_COTES_CERCLE)), (sin(2*pi*i/NB_COTES_CERCLE)));
          glTexCoord2f((cos(2*pi*(i+1)/NB_COTES_CERCLE))/2, (sin(2*pi*(i+1)/NB_COTES_CERCLE))/2);
          glVertex2f((cos(2*pi*(i+1)/NB_COTES_CERCLE)), (sin(2*pi*(i+1)/NB_COTES_CERCLE)));
        }
      glEnd();

      glDisable(GL_TEXTURE_2D); //désactive le texturing
      glBindTexture(GL_TEXTURE_2D, 0); //debind la texture

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
  SDL_WM_SetCaption("Space", NULL);

  GLuint textures[11];
  textures[0] = loadTexture(stars_path);
  textures[1] = loadTexture(sun_path);
  textures[2] = loadTexture(mercury_path);
  textures[3] = loadTexture(venus_path);
  textures[4] = loadTexture(earth_path);
  textures[5] = loadTexture(mars_path);
  textures[6] = loadTexture(jupiter_path);
  textures[7] = loadTexture(saturn_path);
  textures[8] = loadTexture(uranus_path);
  textures[9] = loadTexture(neptune_path);
  textures[10] = loadTexture(moon_path);


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

glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, textures[0]);

glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex2f(-1, 1);
  glTexCoord2f(1, 0);
  glVertex2f(1, 1);
  glTexCoord2f(1, 1);
  glVertex2f(1, -1);
  glTexCoord2f(0, 1);
  glVertex2f(-1, -1);
glEnd();

glDisable(GL_TEXTURE_2D); //désactive le texturing
glBindTexture(GL_TEXTURE_2D, 0); //debind la texture

    //soleil
    drawTexturedPlanet(0.0696, 0, textures[1]);

    //mercure
    glPushMatrix();
      glRotatef(rotate1+=1.4, 0.0, 0.0, 1.0);
      drawTexturedPlanet(0.002439, 0.0696 + 0.0387, textures[2]);
    glPopMatrix();

    //venus
    glPushMatrix();
      glRotatef(rotate2+=1.2, 0.0, 0.0, 1.0);
      drawTexturedPlanet(0.006051, 0.0696 + 0.0723, textures[3]);
    glPopMatrix();

    //terre
    glPushMatrix();
      glRotatef(rotate3++, 0.0, 0.0, 1.0);
      drawTexturedPlanet(0.006378, 0.0696 + 0.1, textures[4]);
      glPushMatrix();
        glTranslatef(0.0696 + 0.1, 0, 0); //le repère est maintenant centré au milieu de la planète
          glRotatef(rotate1++, 0.0, 0.0, 1.0);
          drawTexturedPlanet(0.003, 0.02, textures[10]); //Lune
      glPopMatrix();
    glPopMatrix();

    //mars
    glPushMatrix();
      glRotatef(rotate4+=0.8, 0.0, 0.0, 1.0);
      drawTexturedPlanet(0.003393, 0.0696 + 0.1524, textures[5]);
    glPopMatrix();


    //jupiter
    glPushMatrix();
      glRotatef(rotate5+=0.6, 0.0, 0.0, 1.0);
      drawTexturedPlanet(0.071492, 0.0696 + 0.5203/2, textures[6]);
      glPushMatrix();
        glTranslatef(0.0696 + 0.5203/2, 0, 0); //le repère est maintenant centré au milieu de la planète
        glPushMatrix();
          glRotatef(rotate2+=0.16, 0.0, 0.0, 1.0);
          drawTexturedPlanet(0.005, 0.14, textures[10]); //Lune
        glPopMatrix();
        glPushMatrix();
          glRotatef(rotate3+=0.1, 0.0, 0.0, 1.0);
          drawTexturedPlanet(0.005, 0.15, textures[10]); //Lune
        glPushMatrix();
          glRotatef(rotate5+=0.1, 0.0, 0.0, 1.0);
        drawTexturedPlanet(0.005, 0.12, textures[10]); //Lune
        glPopMatrix();
          glRotatef(rotate4+=0.1, 0.0, 0.0, 1.0);
          drawTexturedPlanet(0.005, 0.11, textures[10]); //Lune
        glPopMatrix();
      glPopMatrix();
    glPopMatrix();

    //saturne
    glPushMatrix();
      glRotatef(rotate6+=0.4, 0.0, 0.0, 1.0);
      drawTexturedPlanet(0.060268, 0.0696 + 0.9516/2, textures[7]);
    glPopMatrix();

    //uranus
    glPushMatrix();
      glRotatef(rotate7+=0.2, 0.0, 0.0, 1.0);
      drawTexturedPlanet(0.025559, 0.0696 + 1.9165/3, textures[8]);
    glPopMatrix();

    //neptune
    glPushMatrix();
      glRotatef(rotate8+=0.1, 0.0, 0.0, 1.0);
      drawTexturedPlanet(0.024764, 0.0696 + 2.5/3, textures[9]);
    glPopMatrix();


    // Fin du code de dessin

    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }
    }
      SDL_GL_SwapBuffers();
  }

  // Libération des données GPU
  glDeleteTextures(11, &textures);

/* Liberation des ressources associées à la SDL */
  SDL_Quit();
  return EXIT_SUCCESS;
}
