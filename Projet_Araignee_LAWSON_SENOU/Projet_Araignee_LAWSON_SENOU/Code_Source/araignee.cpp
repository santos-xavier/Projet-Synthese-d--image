//1ere version
#include "araignee.h"
#include <GL/glut.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


void dessinerSphere(float rayon, int tranches, int anneaux)
{
    glBegin(GL_QUADS);
    for (int i = 0; i < anneaux; ++i)
    {
        // Latitude
        float phi1 = M_PI * i / anneaux;
        float phi2 = M_PI * (i + 1) / anneaux;

        for (int j = 0; j < tranches; ++j)
        {
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
            glNormal3f(x1, y1, z1);
            glVertex3f(x1, y1, z1);
            glNormal3f(x2, y2, z2);
            glVertex3f(x2, y2, z2);
            glNormal3f(x3, y3, z3);
            glVertex3f(x3, y3, z3);
            glNormal3f(x4, y4, z4);
            glVertex3f(x4, y4, z4);
        }
    }
    glEnd();
}



// dessiner ovale : j'arrivais pas a transformer le sphère en ovale pour l'abdomène donc je l'ai créer et laisser sphère intact
void dessinerOvale(float rayon, int tranches, int anneaux)
{
    glBegin(GL_QUADS);
    for (int i = 0; i < anneaux; ++i)
    {
        float phi1 = M_PI * i / anneaux;
        float phi2 = M_PI * (i + 1) / anneaux;

        // Facteur de grosseur de chaque anneau : 0.6 côté tête -> 1.1 côté arrière
        float g1 = 0.6f + 0.5f * (1.0f - cos(phi1)) / 2.0f;
        float g2 = 0.6f + 0.5f * (1.0f - cos(phi2)) / 2.0f;

        for (int j = 0; j < tranches; ++j)
        {
            float theta1 = 2.0f * M_PI * j / tranches;
            float theta2 = 2.0f * M_PI * (j + 1) / tranches;

            // Sommet 1
            float x1 = -1.3f * rayon * cos(phi1);
            float y1 = rayon * g1 * sin(phi1) * cos(theta1);
            float z1 = rayon * g1 * sin(phi1) * sin(theta1);

            // Sommet 2
            float x2 = -1.3f * rayon * cos(phi2);
            float y2 = rayon * g2 * sin(phi2) * cos(theta1);
            float z2 = rayon * g2 * sin(phi2) * sin(theta1);

            // Sommet 3
            float x3 = -1.3f * rayon * cos(phi2);
            float y3 = rayon * g2 * sin(phi2) * cos(theta2);
            float z3 = rayon * g2 * sin(phi2) * sin(theta2);

            // Sommet 4
            float x4 = -1.3f * rayon * cos(phi1);
            float y4 = rayon * g1 * sin(phi1) * cos(theta2);
            float z4 = rayon * g1 * sin(phi1) * sin(theta2);

            // Normales (approximation : du centre vers le sommet)
            glNormal3f(x1, y1, z1);
            glVertex3f(x1, y1, z1);
            glNormal3f(x2, y2, z2);
            glVertex3f(x2, y2, z2);
            glNormal3f(x3, y3, z3);
            glVertex3f(x3, y3, z3);
            glNormal3f(x4, y4, z4);
            glVertex3f(x4, y4, z4);
        }
    }
    glEnd();
}


// Rayon d'un anneau : interpolé de r1 à r2, avec un "pli" (anneau plus gros) un sur deux
static float rayonAnneau(float r1, float r2, int k, int segments) {
    float r = r1 + (r2 - r1) * k / segments;
    if (k > 0 && k < segments && k % 2 == 1) r *= 1.2f;
    return r;
}

