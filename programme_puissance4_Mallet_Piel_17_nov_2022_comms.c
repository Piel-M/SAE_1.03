/**
*
* \brief Programme puissance 4 permettant à deux joueurs de jouer l'un contre l'autre.
* \author Mallet Piel
* \version 8.4
* \date 17 novembre 2022
*
* Ce programme permet d'afficher un puissance 4 dans le terminal
* et de permettre à deux joueurs de jouer l'un après l'autre.
* Chacun peut choisir sa colonne en se déplaçant avec les touches "q" et "d" et de valider avec la touche "s".
* Le programme annonce le joueur ayant gagner en fin de partie et affiche les pions l'ayant fait gagner en surligné.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*définitions des couleurs ANSI.*/
/**
*
* \def WHTB
* \brief Define à mettre avant du texte pour afficher tout le texte qui suit en blanc surligné.
*
*/
#define WHTB "\e[47m"
/**
*
* \def reset
* \brief Define à mettre avant/après du texte pour remettre l'affichage par défaut (après avoir affiché ce que l'on voulait avec le define "WHTB" par exemple).
*
*/
#define reset "\e[0m"

/*définition des constantes.*/
/**
*
* \def NBLIG
* \brief Define servant de constante pour le nombre de lignes.
*
*/
#define NBLIG 6

/**
*
* \def NBCOL
* \brief Define servant de constante pour le nombre de colonnes.
*
*/
#define NBCOL 7

/**
*
* \def PION_A
* \brief Constante du caractère du pion A.
*
*/
const char PION_A = 'X';

/**
*
* \def PION_B
* \brief Constante du caractère du pion B.
*
*/
const char PION_B = 'O';

/**
*
* \def VIDE
* \brief Constante du caractère d'une case vide " ".
*
*/
const char VIDE = ' ';

/**
*
* \def INCONNU
* \brief Constante du caractère d'une case inconnue " ".
*
*/
const char INCONNU = ' ';

/**
*
* \def COLONNE_DEBUT
* \brief Constante permettant de placer le pion au dessus de la colonne centrale au début d'un tour.
*
*/
const int COLONNE_DEBUT = 3;

/**
*
* \typedef grille
* \brief typedef permettant de créer des tableaux a double dimensions de taille NBLIG et NBCOL.
*
* Permet de créer la grille du puissance 4.
*
*/
typedef char grille[NBLIG][NBCOL];

/*initialisation des fonctions/procédures*/
void initGrille (grille);
void afficher(grille, char, int, int);
bool grillePleine (grille);
void jouer(grille, char, int*, int*);
int choisirColonne (grille, char, int);
int trouverLigne (grille, int);
bool estVainqueur (grille, int, int, int*);
void finDePartie (char);
void couleurChangeFin(grille, char, int, int, int);

//programme principal
int main(){
    printf("\e[1;1H\e[2J"); //on clear l'écran au cas ou il y avait déjà du texte dans le terminal
    //initialisation des variable
    char vainqueur;
    int ligne, colonne;
    int mode;
    ligne=0;
    grille g;
    initGrille(g); //on appel la procédure qui initialise la grille
    vainqueur = INCONNU; //on ne connait pas le vainqueur au début de la partied
    printf("\nTour du joueur A : \n\n");
    afficher(g, PION_A, ligne, COLONNE_DEBUT); //on affiche la grille pour le premier tour
    while (vainqueur==INCONNU && grillePleine(g)!=true){ //tant que la grille n'est pas pleine et qu'il n'y a pas de vainqueur on reste dans la boucle de jeu
        jouer(g, PION_A, &ligne, &colonne);
        printf("\e[1;1H\e[2J"); //on clear l'écran pour un affichage plus propre
        printf("\nTour du joueur B : \n\n");
        afficher(g, PION_B, ligne, COLONNE_DEBUT);
        if (estVainqueur(g, ligne, colonne, &mode)){
            vainqueur = PION_A;
        } else if (grillePleine(g)!=true){
            jouer(g, PION_B, &ligne, &colonne);
            printf("\e[1;1H\e[2J"); //on clear l'écran pour un affichage plus propre
            printf("\nTour du joueur A : \n\n");
            afficher(g, PION_A, ligne, COLONNE_DEBUT);
            if (estVainqueur(g, ligne, colonne, &mode)){
                vainqueur = PION_B;
            }
        }
    }
    printf("\e[1;1H\e[2J"); //on clear l'écran pour un affichage plus propre
    finDePartie(vainqueur);
    couleurChangeFin(g, vainqueur, ligne, colonne, mode);
    afficher(g, vainqueur, ligne, colonne);
    printf("%s", reset);
    return EXIT_SUCCESS;
}

