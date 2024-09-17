#include "PileLR.h"

int nbMallocListe;
int nbMallocListe_l;

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


void initVide( Liste *L)
{
    *L = NULL ;
}


bool estVide(Liste l)
{
    return l == NULL ;
}


int premier(Liste l)
{
    return l->nombre ;
}


Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    nbMallocListe++;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}


void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ; 
}


Liste suite(Liste l)
{
    return l->suivant ;
}


Liste* suitePtr(Liste* l)
{
    return &((*l)->suivant);
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}


void initVide_l(Liste_l *L)
{
    *L = NULL;
} 


bool estVide_l(Liste_l L)
{
    return L == NULL;
}


Liste premier_l(Liste_l l)
{
    return l->liste;
}


Liste_l ajoute_l(Liste x, Liste_l l)
{
    Liste_l tmp = (Liste_l)malloc(sizeof(Bloc_l));
    nbMallocListe_l++;
    tmp->liste = x;
    tmp->suivant = l;
    return tmp;
}


void empile_l(Liste x, Liste_l *l)
{
    *l = ajoute_l(x, *l);
}


Liste_l suite_l(Liste_l l)
{
    return l->suivant;
}


void depile_l(Liste_l *l)
{ 
    Liste_l tmp = *l;
    *l = suite_l(*l);
    free(tmp);
}



/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( ((**L).suivant) == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
     if ( (*L) ISNOT NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
                 L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
     }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }
      
}


/*************************************************/
/*                                               */
/*           Zero en position 1, 2 ou 3          */
/*                                               */
/*************************************************/

bool ZPUDT_bis(Liste l, int acc)
{
    if(estVide(l) OR acc == 3) return false;
    else if(premier(l) == 0) return true;
    else return ZPUDT_bis(suite(l), acc+1);
}

bool ZeroEnPositionUnOuDeuxOuTrois(Liste l) { return ZPUDT_bis(l, 0); }

/*************************************************/
/*                                               */
/*           Plus courte entre 2 listes          */
/*                                               */
/*************************************************/

bool PlusCourte(Liste l1, Liste l2)
{
    if(estVide(l2))
        return false;
    else if(estVide(l1))
        return true;
    return PlusCourte(suite(l1), suite(l2));
}

/*************************************************/
/*                                               */
/*          Nbr de 0 avant une position          */
/*                                               */
/*************************************************/

// recursive non terminale
int NombreDe0AvantUnePositionK_rec(Liste l, int k)
{
    if(estVide(l) OR k == 0) return 0;
    else if(premier(l) == 0) 
        return 1 + NombreDe0AvantUnePositionK_rec(suite(l), k-1);
    else 
        return NombreDe0AvantUnePositionK_rec(suite(l), k-1);
}

// iterative
int NombreDe0AvantUnePositionK_iter(Liste l, int k)
{
    int cpt = 0;
    while (k > 0 AND NOT estVide(l)){
        if(premier(l) == 0) cpt++;
        l = suite(l);
        k--;
    }
    return cpt;

}

// recursive (sous-fonction)
int NombreDe0AvantUnePositionK_recTerm(Liste l, int k)
{
    return Bis_recTerm(l, k, 0);
}

int Bis_recTerm(Liste l, int k, int cpt)
{
    if(k < 1 OR estVide(l)) 
        return cpt;
    else if(premier(l) == 0) 
        return Bis_recTerm(suite(l), k-1, cpt+1);
    else 
        return Bis_recTerm(suite(l), k-1, cpt);
}

// recursive (sous-procédure)
int NombreDe0AvantUnePositionK_recTermProc(Liste l, int k)
{
    int cpt = 0;
    Bis_recTermProc(l, k, &cpt);
    return cpt;
}

void Bis_recTermProc(Liste l, int k, int* cpt)
{
    if(k < 1 OR estVide(l)) 
        return;
    else if(premier(l) == 0) (*cpt)++;
    
    Bis_recTermProc(suite(l), k-1, cpt);
}


