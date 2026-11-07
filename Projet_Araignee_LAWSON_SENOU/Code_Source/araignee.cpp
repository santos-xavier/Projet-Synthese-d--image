#include "araignee.h"
#include <GL/glut.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//dessiner sol
GLuint texSol = 0;
void dessinerSol(float taille, int n)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            float x1 = -taille + 2.0f * taille * i / n;
            float x2 = -taille + 2.0f * taille * (i + 1) / n;

            float z1 = -taille + 2.0f * taille * j / n;
            float z2 = -taille + 2.0f * taille * (j + 1) / n;

            if ((i + j) % 2 == 0)
                glColor3f(1.0f, 1.0f, 1.0f);
            else
                glColor3f(0.0f, 0.0f, 0.0f);

            glVertex3f(x1, 0.0f, z1);
            glVertex3f(x1, 0.0f, z2);
            glVertex3f(x2, 0.0f, z2);
            glVertex3f(x2, 0.0f, z1);
        }
    }

    glEnd();

    glEnable(GL_LIGHTING);
}


// sphere
void dessinerSphere(float rayon, int tranches, int anneaux)
{
    glBegin(GL_QUADS);
    for (int i = 0; i < anneaux; ++i)
    {
        float phi1 = M_PI * i / anneaux;
        float phi2 = M_PI * (i + 1) / anneaux;

        for (int j = 0; j < tranches; ++j)
        {
            float theta1 = 2.0f * M_PI * j / tranches;
            float theta2 = 2.0f * M_PI * (j + 1) / tranches;

            float x1 = rayon * sin(phi1) * cos(theta1);
            float y1 = rayon * cos(phi1);
            float z1 = rayon * sin(phi1) * sin(theta1);

            float x2 = rayon * sin(phi2) * cos(theta1);
            float y2 = rayon * cos(phi2);
            float z2 = rayon * sin(phi2) * sin(theta1);

            float x3 = rayon * sin(phi2) * cos(theta2);
            float y3 = rayon * cos(phi2);
            float z3 = rayon * sin(phi2) * sin(theta2);

            float x4 = rayon * sin(phi1) * cos(theta2);
            float y4 = rayon * cos(phi1);
            float z4 = rayon * sin(phi1) * sin(theta2);

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


//dessiner ovale
void dessinerOvale(float rayon, int tranches, int anneaux)
{
    glBegin(GL_QUADS);
    for (int i = 0; i < anneaux; ++i)
    {
        float phi1 = M_PI * i / anneaux;
        float phi2 = M_PI * (i + 1) / anneaux;

        // Facteur de grosseur de chaque anneau : 0.6 côté tête -> 1.1 côté arrière
        float g1 = 0.6f + 1.0f * (1.0f - cos(phi1)) / 2.0f;
        float g2 = 0.6f + 1.0f * (1.0f - cos(phi2)) / 2.0f;

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

// cylindre
void dessinerCylindre(float rayon, float hauteur, int segments)
{
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; ++i)
    {
        float theta = 2.0f * M_PI * i / segments;
        float x = rayon * cos(theta);
        float z = rayon * sin(theta);
        glNormal3f(cos(theta), 0.0f, sin(theta));
        glVertex3f(x, 0.0f, z);
        glVertex3f(x, hauteur, z);
    }
    glEnd();
}

// pattes
void dessinerPatte(float angleEpaule, float angleGenou)
{
    glPushMatrix();
    glRotatef(angleEpaule, 0.0, 0.0, 1.0);
    dessinerCylindre(0.04, 0.5, 8);

    glTranslatef(0.0, 0.5, 0.0);
    glRotatef(angleGenou, 0.0, 0.0, 1.0);
    dessinerCylindre(0.03, 0.6, 8);

    glTranslatef(0.0, 0.6, 0.0);
    glRotatef(-angleGenou - 20.0, 0.0, 0.0, 1.0);
    dessinerCylindre(0.02, 0.3, 8);
    glPopMatrix();
}

// Araignee
void dessinerAraignee()
{
    /* Abdomen
    glPushMatrix();
        glTranslatef(0.0, 0.1, -0.9);
        glScalef(1.0, 1.0, 1.2);
        dessinerSphere(0.55, 16, 16);
    glPopMatrix();*/

    // abdomen
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.65f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.95f, 0.65f, 0.8f);
    glRotatef(15.0f, 0.0f, 0.0f, 1.0f); // pour incliner de 15° vers le haut l'abdomen
    dessinerOvale(0.7f, 15, 10);
    glPopMatrix();

    // Céphalothorax
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glScalef(1.0, 0.9, 1.2);
    dessinerSphere(0.35, 16, 16);
    glPopMatrix();

    // Tête
    glPushMatrix();
    glTranslatef(0.0, -0.05, 0.4);
    dessinerSphere(0.37, 16, 16);
    glPopMatrix();

    dessinerYeux();
    dessinerCheliceres();

    // Pattes de droite
    for (int i = 0; i < 4; ++i)
    {
        glPushMatrix();
        glTranslatef(0.25, 0.0, 0.25 - i * 0.2);
        glRotatef(45.0 - i * 30.0, 0.0, 1.0, 0.0);
        dessinerPatte(140.0, 70.0);
        glPopMatrix();
    }

    // Pattes de gauche
    for (int i = 0; i < 4; ++i)
    {
        glPushMatrix();
        glTranslatef(-0.25, 0.0, 0.25 - i * 0.2);
        glRotatef(-45.0 + i * 30.0, 0.0, 1.0, 0.0);
        dessinerPatte(-140.0, -70.0);
        glPopMatrix();
    }
}

// yeux
void dessinerYeux()
{
    glPushMatrix();
    // On se place sur la tête (même position que la sphère de tête)
    glTranslatef(0.0, -0.05, 0.4);

    // On avance un peu vers l'avant de la tête pour que les yeux soient visibles
    glTranslatef(0.0, 0.0, 0.35);

    // On désactive l'éclairage pour que les yeux soient bien noirs
    glDisable(GL_LIGHTING);
    glColor3f(0.0, 0.0, 0.0); // Yeux noirs

    // Rangée du haut (2 yeux de chaque côté)
    for (int i = 0; i < 2; ++i)
    {
        // Œil droit
        glPushMatrix();
        glTranslatef(0.06 + i * 0.05, 0.08, 0.0);
        dessinerSphere(0.025, 8, 8);
        glPopMatrix();

        // Œil gauche
        glPushMatrix();
        glTranslatef(-0.06 - i * 0.05, 0.08, 0.0);
        dessinerSphere(0.025, 8, 8);
        glPopMatrix();
    }

    // Rangée du bas (2 yeux de chaque côté)
    for (int i = 0; i < 2; ++i)
    {
        // Œil droit
        glPushMatrix();
        glTranslatef(0.04 + i * 0.05, 0.0, 0.02);
        dessinerSphere(0.02, 8, 8);
        glPopMatrix();

        // Œil gauche
        glPushMatrix();
        glTranslatef(-0.04 - i * 0.05, 0.0, 0.02);
        dessinerSphere(0.02, 8, 8);
        glPopMatrix();
    }

    // On réactive l'éclairage
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

//crochets

void dessinerCheliceres()
{
    glPushMatrix();
    // On se place DEVANT et SOUS la tête
    // z = 0.8 pour sortir de la sphère de tête (qui va jusqu'à z=0.77)
    // y = -0.25 pour être sous la tête
    glTranslatef(0.0, -0.25, 0.75);

    // Chélicère droit
    glPushMatrix();
    glTranslatef(0.07, 0.0, 0.0);
    glRotatef(-30.0, 1.0, 0.0, 0.0);  // Inclinaison vers le bas
    glRotatef(10.0, 0.0, 0.0, 1.0);   // Légère rotation sur le côté
    dessinerCylindre(0.025, 0.18, 8);
    glPopMatrix();

    // Chélicère gauche
    glPushMatrix();
    glTranslatef(-0.07, 0.0, 0.0);
    glRotatef(-30.0, 1.0, 0.0, 0.0);
    glRotatef(-10.0, 0.0, 0.0, 1.0);
    dessinerCylindre(0.025, 0.18, 8);
    glPopMatrix();
    glPopMatrix();
}
