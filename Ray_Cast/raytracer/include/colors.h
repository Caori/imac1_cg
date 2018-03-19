#ifndef COLORS_H
#define COLORS_H

typedef struct color3f {
  //valeurs comprises entre 0.0 et 1.0 !
  float r;
  float g;
  float b;
} Color3f;

// Calcule la somme de deux couleurs
Color3f addColors(Color3f c1, Color3f c2);

// Calcule la différence de deux couleurs
Color3f subColors(Color3f c1, Color3f c2);

// Calcule la multiplication de deux couleurs
Color3f multColors(Color3f c1, Color3f c2);

// Calcule la division de deux couleurs
Color3f divColors(Color3f c1, Color3f c2);

// Multiplie une couleur par un scalaire
Color3f multColorScal(Color3f c, float a);

// Divise une couleur par un scalaire
Color3f divColorScal(Color3f c, float a);

#endif
