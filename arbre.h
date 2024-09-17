#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then
typedef enum {false, true} bool;

typedef struct bloc_image
    {  
        bool toutnoir ;
        struct bloc_image* fils[4] ;
    }
    bloc_image;
typedef bloc_image* image ;

image construit_blanc();

image construit_noir();

image construit_compose(image i1,image i2,image i3,image i4);

void pr_im(image i);

void pr_im_prof_aux(image i, int p);
void pr_im_prof(image i);

image lecture();
image lecture_aux(char* c, int* cursor, int csize); //cursor inout, csize in

bool estnoir(image i);
bool estblanche(image i);

image diagonale(int p);

image quartdetour(image i);

void negatif(image* i);

void simplifie(image* i, int p);

bool incluse(image i1, image i2);

int hautMaxBlanc(image i);
void hautMaxBlancBis(image i, int* prof, bool* toutblanc);

int mypow(int x, int n);

void blanchitProfP(image *i, int p, int x, int y);

int profImage(image i);
void profBis(image i, int *prof);

int* arrayHauteur(image i, int* size);

void arrayHauteurBis(image i, int* array, int prof, int x, int y, int profcourante);

#endif