// Cylindre facetté le long de +Y, de y=0 à y=longueur
void dessinerCylindrePlis(float r1, float r2, float longueur, int tranches, int segments) {
    for (int k = 0; k < segments; ++k) {
        float ra = rayonAnneau(r1, r2, k, segments);
        float rb = rayonAnneau(r1, r2, k + 1, segments);
        float ya = longueur * k / segments;
        float yb = longueur * (k + 1) / segments;

        glBegin(GL_QUADS);
        for (int j = 0; j < tranches; ++j) {
            float th1 = 2.0f * M_PI * j / tranches;
            float th2 = 2.0f * M_PI * (j + 1) / tranches;

            float p1[3] = {ra * cosf(th1), ya, ra * sinf(th1)};
            float p2[3] = {rb * cosf(th1), yb, rb * sinf(th1)};
            float p3[3] = {rb * cosf(th2), yb, rb * sinf(th2)};
            float p4[3] = {ra * cosf(th2), ya, ra * sinf(th2)};

            // Normale PAR FACE (produit vectoriel) -> aspect facetté
            float u[3] = {p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2]};
            float v[3] = {p4[0] - p1[0], p4[1] - p1[1], p4[2] - p1[2]};
            glNormal3f(u[1] * v[2] - u[2] * v[1],
                       u[2] * v[0] - u[0] * v[2],
                       u[0] * v[1] - u[1] * v[0]);

            glVertex3fv(p1); glVertex3fv(p2); glVertex3fv(p3); glVertex3fv(p4);
        }
        glEnd();
    }

    // Bouchon au bout
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    for (int j = 0; j < tranches; ++j) {
        float th = 2.0f * M_PI * j / tranches;
        glVertex3f(r2 * cosf(th), longueur, r2 * sinf(th));
    }
    glEnd();
}



void dessinerAraignee()
{
    // Abdomen
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    dessinerOvale(1.0f, 20, 20);
    glRotatef(15.0f, 0.0f, 0.0f, 1.0f);   // relève l'arrière de 15°
    dessinerOvale(1.0f, 20, 20);
    glPopMatrix();

   // Céphalothorax
glPushMatrix();
    glTranslatef(-1.9f, 0.0f, 0.0f);

    // Corps : sphère aplatie
    glPushMatrix();
        glScalef(0.9f, 0.55f, 0.7f);
        dessinerSphere(1.0f, 24, 24);
    glPopMatrix();

    // Yeux : amas de bosses sur le dessus du museau
    // {élévation (°), azimut (°), rayon}
    const float yeux[4][3] = {
        {38.0f, 10.0f, 0.09f},
        {25.0f, 32.0f, 0.08f},
        {50.0f, 30.0f, 0.07f},
        {62.0f, 10.0f, 0.06f}
    };
    for (int e = 0; e < 4; e++) {
        float a = yeux[e][0] * M_PI / 180.0f;
        float b = yeux[e][1] * M_PI / 180.0f;
        // point sur la surface de l'ellipsoïde (0.9, 0.55, 0.7)
        float x = -0.9f * cosf(a) * cosf(b);
        float y =  0.55f * sinf(a);
        float z =  0.7f * cosf(a) * sinf(b);
        for (int c = -1; c <= 1; c += 2) {
            glPushMatrix();
                glTranslatef(x, y, z * c);
                dessinerSphere(yeux[e][2], 10, 10);
            glPopMatrix();
        }
    }

    // Crochets (chélicères) : 2 cylindres à plis qui pendent sous le museau
    for (int c = -1; c <= 1; c += 2) {
        glPushMatrix();
            glTranslatef(-0.78f, -0.15f, 0.14f * c);
            glRotatef(165.0f, 0.0f, 0.0f, 1.0f);   // vers le bas, légèrement vers l'avant
            dessinerCylindrePlis(0.13f, 0.07f, 0.5f, 6, 3);
        glPopMatrix();
    }

    // Pédipalpes : 2 segments pliés sur les côtés du museau
    for (int c = -1; c <= 1; c += 2) {
        glPushMatrix();
            glTranslatef(-0.7f, -0.2f, 0.4f * c);
            glRotatef(c * 110.0f, 1.0f, 0.0f, 0.0f);   // part sur le côté
            dessinerCylindrePlis(0.07f, 0.06f, 0.35f, 6, 2);
            glTranslatef(0.0f, 0.35f, 0.0f);
            glRotatef(c * 50.0f, 1.0f, 0.0f, 0.0f);    // se plie vers le bas
            dessinerCylindrePlis(0.06f, 0.04f, 0.3f, 6, 2);
        glPopMatrix();
    }
glPopMatrix();


    }








