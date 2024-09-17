#include "arbre.h"
#define MAXSTRING 500

image construit_blanc(){
    return NULL;
}

image construit_noir(){
    bloc_image* b = (bloc_image *)malloc(sizeof(bloc_image));
    b->toutnoir = true;
    for(int f = 0; f<4; f++){
        b->fils[f] = NULL;
    }
    return b;
}

void free_image(image i){
    if(i == NULL){
        return;
    }else if(i->toutnoir){
        free(i);
        i = NULL;
    }else{
        for(int f = 0; f<4; f++){
            free_image(i->fils[f]);
        }
        free(i);
        i = NULL;
    }
}

image construit_compose(image i1,image i2,image i3,image i4){
    bloc_image* b = (bloc_image *)malloc(sizeof(bloc_image));
    b->toutnoir = false;
    b->fils[0] = i1;
    b->fils[1] = i2;
    b->fils[2] = i3;
    b->fils[3] = i4;
    return b;
}

void pr_im(image i){
    if(i == NULL){
        printf("B");
    }else if(i->toutnoir){
        printf("N");
    }else{
        printf("(");
        for(int f = 0; f<4; f++){
            pr_im(i->fils[f]);
        }
        printf(")");
    }
}

void pr_im_prof_aux(image i, int p){
    if(i == NULL){
        printf("B%d ", p);
    }else if(i->toutnoir){
        printf("N%d ", p);
    }else{
        printf("( ");
        for(int f = 0; f<4; f++){
            pr_im_prof_aux(i->fils[f], p+1);
        }
        printf(") ");
    }

}
void pr_im_prof(image i){
    pr_im_prof_aux(i, 0);
}

image lecture(){
    char s[MAXSTRING];
    printf( "écrivez votre image (%d char max, doit commencer par '(', 'B', ou 'N') : ", MAXSTRING);
    fgets(s, MAXSTRING, stdin);
    if(s[0] == 'B'){
        return construit_blanc();
    }else if(s[0] == 'N'){
        return construit_noir();
    }else{
        int cursor = 1; //skip first (
        return lecture_aux(s, &cursor, strlen(s));
    }
}
image lecture_aux(char* c, int* cursor, int csize){ //cursor inout
    image im = malloc(sizeof(bloc_image));
    int currentson = 0;
    do{
        if(*cursor >= 500 || csize<=(*cursor)){break; /*error, invalid format provided, did not see enough closing parenthesis*/}

        if(c[(*cursor)] == '('){
            (*cursor)++;
            image inside = lecture_aux(c, cursor, csize);
            im->fils[currentson] = inside;
            currentson++;
        }else if(c[(*cursor)] == 'B'){
            im->fils[currentson] = construit_blanc();
            currentson++;
        }else if(c[(*cursor)] == 'N'){
            im->fils[currentson] = construit_noir();
            currentson++;
        }
        (*cursor)++;
    }while(c[(*cursor)] != ')' && currentson < 4);
    if(currentson != 4){
        /*error, invalid format, closed too early -> filled with whites*/
    }
    return im;
}

bool estnoir(image i){
    if(i == NULL){
        return false;
    }else if(i->toutnoir){
        return true;
    }else{
        return estnoir(i->fils[0]) && estnoir(i->fils[1]) && estnoir(i->fils[2]) && estnoir(i->fils[3]);
    }
}

bool estblanche(image i){
    if(i == NULL){
        return true;
    }else if(i->toutnoir){
        return false;
    }

    for(int f = 0; f<4; f++){
        if(i->fils[f] != NULL){ //lourdeur ?
            if(i->fils[f]->toutnoir == true){
                return false;
            }
        }
    }
    return true;
}

image diagonale(int p){
    if(p == 0){
        return construit_noir();
    }
    image d = diagonale(p-1);
    return construit_compose(d, construit_blanc(), construit_blanc(), d);
}

image quartdetour(image i){
    if(i == NULL){
        return construit_blanc();
    }else if(i->toutnoir){
        return construit_noir();
    }else{
        image f1 = quartdetour(i->fils[0]);
        image f2 = quartdetour(i->fils[1]);
        image f3 = quartdetour(i->fils[2]);
        image f4 = quartdetour(i->fils[3]);
        return construit_compose(f3,f1,f4,f2);
    }
}