//initialisation de la grille
/**
*
* \fn void initGrille (grille g)
*
* \brief Procédure qui initialise la grille.
*
* \param g : La grille à remplir de caractères vides.
*
* Consiste à remplir la grille du puissance 4 de caractères vides pour l'initialiser totalement vide au début du programme.
*
*/
void initGrille (grille g){
    int i, j;
    for (i=0; i<NBLIG; i++){
        for (j=0; j<NBCOL; j++){
            g[i][j] = VIDE;
        }
    }
}

//affichage de la grille 
/**
*
* \fn void afficher (grille g, char pion, int ligne, int colonne)
*
* \brief Procédure qui affiche la grille.
*
* \param g : La grille à afficher.
* \param pion : Le caractère du joueur qui joue à afficher au dessus de la grille, ou pour modifier le caractère R (caractère ayant permis de gagner), par celui du joueur ayant gagner (seulement à la fin du jeu). 
* \param ligne : 
* \param colonne : permet de savoir ou le pion est, et d'afficher le caractère du joueur au dessus de la bonne colonne.
*
* Consiste à afficher la grille avant chaque tour, et à la toute fin avec les caractères gagnants surlignés.
*
*/
void afficher (grille g, char pion, int ligne, int colonne){
    int i, j, k;
    printf("   "); //on initialise deux case au début pour prévoir l'espace avant de calculer ou placer le pion avec le "colonne".
    for (k=0; k<colonne; k++){ //selon le nombre de colonne, on affiche un certain nombre d'espace afin de placer le pion au dessus de la bonne colonne.
        printf("    ");
    }
    printf("%c\n", pion); //on affiche le pion au dessus de la bonne colonne et on passe une ligne pour afficher la flèche.
    printf("   "); //on initialise trois case au début pour prévoir l'espace avant de calculer ou placer le symbole de fléche avec le "colonne".
    for (k=0; k<colonne; k++){ //selon le nombre de colonne, on affiche un certain nombre d'espace afin de placer la flèche au dessus de la bonne colonne.
        printf("    ");
    }
    printf("ᐁ\n"); //on affiche la flèche au dessus de la bonne colonne et on passe une ligne pour afficher le tableau.
    printf(" ┌───┬───┬───┬───┬───┬───┬───┐\n");
    for (i=0; i<NBLIG; i++){
        printf("%d", 6-i); //affichage des chiffres des lignes pour la fidélité à la maquette.
        for (j=0; j<NBCOL; j++){
            if (g[i][j] == 'R'){ //si les caractères sont des caractères affichant la réussite, 
                g[i][j] = pion; //on change le caractère pour celui du gagnant.
                printf("| %s%C%s ", WHTB, g[i][j], reset); //affichage spécial pour les pions ayant donnés la victoire au gagnant.
            } else {
                printf("| %c ", g[i][j]); //affichage normal des pions.
            }
    }
        printf("|\n");
        if (i<NBLIG-1){
            printf(" ├───┼───┼───┼───┼───┼───┼───┤\n"); //affichage ligne horizontale + bout des ligne verticales.
        }

    }
    printf(" └───┴───┴───┴───┴───┴───┴───┘\n"); //affichage du bas de la grille.
    printf("   1   2   3   4   5   6   7\n"); //affichage des chiffres des colonnes pour la fidélité à la maquette.
}

//on vérifie si la grille est pleine
/**
*
* \fn bool grillePleine (grille g)
*
* \brief Fonction qui vérifie si un tableau à deux dimensions est plein.
*
* \param g : La grille à vérifier.
*
* \return true si la grille est pleine, et false si elle ne l'est pas.
*
* Consiste à vérifier si la grille du jeu est pleine afin de renvoyer true si elle l'est et false si elle ne l'est pas.
*
*/
bool grillePleine (grille g){ //bool = on renvoie true si elle l'est et false si elle ne l'est pas.
    int i, j;
    for (i=0; i<NBLIG; i++){ //on parcourt la grille
        for (j=0; j<NBCOL; j++){
            if (g[i][j] == VIDE){ //si on trouve une case vide, la grille n'est pas pleine.
                return false;
            }
        }
    }
    return true; //si on ne trouve pas de cases vides c'est que le tableau est plein
}

