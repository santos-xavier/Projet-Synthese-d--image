#ifndef ARAIGNEE_H
#define ARAIGNEE_H
#include <GL/glut.h>

extern GLuint texSol;

void dessinerSol(float taille, int n);
void dessinerSphere(float rayon, int tranches, int anneaux);
void dessinerCylindre(float rayon, float hauteur, int segments);
void dessinerOvale(float rayon, int tranches, int anneaux);
void dessinerPatte(float angleEpaule, float angleGenou);
void dessinerAraignee();
void dessinerYeux();
void dessinerCheliceres();

#endif