/*************************************************/
/*                                               */
/*            Nbr de 0 depuis jusqu'à            */
/*         la kieme posit° depuis la fin         */
/*                                               */
/*************************************************/

int NombreDe0ApresRetroPositionK(Liste l, int k)
{
    int cpt = 0;
    Bis_N0Retro(l, &k, &cpt);
    return cpt;
}
void Bis_N0Retro(Liste l, int* k, int* cpt)
{
    if(NOT estVide(l)){
        Bis_N0Retro(suite(l), k, cpt);
        if(*k > 0) {;
            if(premier(l) == 0) (*cpt)++;
            (*k)--;
        }
    }
}

/*************************************************/
/*                                               */
/*            Renvoie une liste avec             */
/*      tous les nombres positifs dupliqués      */
/*                                               */
/*************************************************/

Liste FctBegaye_rec(Liste l)
{
    if(estVide(l)) return NULL;
    else if (premier(l) > 0)
        return ajoute(premier(l), ajoute(premier(l), FctBegaye_rec(suite(l))));
    else return FctBegaye_rec(suite(l));
}


Liste FctBegaye_recTerm(Liste l)
{
    Liste res = NULL;
    Bis_fctBegaye(l, &res);
    return res;
}

void Bis_fctBegaye(Liste l, Liste* s)
{
    if(NOT estVide(l)) {
        if(premier(l) > 0)
        {
            empile(premier(l), s);
            empile(premier(l), suitePtr(s));
            Bis_fctBegaye(suite(l), suitePtr(suitePtr(s)));

        }
        else Bis_fctBegaye(suite(l),  s);
    }
}


Liste FctBegaye_iter(Liste l)
{
    Liste res = NULL;
    Liste* s = &res;
    while (NOT estVide(l))
    {
        if(premier(l) > 0)
        {
            empile(premier(l), s);
            empile(premier(l), suitePtr(s));
            s = suitePtr(suitePtr(s));
        } 
        l = suite(l);
    } 
    return res;
} 

/*************************************************/
/*                                               */
/*             Modifie une liste en              */
/*     dupliquant tous les nombres positifs      */
/*                                               */
/*************************************************/

void ProcBegaye(Liste* l)
{
    if(NOT estVide(*l)) {
        if(premier(*l) > 0)
        {
            empile(premier(*l), l);
            ProcBegaye(suitePtr(suitePtr(l)));
        }
        else 
        {
            depile(l);
            ProcBegaye(l);
        }
    }
}


/*************************************************/
/*                                               */
/*                 Permutations                  */
/*                                               */
/*************************************************/

Liste_l Concat(Liste_l l1, Liste_l l2)
{ 
    if(estVide_l(l1)) return l2;
    else return ajoute_l(premier_l(l1), Concat(suite_l(l1), l2));
}

Liste_l AETTL(int x, Liste_l l)
{
    if(estVide_l(l)) return NULL;
    else return ajoute_l(ajoute(x, premier_l(l)), AETTL(x, suite_l(l)));
}

Liste_l ATP(int x, Liste l)
{ 
    
    if(estVide(l))
    {
        Liste_l tmp = NULL;
        Liste tmp2; initVide(&tmp2); empile(x, &tmp2);
        empile_l(tmp2, &tmp);
        return tmp;
    }
    else return ajoute_l(ajoute(x, l), AETTL(premier(l), ATP(x, suite(l)))); 
}  
   
Liste_l ATLTP(int x, Liste_l l)
{ 
    if(estVide_l(l)) return NULL;
    else return Concat(ATP(x, premier_l(l)), ATLTP(x, suite_l(l)));
}