//procédure pour jouer un tour du jeu
/**
*
* \fn void jouer(grille g, char pion, int *ligne, int *colonne)
*
* \brief Procédure qui permet de jouer un tour de jeu.
*
* \param g : La grille dans laquelle on joue.
* \param pion : Le pion du joueur qui joue ce tour.
* \param ligne : La ligne ou va être placé le pion du joueur (paramètre de sortie)
* \param colonne : La colonne ou va être placé le pion du joueur (paramètre de sortie)
*
* \return true si la grille est pleine, et false si elle ne l'est pas.
*
* Consiste à jouer un tour du jeu de puissance 4.
*
*/
void jouer(grille g, char pion, int *ligne, int *colonne){
    *colonne = choisirColonne(g, pion, COLONNE_DEBUT);    //le joueur choisit une colonne
    while (g[0][*colonne] != VIDE){ //condition pour vérifier que la colonne ne soit pas pleine 
        printf("La colonne est pleine, veuillez choisir une autre colonne"); //si elle l'est, on demande au joueur de choisir une autre colonne
        *colonne = choisirColonne(g, pion, COLONNE_DEBUT);
    }
    *ligne = trouverLigne(g, *colonne); //on trouve la ligne où le pion doit être placé
    g[*ligne][*colonne] = pion; //on place le pion dans la grille
}

//fonction pour choisir la colonne où l'on veut jouer
/**
*
* \fn int choisirColonne (grille g, char pion, int colonne)
*
* \brief Fonction qui permet au joueur qui joue de choisir la colonne ou il veut jouer.
*
* \param g : La grille dans laquelle on joue.
* \param pion : Le pion du joueur qui joue ce tour.
* \param ligne : La ligne ou va être placé le pion du joueur (paramètre de sortie)
* \param colonne : La colonne ou va être placé le pion du joueur (paramètre de sortie)
*
* \return true si la grille est pleine, et false si elle ne l'est pas.
*
* Consiste à jouer un tour du jeu de puissance 4.
*
*/
int choisirColonne (grille g, char pion, int colonne){
    char input_user='r'; //caractère saisi
    if (pion == 'X'){   //on regarde quel joueur joue pour afficher le bon joueur au dessus de la grille
        while (input_user != 's'){ //tant que le joueur ne confirme pas on lui demande ou il veut se déplacer
            printf("\nJoueur A, entrez \"q\" pour vous déplacer vers la gauche, et \"d\" pour vous déplacer vers la droite.\nPuis, confirmer avec la touche \"s\" la colonne ou vous souhaitez placer votre pion : "); //on demande au joueur A de choisir une colonne dans la grille
            scanf("%c", &input_user); 
            while (getchar () != '\n'); //on "avale" tout les caractères si l'utilisateur à taper trop de caractères.
            while (input_user != 'q' && input_user!= 'd' && input_user!= 's'){ //si l'utilisateur se trompe de caractères, on lui redemande.
                printf("\nJoueur A, veuillez entrer un des 3 caractères proposés, \"q\", \"d\" ou \"s\" pour confirmer.");
                scanf("%c", &input_user);
                while (getchar () != '\n'); //on "avale" tout les caractères si l'utilisateur à taper trop de caractères.
            }
            if (input_user=='q'){
                colonne--; //déplacement vers la gauche.
                if (colonne<0){ //si on sors de la grille, on annule le déplacement.
                    colonne++;
                }
                printf("\e[1;1H\e[2J"); //on supprime tout ce qu'il y avait à l'écran pour afficher uniquement la nouvelle grille
                afficher(g, pion, 0, colonne);
            } else if (input_user=='d'){
                colonne++; //déplacement vers la droite.
                if (colonne>6){ //si on sors de la grille, on annule le déplacement.
                    colonne--;
                }
                printf("\e[1;1H\e[2J"); //on supprime tout ce qu'il y avait à l'écran pour afficher uniquement la nouvelle grille
                afficher(g, pion, 0, colonne);
            }
        }
    } else if (pion == 'O'){
        while (input_user != 's'){ //tant que le joueur ne confirme pas on lui demande ou il veut se déplacer
            printf("\nJoueur B, entrez \"q\" pour vous déplacer vers la gauche, et \"d\" pour vous déplacer vers la droite.\nPuis, confirmer avec la touche \"s\" la colonne ou vous souhaitez placer votre pion : "); //on demande au joueur A de choisir une colonne dans la grille
            scanf("%c", &input_user);
            while (getchar () != '\n'); //on "avale" tout les caractères si l'utilisateur à taper trop de caractères.
            while (input_user != 'q' && input_user!= 'd' && input_user!= 's'){ //si l'utilisateur se trompe de caractères, on lui redemande.
                printf("\nJoueur B, veuillez entrer un des 3 caractères proposés, \"q\", \"d\" ou \"s\" pour confirmer.");
                scanf("%c", &input_user);
                while (getchar () != '\n'); //on "avale" tout les caractères si l'utilisateur à taper trop de caractères.
            }
            if (input_user=='q'){
                colonne--; //déplacement vers la gauche.
                if (colonne<0){ //si on sors de la grille, on annule le déplacement.
                    colonne++;
                }
                printf("\e[1;1H\e[2J"); //on supprime tout ce qu'il y avait à l'écran pour afficher uniquement la nouvelle grille
                afficher(g, pion, 0, colonne);
            } else if (input_user=='d'){
                colonne++; //déplacement vers la droite.
                if (colonne>6){ //si on sors de la grille, on annule le déplacement.
                    colonne--;
                }
                printf("\e[1;1H\e[2J"); //on supprime tout ce qu'il y avait à l'écran pour afficher uniquement la nouvelle grille
                afficher(g, pion, 0, colonne);
            }
        }
    }
    return colonne; //on renvoie la colonne choisie
}

