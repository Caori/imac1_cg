#include <stdlib.h>
#include <stdio.h>

#include "geometry.h"
#include "colors.h"

int main(int argc, char** arvg) {
  Point3D point1 = pointXYZ(1, 2, 3);
  printPoint3D(point1);

  Point3D point2 = pointXYZ(6, 2, 8);
  printPoint3D(point2);

  Vector3D vecteur1 = vectorXYZ(2, 5, -4);
  printVector3D(vecteur1);

  Vector3D vecteur2 = vectorXYZ(4, -1, 4);
  printVector3D(vecteur2);

  Vector3D vectAB = vector(point1, point2);
  printVector3D(vectAB);

  return EXIT_SUCCESS;
}