Liste_l Permutations(Liste l)
{
    if(estVide(l)) 
    {
        Liste_l tmp = (Liste_l)malloc(sizeof(Bloc_l));
        nbMallocListe_l++;
        tmp->liste = NULL;
        tmp->suivant = NULL;
        return tmp;
    }
    else return ATLTP(premier(l), Permutations(suite(l)));
}

void empileBis(int n, ListeBis *l){
    Bloc_lb* B = (Bloc_lb *)malloc(sizeof(Bloc_lb));
    B->nombre = n;
    B->precedent = l;
    B->suivant = *l;
    if(*l != NULL){
        (**l).precedent = &(B->suivant);
    }
    *l = B;
}

void afficheBis(ListeBis l){
    if(l == NULL){
        printf("\n");
    }
    else
    {
        printf("%d ", l->nombre);
        afficheBis(l->suivant);
    }
}

void retireBlocP(Bloc_lb ** *P){
    //P pointe sur "precedent", un pointeur vers un pointeur de bloc
    Bloc_lb** pSuivantBefore = *P;
    Bloc_lb* pBlocASup = *pSuivantBefore;
    Bloc_lb *next = (*pBlocASup).suivant;

    if(pBlocASup->suivant != NULL){
        pBlocASup->suivant->precedent = pSuivantBefore;
    }
    *pSuivantBefore = next;

    free(pBlocASup);
}
void fuitePermut(Liste l, int *n1, int *n2)
{
    nbMallocListe = 0;
    nbMallocListe_l = 0;
    Permutations(l);
    *n1 = nbMallocListe;
    *n2 = nbMallocListe_l;
    nbMallocListe = 0;
    nbMallocListe_l = 0;
}


/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup (Liste l)
{
        printf("Double Affichage \n") ;
        affiche_rec(l) ;
        affiche_iter(l) ;

        printf("Longueur en double %d %d \n\n", 
                           longueur_rec(l), 
                           longueur_iter(l) 
               ) ;
}



