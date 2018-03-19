#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "geometry.h"

Point3D pointXYZ(float x, float y, float z) {
  Point3D point;
  point.x = x;
  point.y = y;
  point.z = z;

  return point;
}

Vector3D vectorXYZ(float x, float y, float z) {
  Vector3D vector;
  vector.x = x;
  vector.y = y;
  vector.z = z;

  return vector;
}

Vector3D vector(Point3D A, Point3D B) {
  Vector3D vectorAB;
  vectorAB.x = B.x - A.x;
  vectorAB.y = B.y - A.y;
  vectorAB.z = B.z - A.z;

  return vectorAB;
}

Point3D pointPlusVector(Point3D P, Vector3D V) {
  Point3D PtransV;
  PtransV.x = P.x + V.x;
  PtransV.y = P.y + V.y;
  PtransV.z = P.z + V.z;

  return PtransV;
}

Vector3D addVectors(Vector3D A, Vector3D B) {
  Vector3D AplusB;
  AplusB.x = A.x + B.x;
  AplusB.y = A.y + B.y;
  AplusB.z = A.z + B.z;

  return AplusB;
}

Vector3D subVectors(Vector3D A, Vector3D B) {
  Vector3D AmoinsB;
  AmoinsB.x = A.x - B.x;
  AmoinsB.y = A.y - B.y;
  AmoinsB.z = A.z - B.z;

  return AmoinsB;
}

Vector3D multVector(Vector3D V, float a) {
  Vector3D VfoisScal;
  VfoisScal.x = V.x * a;
  VfoisScal.y = V.y * a;
  VfoisScal.z = V.z * a;

  return VfoisScal;
}

Vector3D divVector(Vector3D V, float a) {
  if(a == 0) {
    printf("Erreur : division par 0.\n");
    return V;
  }
  Vector3D VdivScal;
  VdivScal.x = V.x / a;
  VdivScal.y = V.y / a;
  VdivScal.z = V.z / a;

  return VdivScal;
}

float dot(Vector3D A, Vector3D B) {
  float prodScal;
  prodScal = A.x*B.x + A.y*B.y + A.z*B.z;

  return prodScal;
}

float norm(Vector3D A) {
  float normA;
  normA = sqrt(A.x*A.x + A.y*A.y + A.z*A.z);

  return normA;
}

Vector3D normalize(Vector3D A) {
  Vector3D normVect; //vecteur normalisé de A
  float normA = norm(A); //calcule norme de A
  if(normA == 0) {
    printf("Attention : division par 0.\n");
    return A;
  }
  normVect.x = A.x / normA;
  normVect.y = A.y / normA;
  normVect.z = A.z / normA;

  return normVect;
}

void printPoint3D(Point3D p) {
  printf("Coordonnées du point : %f, %f, %f \n", p.x, p.y, p.z);
}

void printVector3D(Vector3D v) {
    printf("Coordonnées du vecteur : %f, %f, %f \n", v.x, v.y, v.z);
}
