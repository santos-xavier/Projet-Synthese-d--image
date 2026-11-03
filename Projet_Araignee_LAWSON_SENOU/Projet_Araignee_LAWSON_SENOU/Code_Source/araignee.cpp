#include "araignee.h"
#include <GL/glut.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void dessinerSphere(float rayon, int tranches, int anneaux) {
    glBegin(GL_QUADS);
    for (int i = 0; i < anneaux; ++i) {
        // Latitude
        float phi1 = M_PI * i / anneaux;
        float phi2 = M_PI * (i + 1) / anneaux;

        for (int j = 0; j < tranches; ++j) {
            // Longitude
            float theta1 = 2.0f * M_PI * j / tranches;
            float theta2 = 2.0f * M_PI * (j + 1) / tranches;

            // Calcul des 4 sommets de la facette
            // Sommet 1
            float x1 = rayon * sin(phi1) * cos(theta1);
            float y1 = rayon * cos(phi1);
            float z1 = rayon * sin(phi1) * sin(theta1);

            // Sommet 2
            float x2 = rayon * sin(phi2) * cos(theta1);
            float y2 = rayon * cos(phi2);
            float z2 = rayon * sin(phi2) * sin(theta1);

            // Sommet 3
            float x3 = rayon * sin(phi2) * cos(theta2);
            float y3 = rayon * cos(phi2);
            float z3 = rayon * sin(phi2) * sin(theta2);

            // Sommet 4
            float x4 = rayon * sin(phi1) * cos(theta2);
            float y4 = rayon * cos(phi1);
            float z4 = rayon * sin(phi1) * sin(theta2);

            // Normales 
            glNormal3f(x1, y1, z1); glVertex3f(x1, y1, z1);
            glNormal3f(x2, y2, z2); glVertex3f(x2, y2, z2);
            glNormal3f(x3, y3, z3); glVertex3f(x3, y3, z3);
            glNormal3f(x4, y4, z4); glVertex3f(x4, y4, z4);
        }
    }
    glEnd();
}

void dessinerAraignee() {
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        dessinerSphere(1.0, 20, 20); // 20x20 pour avoir une sphère un peu lisse
    glPopMatrix();
}
