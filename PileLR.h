#ifndef PILE

#define PILE

#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then




/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste;

typedef struct Bloc_l
{ 
    Liste liste;
    struct Bloc_l *suivant;
} Bloc_l;

typedef Bloc_l *Liste_l;

typedef struct Bloc_lb
{
    int nombre;
    struct Bloc_lb *suivant;
    struct Bloc_lb **precedent;
} Bloc_lb;

typedef Bloc_lb *ListeBis;

typedef enum {false, true} bool;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* revoie un pointeur vers une liste sans la première valeur de cette liste */
Liste* suitePtr(Liste* l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);


void initVide_l(Liste_l *L);
bool estVide_l(Liste_l L);
Liste premier_l(Liste_l l);
Liste_l ajoute_l(Liste x, Liste_l l);
void empile_l(Liste x, Liste_l *l);
Liste_l suite_l(Liste_l l);
void depile_l(Liste_l *l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);

/* Regarde si la liste comporte une zéro dans les 3 premières positions */
bool ZeroEnPositionUnOuDeuxOuTrois(Liste l);

/* Regarde si la liste l1 est strictement plus grande que l2 */
bool PlusCourte(Liste l1, Liste l2);

/* compte le nombre de 0 avant une certaine position (recursive non terminale)*/
int NombreDe0AvantUnePositionK_rec(Liste l, int k);

/* compte le nombre de 0 avant une certaine position (itérative)*/
int NombreDe0AvantUnePositionK_iter(Liste l, int k);

/* compte le nombre de 0 avant une certaine position (sous-fonction recursive terminale)*/
int NombreDe0AvantUnePositionK_recTerm(Liste l, int k);
int Bis_recTerm(Liste, int, int);

/* compte le nombre de 0 avant une certaine position (sous-procédure recursive terminale)*/
int NombreDe0AvantUnePositionK_recTermProc(Liste l, int k);
void Bis_recTermProc(Liste, int, int*);

/* compte de nombre de 0 jusqu'à la kieme position depuis la fin */
int NombreDe0ApresRetroPositionK(Liste l, int k);
void Bis_N0Retro(Liste l, int* k, int* cpt);


/* Renvoie une liste avec tout les éléments positifs dupliqués (recursif) */
Liste FctBegaye_rec(Liste l);

/* Renvoie une liste avec tout les éléments positifs dupliqués (recursif terminal) */
Liste FctBegaye_recTerm(Liste l);
void Bis_fctBegaye(Liste l, Liste* s);

/* Renvoie une liste avec tout les éléments positifs dupliqués (itératif) */
Liste FctBegaye_iter(Liste l);

/* Modifie la liste d'entrée en dupliquant chaque element strctement positif et retire les autres */
void ProcBegaye(Liste* l);

// fonctions pour Permutations

// Concatenne deux listes de listes
Liste_l Concat(Liste_l l1, Liste_l l2);
// Ajoute en-tête toutes listes (ajoute un elmt x en tête de chaque liste d'une liste de listes)
Liste_l AETTL(int x, Liste_l l);
// ajoute toutes positions
Liste_l ATP(int x, Liste l);
// ajoute toutes listes toutes positions
Liste_l ATLTP(int x, Liste_l l);
// Donne toutes les permutations d'une liste l (renvoie une liste de liste)
Liste_l Permutations(Liste l);

#endif