int main(int argc, char** argv)
{
    Liste l ;

        initVide (&l) ;

          poup(l) ;

             empile(4, &l) ;

          poup(l) ;

             empile(5, &l) ;
             empile(6, &l) ;
             empile(7, &l) ;
             empile(8, &l) ;
             empile(9, &l) ;

          poup(l) ;

        VireDernier_rec  (&l) ;
        VireDernier_iter (&l) ;
        depile(& l) ;

          poup(l) ;

    VideListe(&l);

    //test ZeroEnPositionUnOuDeuxOuTrois
    printf("\033[1;4mTest ZeroEnPositionUnOuDeuxOuTrois :\033[0m\n");
        empile(1, &l);
        affiche_rec(l);
        printf("->%d\n", ZeroEnPositionUnOuDeuxOuTrois(l));
        VideListe(&l);

        empile(8, &l);
        empile(2, &l);
        empile(0, &l);
        empile(4, &l);
        empile(3, &l);
        affiche_rec(l);
        printf("->%d\n", ZeroEnPositionUnOuDeuxOuTrois(l));
        VideListe(&l);

        empile(2, &l);
        empile(0, &l);
        affiche_rec(l);
        printf("->%d\n", ZeroEnPositionUnOuDeuxOuTrois(l));
        VideListe(&l);

        empile(8, &l);
        empile(2, &l);
        empile(0, &l);
        empile(5, &l);
        empile(4, &l);
        empile(3, &l);
        affiche_rec(l);
        printf("->%d\n", ZeroEnPositionUnOuDeuxOuTrois(l));
        VideListe(&l);
        
        empile(2, &l);
        empile(9, &l);
        affiche_rec(l);
        printf("->%d\n", ZeroEnPositionUnOuDeuxOuTrois(l));
        VideListe(&l);
    
    printf("\n\033[1;4mTest PlusCourte :\033[0m\n");
        Liste l1, l2;
        initVide(&l1); initVide(&l2);
        empile(8, &l1);
        empile(2, &l1);
        empile(0, &l1);
        empile(4, &l1);
        empile(3, &l1);

        empile(2, &l2);
        empile(0, &l2);
        printf("l1 = ");
        affiche_rec(l1);

        printf("l2 = ");
        affiche_rec(l2);
        printf("->%d\n", PlusCourte(l1, l2));

        Liste tmp = l2;
        l2 = l1;
        l1 = tmp;
        printf("l1 = ");
        affiche_rec(l1);
        printf("l2 = ");
        affiche_rec(l2);
        printf("->%d\n", PlusCourte(l1, l2));
        
        l1 = l2;
        printf("l1 = ");
        affiche_rec(l1);
        printf("l2 = ");
        affiche_rec(l2);
        printf("->%d\n", PlusCourte(l1, l2));
        VideListe(&l1);


    printf("\n\033[1;4mTest NombreDe0AvantUnePositionK :\033[0m\n");
        empile(0, &l);
        empile(1, &l);
        empile(0, &l);
        empile(0, &l);
        empile(0, &l);
        empile(9, &l);
        empile(6, &l);
        empile(5, &l);
        empile(0, &l);
        empile(2, &l);
        affiche_rec(l);
        printf("Recursif : \n");
        printf("->%d (k = 0)\n", NombreDe0AvantUnePositionK_rec(l, 0));
        printf("->%d (k = 1)\n", NombreDe0AvantUnePositionK_rec(l, 1));
        printf("->%d (k = 6)\n", NombreDe0AvantUnePositionK_rec(l, 6));
        printf("->%d (k = 7)\n", NombreDe0AvantUnePositionK_rec(l, 7));
        printf("->%d (k = 11)\n", NombreDe0AvantUnePositionK_rec(l, 10));

        printf("Iteratif : \n");
        printf("->%d (k = 0)\n", NombreDe0AvantUnePositionK_iter(l, 0));
        printf("->%d (k = 1)\n", NombreDe0AvantUnePositionK_iter(l, 1));
        printf("->%d (k = 6)\n", NombreDe0AvantUnePositionK_iter(l, 6));
        printf("->%d (k = 7)\n", NombreDe0AvantUnePositionK_iter(l, 7));
        printf("->%d (k = 11)\n", NombreDe0AvantUnePositionK_iter(l, 10));

        printf("Recursif terminal (sous-fonction) : \n");
        printf("->%d (k = 0)\n", NombreDe0AvantUnePositionK_recTerm(l, 0));
        printf("->%d (k = 1)\n", NombreDe0AvantUnePositionK_recTerm(l, 1));
        printf("->%d (k = 6)\n", NombreDe0AvantUnePositionK_recTerm(l, 6));
        printf("->%d (k = 7)\n", NombreDe0AvantUnePositionK_recTerm(l, 7));
        printf("->%d (k = 11)\n", NombreDe0AvantUnePositionK_recTerm(l, 10));
        
        printf("Recursif terminal (sous-procédure) : \n");
        printf("->%d (k = 0)\n", NombreDe0AvantUnePositionK_recTermProc(l, 0));
        printf("->%d (k = 1)\n", NombreDe0AvantUnePositionK_recTermProc(l, 1));
        printf("->%d (k = 6)\n", NombreDe0AvantUnePositionK_recTermProc(l, 6));
        printf("->%d (k = 7)\n", NombreDe0AvantUnePositionK_recTermProc(l, 7));
        printf("->%d (k = 11)\n", NombreDe0AvantUnePositionK_recTermProc(l, 10));
        
        VideListe(&l);

        empile(3, &l);
        empile(0, &l);
        empile(0, &l);
        empile(5, &l);
        affiche_rec(l);
        printf("->%d (k = 6) Récursif\n", NombreDe0AvantUnePositionK_rec(l, 6));
        printf("->%d (k = 6) Itératif\n", NombreDe0AvantUnePositionK_iter(l, 6));
        printf("->%d (k = 6) Récursif terminal (sous-fonction)\n", NombreDe0AvantUnePositionK_recTerm(l, 6));
        printf("->%d (k = 6) Récursif terminal (sous-procédure)\n", NombreDe0AvantUnePositionK_recTermProc(l, 6));

        VideListe(&l);


    printf("\n\033[1;4mTest NombreDe0ApresRetroPositionK :\033[0m\n");
        empile(2, &l);
        empile(0, &l);
        empile(5, &l);
        empile(6, &l);
        empile(9, &l);
        empile(0, &l);
        empile(0, &l);
        empile(1, &l);
        empile(0, &l);
        affiche_rec(l);
        printf("->%d (k = 0)\n", NombreDe0ApresRetroPositionK(l, 0));
        printf("->%d (k = 6)\n", NombreDe0ApresRetroPositionK(l, 6));
        printf("->%d (k = 7)\n", NombreDe0ApresRetroPositionK(l, 7));
        printf("->%d (k = 9)\n", NombreDe0ApresRetroPositionK(l, 9));
        printf("->%d (k = 11)\n", NombreDe0ApresRetroPositionK(l, 11));

        VideListe(&l);
        empile(3, &l);
        empile(0, &l);
        empile(0, &l);
        empile(5, &l);
        affiche_rec(l);
        printf("->%d (k = 6)\n", NombreDe0ApresRetroPositionK(l, 6));
        VideListe(&l);
    
    printf("\n\033[1;4mTest FctBegaye :\033[0m\n");
        printf("Recursif : \n");
        empile(8, &l);
        empile(8, &l);
        empile(-2, &l);
        empile(6, &l);
        empile(0, &l);
        empile(1, &l);
        empile(2, &l);
        affiche_rec(l);
        
        printf("->"); affiche_rec(FctBegaye_rec(l));

        printf("Recursif terminale: \n");
        affiche_rec(l);
        printf("->"); affiche_rec(FctBegaye_recTerm(l));

        printf("Itératif : \n");
        affiche_rec(l);
        printf("->"); affiche_rec(FctBegaye_iter(l));

    printf("\n\033[1;4mTest ProcBegaye :\033[0m\n");
        printf("ProcBegaye : \n");
        affiche_rec(l);
        ProcBegaye(&l);
        printf("->"); affiche_rec(l);
        VideListe(&l);

    printf("\n\033[1;4mTest Permutations\033[0m\n");
        empile(1, &l);
        empile(2, &l);
        empile(3, &l);
        empile(4, &l);
        printf("Permutations : \n"); affiche_rec(l);

        printf("->\n");
        Liste_l res = Permutations(l);
        
        while(NOT estVide_l(res)){ 
            affiche_rec(premier_l(res));
            res = suite_l(res);
        }
        int liste, liste_l; 
        fuitePermut(l, &liste, &liste_l);
        printf("Nombre de Malloc de liste : %d \nNombre de Malloc de liste de liste : %d \n", liste, liste_l);
        VideListe(&l);
        
        printf("[]\n->"); 
        res = Permutations(l);
        while(NOT estVide_l(res)){ 
            affiche_rec(premier_l(res));
            res = suite_l(res);
        }
        empile(1, &l);
        affiche_rec(l);
        printf("->"); 
        res = Permutations(l);
        while(NOT estVide_l(res)){ 
            affiche_rec(premier_l(res));
            res = suite_l(res);
        }

    printf("\n\033[1;4mTest retireBlocP\033[0m\n");
        ListeBis lb = NULL;
        empileBis(1, &lb);
        empileBis(2, &lb);
        empileBis(3, &lb);
        empileBis(4, &lb);
        printf("test affichebis : \n"); 
        afficheBis(lb);
        retireBlocP(&(lb->suivant->suivant->suivant->precedent));
        afficheBis(lb);
        retireBlocP(&(lb->precedent));
        afficheBis(lb);

    
    return 0;
}
