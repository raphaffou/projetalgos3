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
    printf( "écrivez votre image (%d char max, doit commencer par '(') : ", MAXSTRING);
    fgets(s, MAXSTRING, stdin);
    int cursor = 1; //skip first (
    return lecture_aux(s, &cursor, strlen(s));
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
    }

    for(int f = 0; f<4; f++){
        if(i->fils[f] == NULL){
            return false;
        }else if(i->fils[f]->toutnoir == false){
            if(!estnoir(i->fils[f])){
                return false;
            };
        }
    }
    return true;
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
            }else if(!estblanche(i->fils[f])){
                return false;
            };
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
    if(estblanche(i) || estnoir(i)){
        return i;
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
            (*i) = construit_noir();
        }else if(estblanche(*i)){
            printf("B\n");
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
    image simp = lecture();
    simplifie(&simp, 2);
    pr_im_prof(simp);
    printf("\n");
}