void negatif(image* i){
    if(*i == NULL){
        *i = construit_noir();
    }else if((*i)->toutnoir){
        free((*i));
        *i = construit_blanc();
    }else{
        for(int f = 0; f<4; f++){
            negatif(&((*i)->fils[f]));
        }
    }
}

void simplifie(image* i, int p){
    printf("simplification (p = %d) \n", p);
    if(p == 0){
        printf("P0\n");
        if(estnoir(*i)){
            printf("N\n");
            free_image((*i));
            (*i) = construit_noir();
        }else if(estblanche(*i)){
            printf("B\n");
            free_image((*i));
            (*i) = construit_blanc();
        }
    }else{
        if((*i) == NULL || (*i)->toutnoir){
            return ;
        }else{
            for(int f = 0; f<4; f++){
                simplifie(&((*i)->fils[f]), p-1);
            }
        }
    }
}

bool incluse(image i1, image i2){
    if(i1 == NULL){
        return true;
    }else if(i1->toutnoir){
        pr_im(i1);
        printf("\n");
        pr_im(i2);
        bool res = estnoir(i2);
        printf("  : %d\n----\n", res);
        return res;
    }else if(i2 == NULL){
        pr_im(i1);
        printf("\n");
        pr_im(i2);
        bool res = estblanche(i1);
        printf("  : %d\n----\n", res);
        return res;
    }else if(i2->toutnoir){
        return true;
    }else{
        printf("JE FAIS UNE RECURSION \n");
        return incluse(i1->fils[0], i2->fils[0])
            && incluse(i1->fils[1], i2->fils[1])
            && incluse(i1->fils[2], i2->fils[2])
            && incluse(i1->fils[3], i2->fils[3]);
    }
}

int max(int a, int b){
    if(a>b){
        return a;
    }else{
        return b;
    }
}

int hautMaxBlanc(image i){
    int prof;
    bool toutblanc;
    hautMaxBlancBis(i, &prof, &toutblanc);
    return prof;
}
void hautMaxBlancBis(image i, int* prof, bool* toutblanc){
    //erreur de denomination, c'est hauteur pas profondeur (mais ça marche)
    if(i == NULL){
        *prof = 0;
        *toutblanc = true;
    }else if(i->toutnoir){
        *prof = -1;
        *toutblanc = false;
    }else{
        int prof1, prof2, prof3, prof0;
        bool toutblanc1, toutblanc2, toutblanc3, toutblanc0;
        hautMaxBlancBis(i->fils[0], &prof0, &toutblanc0);
        hautMaxBlancBis(i->fils[1], &prof1, &toutblanc1);
        hautMaxBlancBis(i->fils[2], &prof2, &toutblanc2);
        hautMaxBlancBis(i->fils[3], &prof3, &toutblanc3);
        if(toutblanc0 && toutblanc1 && toutblanc2 && toutblanc3){
            (*prof) = max(
                        max(prof0, prof1), 
                        max(prof2,prof3)
                    ) + 1;
            (*toutblanc) = true;
        }else{
            (*prof) = max(
                        max(prof0, prof1), 
                        max(prof2,prof3)
                    );
            (*toutblanc) = false;
        }
    }
}

int mypow(int x, int n)
{
    int r = 1;
    while (n != 0)
    {
        if (n % 2 == 1)
        {
            r *= x;
        }
        n = n / 2;
        x = x * x;
    }
    return r;
}


void blanchitProfP(image *i, int p, int x, int y){
    if(p == 0){
        free_image((*i));
        (*i) = construit_blanc(); 
    }else{
        int hw = mypow(2, p-1);
        printf("x: %d\ny: %d\nhw: %d\n", x, y, hw);
        if(i == NULL){
            (*i) = construit_compose(
                        construit_blanc(),
                        construit_blanc(),
                        construit_blanc(),
                        construit_blanc()
                    );
        }else if((*i)->toutnoir){
            (*i) = construit_compose(
                        construit_noir(),
                        construit_noir(),
                        construit_noir(),
                        construit_noir()
                    );
        }
        if(x + 1 <= hw){
            if(y + 1 <= hw){
                //bas à gauche
                blanchitProfP(&((*i)->fils[2]), p-1, x, y);
            }else{
                //haut à gauche
                blanchitProfP(&((*i)->fils[0]), p-1, x, y - (hw - 1));
            }
        }else{
            if(y + 1 <= hw){
                //bas à droite
                blanchitProfP(&((*i)->fils[3]), p-1, x - (hw - 1), y);

            }else{
                //haut à droite
                blanchitProfP(&((*i)->fils[1]), p-1,  x - (hw - 1), y - (hw - 1));
            }
        }
    }
}

