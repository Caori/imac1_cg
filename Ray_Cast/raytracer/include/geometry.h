#ifndef GEOMETRY_H
#define GEOMETRY_H

typedef struct vec3 {
  float x;
  float y;
  float z;
} Point3D, Vector3D;

// Construit le point de coordonnées (x,y,z)
Point3D pointXYZ(float x, float y, float z);

// Construit le vecteur de coordonnées (x,y,z)
Vector3D vectorXYZ(float x, float y, float z);

// Construit le vecteur AB = B-A
Vector3D vector(Point3D A, Point3D B);

// Construit le point P+V (translation du point P par le vecteur V)
Point3D pointPlusVector(Point3D P, Vector3D V);

// Fonction d'addition de deux vecteurs
Vector3D addVectors(Vector3D A, Vector3D B);

// Fonction de soustraction de deux vecteurs
Vector3D subVectors(Vector3D A, Vector3D B);

// Fonction de multiplication d'un vecteur par un scalaire
Vector3D multVector(Vector3D V, float a);

// Fonction de division d'un vecteur par un scalaire
Vector3D divVector(Vector3D V, float a);

// Calcule le produit scalaire de deux vecteurs
float dot(Vector3D A, Vector3D B);

//Calcule la norme d'un vecteur
float norm(Vector3D A);

// Retourne le vecteur normalizé (divisé par sa norme) passé en paramètre
Vector3D normalize(Vector3D A);

// affiche le contenu du point passé en paramètre
void printPoint3D(Point3D p);

// affiche le contenu du vecteur passé en paramètre
void printVector3D(Vector3D v);

#endif
