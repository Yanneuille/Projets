/**
* @file version4.c
* @brief Programme d'un jeu de snake avec deux serpents.
* @author yann le guennec
* @version 4.0
* @date 12/01/2025 
*
* Le programme dessine un plateau de jeu avec deux serpents ainsi qu'une pomme.
* Les serpents doivent manger 10 pommes tout en évitant les obstacles et l'autre serpent.
* Le programme résout automatiquement le jeu. 
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>

// taille des serpents
#define TAILLE 10
// dimensions du plateau
#define LARGEUR_PLATEAU 80
#define HAUTEUR_PLATEAU 40
#define MID_LARGEUR LARGEUR_PLATEAU/2
#define MID_HAUTEUR HAUTEUR_PLATEAU/2
// positions initiales des têtes des serpents
#define X1_INITIAL 40
#define Y1_INITIAL 13
#define X2_INITIAL 40
#define Y2_INITIAL 27
// nombre de pommes à manger pour gagner
#define NB_POMMES 10
// temporisation entre deux déplacements des serpents (en microsecondes)
#define ATTENTE 70000
// caractères pour représenter les serpents
#define CORPS1 'X'
#define TETE1 '1'
#define CORPS2 'O'
#define TETE2 '2'
// touches de direction ou d'arrêt du jeu
#define HAUT 'z'
#define BAS 's'
#define GAUCHE 'q'
#define DROITE 'd'
#define STOP 'a'
// position des pavés
#define LONGUEUR_PAVES 5
#define HAUTEUR_PAVES 5		
#define NB_PAVES 6
// caractères pour les éléments du plateau
#define BORDURE '#'
#define ESPACE ' '
#define POMME '6'

// définition d'un type pour le plateau : tPlateau
typedef char tPlateau[LARGEUR_PLATEAU + 1][HAUTEUR_PLATEAU + 1];

typedef struct {
  int x;
  int y;
} t_position;

// Prototypes des fonctions
void gotoxy(int x, int y);
void dessinerSerpent(int lesX[], int lesY[], char corps, char tete);
void progresser1(int lesX[], int lesY[], char *direction, tPlateau plateau, bool *collision, bool *pomme, t_position positionPomme, int lesX2[], int lesY2[]);
void progresser2(int lesX[], int lesY[], char *direction, tPlateau plateau, bool *collision, bool *pomme, t_position positionPomme, int lesX1[], int lesY1[]);
void afficher(int, int, char);
void effacer(int x, int y);
void disable_echo();
void enable_echo();
int kbhit();
void initPlateau(tPlateau plateau, int lesPavesX[], int lesPavesY[]);
void dessinerPlateau(tPlateau plateau);
t_position ajouterPomme(tPlateau plateau, int nbPommes, int lesPommesX[], int lesPommesY[]);
void cheminPomme(int lesX[], int lesY[], t_position positionPomme, t_position *teleporteur);

int main() {
    // décompte du temps CPU
    clock_t begin = clock();
    clock_t end;
    double tmpsCPU;

    // tableaux avec éléments des serpents
    int lesX1[TAILLE], lesY1[TAILLE];
    int lesX2[TAILLE], lesY2[TAILLE];

    // Tableau avec positions des pommes
    int lesPommesX[NB_POMMES] = {40, 75, 78, 2, 9, 78, 74, 2, 72, 5};
    int lesPommesY[NB_POMMES] = {20, 38, 2, 2, 5, 38, 32, 38, 32, 2};

    // Tableau avec positions des pavés
    int lesPavesX[NB_PAVES] = {4, 73, 4, 73, 38, 38};
    int lesPavesY[NB_PAVES] = {4, 4, 33, 33, 14, 22};

    // directions des serpents
    char direction1 = DROITE;
    char direction2 = GAUCHE;

    // plateau de jeu
    tPlateau lePlateau;

    bool collision1 = false, collision2 = false;
    bool pommeMangee1 = false, pommeMangee2 = false;

    // décompte des pommes mangées
    int nbPommes1 = 0, nbPommes2 = 0;
    int pommeIndex = 0;

    t_position positionPomme;

    // initialisation des positions des serpents
    for (int i = 0; i < TAILLE; i++) {
        lesX1[i] = X1_INITIAL - i;
        lesY1[i] = Y1_INITIAL;
        lesX2[i] = X2_INITIAL + i;
        lesY2[i] = Y2_INITIAL;
    }

    // mise en place du plateau
    initPlateau(lePlateau, lesPavesX, lesPavesY);
    system("clear");
    dessinerPlateau(lePlateau);

    // placement de la première pomme
    positionPomme = ajouterPomme(lePlateau, pommeIndex, lesPommesX, lesPommesY);

    // boucle de jeu
    do {
        // serpent 1 se déplace
        progresser1(lesX1, lesY1, &direction1, lePlateau, &collision1, &pommeMangee1, positionPomme, lesX2, lesY2);
        if (pommeMangee1) {
            nbPommes1++;
            pommeIndex++;
            if (pommeIndex < NB_POMMES) {
                positionPomme = ajouterPomme(lePlateau, pommeIndex, lesPommesX, lesPommesY);
            }
        }

        dessinerSerpent(lesX1, lesY1, CORPS1, TETE1);

        // serpent 2 se déplace
        progresser2(lesX2, lesY2, &direction2, lePlateau, &collision2, &pommeMangee2, positionPomme, lesX1, lesY1);
        if (pommeMangee2) {
            nbPommes2++;
            pommeIndex++;
            if (pommeIndex < NB_POMMES) {
                positionPomme = ajouterPomme(lePlateau, pommeIndex, lesPommesX, lesPommesY);
            }
        }

        dessinerSerpent(lesX2, lesY2, CORPS2, TETE2);

        usleep(ATTENTE);

    } while (pommeIndex < NB_POMMES && !collision1 && !collision2);

    // fin du jeu
    end = clock();
    tmpsCPU = ((double)(end - begin)) / CLOCKS_PER_SEC;

    gotoxy(1, HAUTEUR_PLATEAU + 2);
    printf("Serpent1 : %d pommes mangées\n", nbPommes1);
    printf("Serpent2 : %d pommes mangées\n", nbPommes2);
    printf("Temps CPU : %.3f secondes\n", tmpsCPU);

    return EXIT_SUCCESS;
}

// Fonction pour dessiner un serpent
void dessinerSerpent(int lesX[], int lesY[], char corps, char tete) {
    for (int i = 1; i < TAILLE; i++) {
        afficher(lesX[i], lesY[i], corps);
    }
    afficher(lesX[0], lesY[0], tete);
}

// Fonction pour initialiser le plateau
void initPlateau(tPlateau plateau, int lesPavesX[], int lesPavesY[]) {
    for (int i = 1; i <= LARGEUR_PLATEAU; i++) {
        for (int j = 1; j <= HAUTEUR_PLATEAU; j++) {
            plateau[i][j] = ESPACE;
        }
    }

    for (int i = 1; i <= LARGEUR_PLATEAU; i++) {
        plateau[i][1] = BORDURE;
        plateau[i][HAUTEUR_PLATEAU] = BORDURE;
    }
    for (int j = 1; j <= HAUTEUR_PLATEAU; j++) {
        plateau[1][j] = BORDURE;
        plateau[LARGEUR_PLATEAU][j] = BORDURE;
    }

    for (int p = 0; p < NB_PAVES; p++) {
        for (int x = lesPavesX[p]; x < lesPavesX[p] + LONGUEUR_PAVES && x <= LARGEUR_PLATEAU; x++) {
            for (int y = lesPavesY[p]; y < lesPavesY[p] + HAUTEUR_PAVES && y <= HAUTEUR_PLATEAU; y++) {
                plateau[x][y] = BORDURE;
            }
        }
    }
}

// Fonction pour déterminer le chemin vers la pomme
void cheminPomme(int lesX[], int lesY[], t_position positionPomme, t_position *teleporteur) {
    teleporteur->x = positionPomme.x;
    teleporteur->y = positionPomme.y;
}
