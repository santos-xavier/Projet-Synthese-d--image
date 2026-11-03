#include <GL/glut.h>
#include <cstdlib>
#include "araignee.h"

// Variables globales pour la caméra
float angleX = 0.0f, angleY = 0.0f;
float zoom = 5.0f;

// Prototypes
void affichage();
void clavier(unsigned char touche, int x, int y);
void clavierSpecial(int touche, int x, int y);
void redimensionner(int largeur, int hauteur);
void initialiserLumieres();

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Projet Araignee - LAWSON SENOU");

    // Activation des tests de profondeur et de la lumière
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    initialiserLumieres();

    // Enregistrement des fonctions de rappel
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutSpecialFunc(clavierSpecial);
    glutReshapeFunc(redimensionner);

    glutMainLoop();
    return 0;
}

void initialiserLumieres() {
    // Lumière blanche venant du haut/avant droit
    GLfloat lumiereDiffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lumiereAmbiante[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat positionLumiere[] = {5.0, 5.0, 5.0, 1.0};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, lumiereDiffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lumiereAmbiante);
    glLightfv(GL_LIGHT0, GL_POSITION, positionLumiere);
}

void affichage() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Mise en place de la caméra
    glTranslatef(0.0, 0.0, -zoom);
    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleY, 0.0, 1.0, 0.0);

    // Dessin
    dessinerAraignee();

    glutSwapBuffers();
}

void clavier(unsigned char touche, int x, int y) {
    switch (touche) {
        case 'z': // Zoom avant
            zoom -= 0.5f;
            if (zoom < 1.0f) zoom = 1.0f; // Sécurité
            glutPostRedisplay();
            break;
        case 'Z': // Zoom arrière
            zoom += 0.5f;
            glutPostRedisplay();
            break;
        case 27: // Touche Echap
        case 'q':
            exit(0);
            break;
    }
}

void clavierSpecial(int touche, int x, int y) {
    switch (touche) {
        case GLUT_KEY_LEFT:
            angleY -= 5.0f;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            angleY += 5.0f;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            angleX -= 5.0f;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            angleX += 5.0f;
            glutPostRedisplay();
            break;
    }
}

void redimensionner(int largeur, int hauteur) {
    if (hauteur == 0) hauteur = 1;
    float ratio = (float)largeur / (float)hauteur;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Projection perspective (plus réaliste)
    gluPerspective(45.0, ratio, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, largeur, hauteur);
}