//cherche la ligne à laquelle je pion va s'arreter 
int trouverLigne (grille g, int colonne){
    int i;
    for (i=NBLIG-1; i>=0; i--){ //on parcourt la grille de bas en haut
        if (g[i][colonne] == VIDE){
            return i; //on renvoie la ligne où le pion doit s'arreter
        }
    }
    return -1; //si la colonne est pleine, on renvoie -1
}

//vérifie si le joueur a gagné après ce tour
bool estVainqueur (grille g, int ligne, int colonne, int *mode){
    int i;
    int compteur;
//vérifie si le joueur a gagné en ligne (vertical)
    compteur = 0;
    for (i=0; i<NBLIG; i++){
        if (g[i][colonne] == g[ligne][colonne]){ //on incrémente le compteur si le pion est le même que celui du joueur
            compteur++;
        } else {
            compteur = 0;   //sinon on le remet à 0
        }
        if (compteur == 4){ //si le compteur est à 4, le joueur a gagné
            *mode=1;
            return true;
        }
    }
//vérifie si le joueur a gagné en colonne (horizontal)
    compteur = 0;
    for (i=0; i<NBCOL; i++){ //on pars de la colonne la plus à gauche et on va vers la droite
        if (g[ligne][i] == g[ligne][colonne]){ //on incrémente le compteur si le pion est le même que celui du joueur
            compteur++;
        } else {
            compteur = 0;   //sinon on le remet à 0
        }
        if (compteur == 4){ //si le compteur est à 4, le joueur a gagné
            *mode=2;
            return true;
        }
    }
//vérifie si le joueur a gagné en diagonale haut gauche vers bas droite
    compteur = 0;
    for(i=0; i<NBLIG && i<NBCOL; i++){ //check diagonale milieu gauche
        if (g[i][i] == g[ligne][colonne]){ //on incrémente le compteur si le pion est le même que celui du joueur
            compteur++;
        } else {
            compteur = 0;   //sinon on le remet à 0
        }
        if (compteur == 4){ //si le compteur est à 4, le joueur a gagné
            *mode=3;
            return true;
        }
    }
    compteur = 0;
    for (i=1; i<NBLIG && i<NBCOL; i++){ //check diagonale milieu-1 gauche
        if (g[i][i-1] == g[ligne][colonne]){ //on incrémente le compteur si le pion est le même que celui du joueur
            compteur++;
        } else {
            compteur = 0;   //sinon on le remet à 0
        }
        if (compteur == 4){ //si le compteur est à 4, le joueur a gagné
            *mode=4;
            return true;
        }
    }
    compteur = 0;
    for (i=2; i<NBLIG && i<NBCOL; i++){ //check diagonale milieu-2 gauche
        if (g[i][i-2] == g[ligne][colonne]){ //on incrémente le compteur si le pion est le même que celui du joueur
            compteur++;
        } else {
            compteur = 0;   //sinon on le remet à 0
        }
        if (compteur == 4){ //si le compteur est à 4, le joueur a gagné
            *mode=5;
            return true;
        }
    }
    compteur = 0;
    for (i=0; i<NBLIG && i<NBCOL; i++){ //check diagonale milieu+1 droite
        if (g[i][i+1] == g[ligne][colonne]){ //on incrémente le compteur si le pion est le même que celui du joueur
            compteur++;
        } else {
            compteur = 0;   //sinon on le remet à 0
        }
        if (compteur == 4){ //si le compteur est à 4, le joueur a gagné
            *mode=6;
            return true;
        }
    }
    compteur = 0;
    for (i=0; i<NBLIG && i<NBCOL; i++){ //check diagonale milieu+2 droite
        if (g[i][i+2] == g[ligne][colonne]){ //on incrémente le compteur si le pion est le même que celui du joueur
            compteur++;
        } else {
            compteur = 0;   //sinon on le remet à 0
        }
        if (compteur == 4){ //si le compteur est à 4, le joueur a gagné
            *mode=7;
            return true;
        }
    }
    compteur = 0;
    for (i=0; i<NBLIG && i<NBCOL; i++){ //check diagonale milieu+3 droite
        if (g[i][i+3] == g[ligne][colonne]){ //on incrémente le compteur si le pion est le même que celui du joueur
            compteur++;
        } else {
            compteur = 0;   //sinon on le remet à 0
        }
        if (compteur == 4){ //si le compteur est à 4, le joueur a gagné
            *mode=8;
            return true;
        }
    }
//vérifie si le joueur a gagné en diagonale haut droite vers bas gauche
    compteur = 0;
    for (i=0; i<NBLIG && i<NBCOL; i++){ //check diagonale milieu droite
        if (g[i][NBCOL-1-i] == g[ligne][colonne]){ //on incrémente le compteur si le pion est le même que celui du joueur
            compteur++;
        } else {
            compteur = 0;   //sinon on le remet à 0
        }
        if (compteur == 4){ //si le compteur est à 4, le joueur a gagné
            *mode=9;
            return true;
        }
    }
    compteur = 0;
    for (i=1; i<NBLIG && i<NBCOL; i++){ //check diagonale milieu-1 droite
        if (g[i][NBCOL-1-i+1] == g[ligne][colonne]){ //on incrémente le compteur si le pion est le même que celui du joueur
            compteur++;
        } else {
            compteur = 0;   //sinon on le remet à 0
        }
        if (compteur == 4){ //si le compteur est à 4, le joueur a gagné
            *mode=10;
            return true;
        }
    }
    compteur = 0;
    for (i=2; i<NBLIG && i<NBCOL; i++){ //check diagonale milieu-2 droite
        if (g[i][NBCOL-1-i+2] == g[ligne][colonne]){ //on incrémente le compteur si le pion est le même que celui du joueur
            compteur++;
        } else {
            compteur = 0;   //sinon on le remet à 0
        }
        if (compteur == 4){ //si le compteur est à 4, le joueur a gagné
            *mode=11;
            return true;
        }
    }
    compteur = 0;
    for (i=0; i<NBLIG && i<NBCOL; i++){ //check diagonale milieu+1 gauche
        if (g[i][NBCOL-1-i-1] == g[ligne][colonne]){ //on incrémente le compteur si le pion est le même que celui du joueur
            compteur++;
        } else {
            compteur = 0;   //sinon on le remet à 0
        }
        if (compteur == 4){ //si le compteur est à 4, le joueur a gagné
            *mode=12;
            return true;
        }
    }
    compteur = 0;
    for (i=0; i<NBLIG && i<NBCOL; i++){ //check diagonale milieu+2 gauche
        if (g[i][NBCOL-1-i-2] == g[ligne][colonne]){ //on incrémente le compteur si le pion est le même que celui du joueur
            compteur++;
        } else {
            compteur = 0;   //sinon on le remet à 0
        }
        if (compteur == 4){ //si le compteur est à 4, le joueur a gagné
            *mode=13;
            return true;
        }
    }
    compteur = 0;
    for (i=0; i<NBLIG && i<NBCOL; i++){ //check diagonale milieu+3 gauche
        if (g[i][NBCOL-1-i-3] == g[ligne][colonne]){ //on incrémente le compteur si le pion est le même que celui du joueur
            compteur++;
        } else {
            compteur = 0;   //sinon on le remet à 0
        }
        if (compteur == 4){ //si le compteur est à 4, le joueur a gagné
            *mode=14;
            return true;
        }
    }
    return false;  //si le joueur n'a pas gagné, on renvoie false
}

