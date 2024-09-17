#include "main.h"
#define MAX 100

double expo(double precision)
{
    int fact = 1;
    double res = 1; // on compte factorielle de 0 dès le depart
    int i = 0;
    double nthterm = 1;
    while (nthterm >= precision)
    {
        i++;
        fact *= i;
        nthterm = (1.0) / ((double)fact);
        res += nthterm;
    }
    return res;
}

double printexp(double depval, int nbtermes)
{
    if (nbtermes != 0)
    {
        double v = nbtermes * printexp(depval, nbtermes - 1) - 1.0;
        printf("%f \n", v);
        return v;
    }
    else
    {
        printf("%f \n", depval - 1);
        return depval - 1;
    }
}

double power1(double x, long int n)
{
    if (n <= 0)
    {
        if(n < 0) return 1/power1(x, -n);
        else return 1;
    }
    else
        return power1(x, n - 1) * x;
}

double power2a(double x, long int n)
{
    double r = 1;
    for (int i = 1; i <= labs(n); i++)
        r *= x;
    return (n > 0) ? r : 1/r;
}

double power3(double x, long int n)
{
    double r = 1;
    power3Helper(x, n, &r);
    return r;
}
void power3Helper(double x, long int n, double *acc)
{
    if (n != 0)
    {
        (*acc) = (*acc) * x;
        power3Helper(x, n - 1, acc);
    }
}

double power4(double x, long int n)
{
    return power4Helper(x, n, 1);
}
double power4Helper(double x, long int n, double r)
{
    if (n == 0)
        return r;
    else
        return power4Helper(x, n - 1, r * x);
}

double power6(double x, long int n)
{
    if (n == 0)
        return 1;
    else
    {
        double p = power6(x, n / 2);
        if (n % 2 == 0)
            return p * p;
        else
            return p * p * x;
    }
}

double power5isbad(double x, long int n)
{
    if (n == 0)
        return 1;
    else if (n % 2)
        return power5isbad(x, n / 2) * power5isbad(x, n / 2);
    else
        return power5isbad(x, n / 2) * power5isbad(x, n / 2) * x;
}

double power7(double x, long int n)
{
    if (n == 0)
        return 1;
    else if (n % 2 == 0)
        return power7(x * x, n / 2);
    else
        return power7(x * x, n / 2) * x;
}

double power8(double x, long int n)
{
    return power8Helper(x, n, 1);
}
double power8Helper(double x, long int n, double r)
{
    if (n == 0)
        return r;
    else if (n % 2 == 0)
        return power8Helper(x * x, n / 2, r);
    else
        return power8Helper(x * x, n / 2, r * x);
}

double power9(double x, long int n)
{
    double r = 1;
    power9Helper(x, n, &r);
    return r;
}
void power9Helper(double x, long int n, double *r)
{
    if (n != 0)
    {
        if (n % 2 == 1)
        {
            *r *= x;
        }
        power9Helper(x * x, n / 2, r);
    }
}

double power10(double x, long int n)
{
    double r = 1;
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

int ackermannRecIterN(int m, int n){
    if (m==0){
        return n+1;
    }
    else {
        int r = 1;
        for(int i = 1; i<=n+1; i++){
            r = ackermannRecIterN(m-1,r);
        }
        return r;
    }
}

int ackermannRec(int m, int n){
    if (m==0){
        return n+1;
    }
    else if (n==0){
        return ackermannRec(m-1,1);
    }
    else{
        return ackermannRec(m-1,ackermannRec(m,n-1));
    } 
}

double xnRec(int n){
    if (n==0){
        return 1;
    }else{
        double xNMoinsUn = xnRec(n-1);
        return xNMoinsUn + 2/xNMoinsUn;
    }
}

double xnIter(int n){
    double res = 1;
    while(n>=1){
        res += 2/res;
        n--;
    }
    return res;
}

double xnSP(int n){
    double res = 1;
    xnSPHelper(n, &res);
    return res;
}
void xnSPHelper(int n, double* acc){
    if(n != 0){
        *acc = (*acc) + 2/(*acc);
        xnSPHelper(n-1, acc);
    }
}

double xnSF(int n){
    return xnSFHelper(n, 1);
}
double xnSFHelper(int n, double acc){
    if(n == 0){
        return acc;
    }
    return xnSFHelper(n-1, acc+2/acc);
}

int main()
{
    printexp(expo(0.000000001), 50); 
    //semble tendre vers 0 pour les premiers termes, puis diverge. 
    //Quand on augmente la precision, se rapproche de 0 plus longtemps
    //cette suite a pour limite lim N!*e - N!*sum(1/n!) = 0 
    printf("------\n");
    double N = power10(10, 5);
    printf("N = %f\n", N);
    printf("%f\n", power10((1+1/N), N));
    printf("%f\n", power9((1+1/N), N));
    printf("%f\n", power8((1+1/N), N));
    printf("%f\n", power7((1+1/N), N));
    printf("%f\n", power6((1+1/N), N));
    printf("%f\n", power2a((1+1/N), N));//-> calcule très longtemps pour une puissance de 10 > 9
    printf("%f\n", power3((1+1/N), N));
    printf("%f\n", power1((1+1/N), N));
    printf("%f\n", power4((1+1/N), N));
    //-> l'opti de recursion terminale n'est pas effectuée :  
    // en effet, power3, power4 et power1 plantent
    // tous ensemble lorsque N est assez grand (pour depassement de pile)
    printf("------\n");
    for(int i = 0; i <= 5/*6*/; i++){
        printf("%d iterrec:%d\n",i, ackermannRecIterN(i, 0));
        printf("%d rec:%d\n",i, ackermannRec(i, 0));
    }
    //segmentation fault pour m = 6, interminable pour le recursoiteratif
    printf("------\n");
    for(int i = 0; i <= 3; i++){
        printf("%d iter:%f\n",i, xnRec(i));
        printf("%d rec:%f\n",i, xnIter(i));
        printf("%d rec SP:%f\n",i, xnSP(i));
        printf("%d rec SF:%f\n",i, xnSF(i));
    }

    printf("%d iter:%f\n",100, xnRec(100));
    printf("%d rec:%f\n",100, xnIter(100));
    printf("%d rec SP:%f\n",100, xnSP(100));
    printf("%d rec SF:%f\n",100, xnSF(100));
    return 0;
}