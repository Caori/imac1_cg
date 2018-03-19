#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NB_COTES_CERCLE 100

//3. Il n'est pas intéressant ici de faire une liste d'affichage
//pour le bras en entier car cela rendrait la manipulation
//de ses différentent parties plus difficile.
//4. Les listes rendent l'affichage des dessins plus complexes
// (en 3D par exemple) plus rapides. Elles ne sont cependant
//pas très utiles dans des programmes simples comme celui-ci,
//elles ne font que rajouter quelques lignes de code.


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

GLuint createFirstArmIDList() {
  GLuint arm1 = glGenLists(1);
  glNewList(arm1, GL_COMPILE);
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
  glEndList();

  return arm1;
}

GLuint createSecondArmIDList() {
  GLuint arm2 = glGenLists(1);
  glNewList(arm2, GL_COMPILE);
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
  glEndList();

  return arm2;
}

GLuint createThirdArmIDList() {
  GLuint arm3 = glGenLists(1);
  glNewList(arm3, GL_COMPILE);
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
  glEndList();

  return arm3;
}

int main() {
  /* Initialisation de la SDL */
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
      fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
      return EXIT_FAILURE;
  }

  setVideoMode();

  /* Titre de la fenêtre */
  SDL_WM_SetCaption("Listes", NULL);

  //on crée les listes d'affichage des parties du bras
GLuint arm1 = createFirstArmIDList();
GLuint arm2 = createSecondArmIDList();
GLuint arm3 = createThirdArmIDList();

  /* Boucle d'affichage */
  int loop = 1;
  int rotate1 = 45;
  int rotate2 = -10;
  int rotate3 = 35;
  int rotate4 = -45;
  int rotate5 = 5;
  while(loop) {

    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
      glRotatef(rotate1++, 0.0, 0.0, 1.0);
      glCallList(arm1);
      glPushMatrix();
        glTranslatef(42.5, 42.5, 0);
        glRotatef(rotate2++, 0.0, 0, 1.0);
        glTranslatef(20, -3, 0);
        glCallList(arm2);
        glPushMatrix();
          glTranslatef(20, -4, 0);
          glRotatef(rotate3++, 0.0, 0.0, 1.0);
          glTranslatef(17, 12, 0);
          glCallList(arm3);
        glPopMatrix();
        glPushMatrix();
          glTranslatef(20, -4, 0);
          glRotatef(rotate4+2, 0.0, 0.0, 1.0);
          glTranslatef(17, 12, 0);
          glCallList(arm3);
        glPopMatrix();
        glPushMatrix();
          glTranslatef(20, -4, 0);
          glRotatef(rotate5+4, 0.0, 0.0, 1.0);
          glTranslatef(17, 12, 0);
          glCallList(arm3);
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
