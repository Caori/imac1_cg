#include <stdio.h>
#include <stdlib.h>

#include "colors.h"


Color3f addColors(Color3f c1, Color3f c2) {
  Color3f newColor;
  newColor.r = c1.r + c2.r;
  newColor.g = c1.g + c2.g;
  newColor.b = c1.b + c2.b;

  return newColor;
}

Color3f subColors(Color3f c1, Color3f c2) {
  Color3f newColor;
  newColor.r = c1.r - c2.r;
  newColor.g = c1.g - c2.g;
  newColor.b = c1.b - c2.b;

  return newColor;
}

Color3f multColors(Color3f c1, Color3f c2) {
  Color3f newColor;
  newColor.r = c1.r * c2.r;
  newColor.g = c1.g * c2.g;
  newColor.b = c1.b * c2.b;

  return newColor;
}

Color3f divColors(Color3f c1, Color3f c2) {
  Color3f newColor;
  if(c2.r == 0) {
    printf("Division par 0 du rouge \n");
    newColor.r = c1.r;
  }
  else newColor.r = c1.r / c2.r;
  if(c2.g == 0) {
    printf("Division par 0 du vert \n");
    newColor.g = c1.g;
  }
  else newColor.r = c1.g / c2.g;
  if(c2.b == 0) {
    printf("Division par 0 du bleu \n");
    newColor.b = c1.b;
  }
  else newColor.r = c1.b / c2.b;

  return newColor;
}

Color3f multColorScal(Color3f c, float a) {
  Color3f newColor;
  newColor.r = c.r * a;
  newColor.g = c.g * a;
  newColor.b = c.b * a;

  return newColor;
}

Color3f divColorScal(Color3f c, float a) {
  if(a == 0) {
    printf("Erreur : division par 0. \n");
    return c; //on retourne la couleur inchangée
  }
  Color3f newColor;
  newColor.r = c.r / a;
  newColor.g = c.g / a;
  newColor.b = c.b / a;

  return newColor;
}