void couleurChangeFin(grille g, char vainqueur, int ligne, int colonne, int mode){
    //affiches les pions du vainqueur en rouge si les pions sont alignés
    int i;
    if (mode == 1){ //vertical
        for (i=6; i>0; i--){
            if (g[i][colonne] == vainqueur && g[i-1][colonne] == vainqueur && g[i-2][colonne] == vainqueur && g[i-3][colonne] == vainqueur){
                g[i][colonne] = 'R';
                g[i-1][colonne] = 'R';
                g[i-2][colonne] = 'R';
                g[i-3][colonne] = 'R';
            }
        }
    } else if (mode == 2){ //horizontal
        for (i=0; i<NBCOL; i++){
            if (g[ligne][i] == vainqueur && g[ligne][i+1] == vainqueur && g[ligne][i+2] == vainqueur && g[ligne][i+3] == vainqueur){
                g[ligne][i] = 'R';
                g[ligne][i+1] = 'R';
                g[ligne][i+2] = 'R';
                g[ligne][i+3] = 'R';
            }
        }
    } else if (mode == 3){ //diagonale milieu gauche
        for(i=0; i<NBLIG && i<NBCOL; i++){ 
            if (g[i][i] == vainqueur && g[i+1][i+1] == vainqueur && g[i+2][i+2] == vainqueur && g[i+3][i+3] == vainqueur){
                g[i][i] = 'R';
                g[i+1][i+1] = 'R';
                g[i+2][i+2] = 'R';
                g[i+3][i+3] = 'R';
            }
        }
    } else if (mode == 4){ //diagonale milieu-1 gauche
        for(i=1; i<NBLIG && i<NBCOL; i++){ 
            if (g[i][i-1] == vainqueur && g[i+1][i] == vainqueur && g[i+2][i+1] == vainqueur && g[i+3][i+2] == vainqueur){
                g[i][i-1] = 'R';
                g[i+1][i] = 'R';
                g[i+2][i+1] = 'R';
                g[i+3][i+2] = 'R';
            }
        }
    } else if (mode == 5){ //diagonale milieu-2 gauche
        for(i=2; i<NBLIG && i<NBCOL; i++){ 
            if (g[i][i-2] == vainqueur && g[i+1][i-1] == vainqueur && g[i+2][i] == vainqueur && g[i+3][i+1] == vainqueur){
                g[i][i-2] = 'R';
                g[i+1][i-1] = 'R';
                g[i+2][i] = 'R';
                g[i+3][i+1] = 'R';
            }
        }
    } else if (mode == 6){ //diagonale milieu+1 droite
        for(i=0; i<NBLIG && i<NBCOL; i++){
            if (g[i][i+1] == vainqueur && g[i+1][i+2] == vainqueur && g[i+2][i+3] == vainqueur && g[i+3][i+4] == vainqueur){
                g[i][i+1] = 'R';
                g[i+1][i+2] = 'R';
                g[i+2][i+3] = 'R';
                g[i+3][i+4] = 'R';
            }
        }
    } else if (mode == 7){ //diagonale milieu+2 droite
        for(i=0; i<NBLIG && i<NBCOL; i++){
            if (g[i][i+2] == vainqueur && g[i+1][i+3] == vainqueur && g[i+2][i+4] == vainqueur && g[i+3][i+5] == vainqueur){
                g[i][i+2] = 'R';
                g[i+1][i+3] = 'R';
                g[i+2][i+4] = 'R';
                g[i+3][i+5] = 'R';
            }
        }
    } else if (mode == 8){ //diagonale milieu+3 droite
        for(i=0; i<NBLIG && i<NBCOL; i++){
            if (g[i][i+3] == vainqueur && g[i+1][i+4] == vainqueur && g[i+2][i+5] == vainqueur && g[i+3][i+6] == vainqueur){
                g[i][i+3] = 'R';
                g[i+1][i+4] = 'R';
                g[i+2][i+5] = 'R';
                g[i+3][i+6] = 'R';
            }
        }
    } else if (mode == 9){ //diagonale milieu droite
        for(i=0; i<NBLIG && i<NBCOL; i++){
            if (g[i][NBCOL-1-i] == vainqueur && g[i+1][NBCOL-1-i-1] == vainqueur && g[i+2][NBCOL-1-i-2] == vainqueur && g[i+3][NBCOL-1-i-3] == vainqueur){
                g[i][NBCOL-1-i] = 'R';
                g[i+1][NBCOL-1-i-1] = 'R';
                g[i+2][NBCOL-1-i-2] = 'R';
                g[i+3][NBCOL-1-i-3] = 'R';
            }
        }
    } else if (mode == 10){ //diagonale milieu-1 droite
        for(i=1; i<NBLIG && i<NBCOL; i++){
            if (g[i][NBCOL-1-i+1] == vainqueur && g[i+1][NBCOL-1-i+2] == vainqueur && g[i+2][NBCOL-1-i+3] == vainqueur && g[i+3][NBCOL-1-i+4] == vainqueur){
                g[i][NBCOL-1-i+1] = 'R';
                g[i+1][NBCOL-1-i+2] = 'R';
                g[i+2][NBCOL-1-i+3] = 'R';
                g[i+3][NBCOL-1-i+4] = 'R';
            }
        }
    } else if (mode == 11){ //diagonale milieu-2 droite
        for(i=2; i<NBLIG && i<NBCOL; i++){
            if (g[i][NBCOL-1-i+2] == vainqueur && g[i+1][NBCOL-1-i+3] == vainqueur && g[i+2][NBCOL-1-i+4] == vainqueur && g[i+3][NBCOL-1-i+5] == vainqueur){
                g[i][NBCOL-1-i+2] = 'R';
                g[i+1][NBCOL-1-i+3] = 'R';
                g[i+2][NBCOL-1-i+4] = 'R';
                g[i+3][NBCOL-1-i+5] = 'R';
            }
        }
    } else if (mode == 12){ //diagonale milieu+1 gauche
        for(i=0; i<NBLIG && i<NBCOL; i++){
            if (g[i][NBCOL-1-i-1] == vainqueur && g[i+1][NBCOL-1-i-2] == vainqueur && g[i+2][NBCOL-1-i-3] == vainqueur && g[i+3][NBCOL-1-i-4] == vainqueur){
                g[i][NBCOL-1-i-1] = 'R';
                g[i+1][NBCOL-1-i-2] = 'R';
                g[i+2][NBCOL-1-i-3] = 'R';
                g[i+3][NBCOL-1-i-4] = 'R';
            }
        }
    } else if (mode == 13){ //diagonale milieu+2 gauche
        for(i=0; i<NBLIG && i<NBCOL; i++){
            if (g[i][NBCOL-1-i-2] == vainqueur && g[i+1][NBCOL-1-i-3] == vainqueur && g[i+2][NBCOL-1-i-4] == vainqueur && g[i+3][NBCOL-1-i-5] == vainqueur){
                g[i][NBCOL-1-i-2] = 'R';
                g[i+1][NBCOL-1-i-3] = 'R';
                g[i+2][NBCOL-1-i-4] = 'R';
                g[i+3][NBCOL-1-i-5] = 'R';
            }
        }
    } else if (mode == 14){ //diagonale milieu+3 gauche
        for(i=0; i<NBLIG && i<NBCOL; i++){
            if (g[i][NBCOL-1-i-3] == vainqueur && g[i+1][NBCOL-1-i-4] == vainqueur && g[i+2][NBCOL-1-i-5] == vainqueur && g[i+3][NBCOL-1-i-6] == vainqueur){
                g[i][NBCOL-1-i-3] = 'R';
                g[i+1][NBCOL-1-i-4] = 'R';
                g[i+2][NBCOL-1-i-5] = 'R';
                g[i+3][NBCOL-1-i-6] = 'R';
            }
        }
    }
}

//afficher le vainqueur (MAL CODER A REFAIRE)
void finDePartie (char vainqueur){
    if (vainqueur == INCONNU){ //si le vainqueur est inconnu, c'est que la grille est pleine et que personne n'a gagné donc match nul
        printf("\nMatch nul\n");
    } else {
        if (vainqueur == 'X'){ //si le vainqueur est le pion "X", c'est que le joueur A a gagné
            printf("\nLe joueur A a gagné !\n");
        } else if (vainqueur == 'O'){ //si le vainqueur est le pion "O", c'est que le joueur B a gagné
            printf("\nLe joueur B a gagné !\n");
    }
    }
}