int profImage(image i){
    int prof;
    profBis(i, &prof);
    return prof;
}
void profBis(image i, int *prof){
    if(i == NULL){
        (*prof) = 0;
    }else if(i->toutnoir){
        (*prof) = 0;
    }else{
        int prof1, prof2, prof3, prof0;
        profBis(i->fils[0], &prof0);
        profBis(i->fils[1], &prof1);
        profBis(i->fils[2], &prof2);
        profBis(i->fils[3], &prof3);
        (*prof) = max(
                    max(prof0, prof1), 
                    max(prof2,prof3)
                ) + 1;
    }
}

int* arrayHauteur(image i, int *size){
    int prof = profImage(i);
    int* array = malloc(sizeof(int) * mypow(2,prof));
    arrayHauteurBis(i, array, prof, 0, 0, 0);
    *size = mypow(2,prof);
    return array;
}
void arrayHauteurBis(image i, int* array, int prof, int x, int y, int profcourante){
    if(i == NULL){
        //do nothing
    }else if(i->toutnoir){
        int w = mypow(2, prof - profcourante); //nb micropixels image courante (c'est la prof globale - la prof de l'image courante)
        for (int i = 0; i < w; i++)
        {
            array[w*x + i] += w;
        }
    }else{
        int newprofcourante = profcourante + 1; //puissance de 2
        arrayHauteurBis(i->fils[0], array, prof, 2*x, 2*y + 1, newprofcourante);
        arrayHauteurBis(i->fils[1], array, prof, 2*x + 1, 2*y + 1, newprofcourante);
        arrayHauteurBis(i->fils[2], array, prof, 2*x, 2*y, newprofcourante);
        arrayHauteurBis(i->fils[3], array, prof, 2*x + 1, 2*y, newprofcourante);
    }
}
//chute utilise arrayHauteur, qui parcourt chaque case 2 fois, mais on a pas eu le temps de le faire


int main(){
    image b1 = construit_noir();
    image b2 = construit_noir();
    image w1 = construit_blanc();
    image w2 = construit_blanc();
    image i = construit_compose(b1,b2,w1,w2);
    image i2 = construit_compose(i,b2,i,w2);
    pr_im(i2);
    printf("\n");
    printf("Test lecture : ");
    //image i3 = lecture();
    //pr_im(i3);
    printf("\n");
    printf("Test est noir : \n");
    //printf("%d", estnoir(lecture()));
    printf("\n");
    printf("Test est blanc : \n");
    //printf("%d", estblanche(lecture()));
    printf("\n");
    printf("Test diagonale : \n");
    pr_im(diagonale(3));
    printf("\n");
    printf("Test quart de tour : \n");
    /* image i4 = lecture();
    pr_im(quartdetour(i4)); */
    printf("\n");
    printf("Test negatif : \n");
    /* image neg = lecture();
    negatif(&neg);
    pr_im(neg); */
    printf("\n");
    printf("Test simplifie : \n");
    /* image simp = lecture();
    simplifie(&simp, 2);
    pr_im_prof(simp); */
    printf("\n");
    printf("Test incluse : \n");
    /* image inc1 = lecture();
    image inc2 = lecture();
    printf("%d", incluse(inc1, inc2)); */
    printf("\n");
    printf("Test hautmaxblanc : \n");
/*     image ihaut = lecture();
    printf("%d", hautMaxBlanc(ihaut)); */
    printf("\n");
    printf("Test blanchit profP : \n");
    image modif = lecture();
    blanchitProfP(&modif, 2, 1, 3);
    pr_im(modif);
    printf("\n");
    printf("Test arrayHauteur : \n");
    image testHauteur = lecture();
    int size;
    int *array = arrayHauteur(testHauteur, &size);
    for(int i = 0; i < size; i++){
        printf("%d ", array[i]);
    }
}