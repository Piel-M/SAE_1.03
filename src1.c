/* ----------------------------------
   Ce fichier contient des exemples
   de commentaires en langage C
   ---------------------------------- */

/* Commentaire d'en-tête du fichier */
/**
 * @file src1.c
 * @brief Ce fichier contient des exemples de commentaires en C.
 */

#include <stdio.h>

/* Définition d'une constante */
#define NB_ELEMENTS 10 /** Nombre d'éléments dans le tableau */

/* Structure pour représenter un point dans l'espace 2D */
typedef struct {
    int x; /** Coordonnée x */
    int y; /** Coordonnée y */
} Point;

/**
 * @brief Affiche un point dans l'espace 2D.
 * @param p Point à afficher.
 */
void afficher_point(Point p) {
    printf("Coordonnées : (%d, %d)\n", p.x, p.y);
}

/* -------------------------------------
   Fin du fichier src1.c
   ------------------------------------- */
