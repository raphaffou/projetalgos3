#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <stdlib.h>


/* Calcule la valeur d'exponnetielle avec une certaine précision */
double expo(double precision);

/* Fonction recursive d'affichage qui renvoie
le dernier terme de la suite et qui l'affiche ainsi que
tous ses predecesseurs */
double printexp(double depval, int nbtermes);

/* Calcule la puissance nieme de x, compatible avec n<0 */
double power1(double x, long int n);

/* Même chose */
double power2a(double x, long int n);

/* Calcule la puissance nieme de x, impompatible avec n<0 */
double power3(double x, long int n);
void power3Helper(double x, long int n, double* acc);

/* Même chose mais avec une fonction au lieu d'une procédure */
double power4(double x, long int n);
double power4Helper(double x, long int n, double r);

/* Fonction power mais avec la technique n/2, recursive simple */
double power6(double x, long int n);

/* La meme fonction qu'avant, mais avec une erreur (lente) */
double power5isbad(double x, long int n);

/* Alternative à la fonction 2 crans au dessus */
double power7(double x, long int n);

/* Recursive simple avec sous fonction */
double power8(double x, long int n);
double power8Helper (double x, long int n, double r);

/* Recursive simple avec sous procedure */
double power9(double x, long int n);
void power9Helper (double x, long int n, double *r);

/* Code iteratif utilisant la technique du n/2 */
double power10(double x, long int n);

/* Ackermann recurso-iter sur n */
int ackermannRecIterN(int m, int n);

/* Ackermann recursion pure */
int ackermannRec(int m, int n);

/*recursive*/
double xnRec(int n);

/*iteratif*/
double xnIter(int n);

/* sous procedure */
double xnSP(int n);
void xnSPHelper(int n, double* acc);

/*sous fonction*/
double xnSF(int n);
double xnSFHelper(int n, double acc);

#endif
