#include <stdio.h>
 
float second, first, constant, dom1, dom2 ,criticalPoint;
 
float equation (float x);
float bisection (float a);
void findRoots (float i, float j);
 
int main(){
 
    float x, root1, root2;
 
    scanf("%f%f%f%f%f" ,&second ,&first ,&constant, &dom1, &dom2);
 
    printf("Entered equation: %.0fx^2 + %.0fx + %.0f\n",second ,first ,constant);
    printf("Domain: %.0f, %.0f\n",dom1 ,dom2 );
 
    criticalPoint = -first/(2*second);                                      //Denklemin t�revi al�n�r, kritik nokta hesaplan�r.
 
    findRoots (root1, root2);
 
    return 0;
}
 
void findRoots (float i, float j){
 
    if ( (equation(criticalPoint) > 0 && second > 0) || (equation(criticalPoint) < 0 && second < 0) || (second == 0 && first == 0) ){ //E�er denklemin reel k�k� yoksa ve ya denklem ikinci ve birinci dereceden bir denklem de�ilse "No roots found" ��kt�s� yazd�r�l�r.
        printf("No roots found\n");
    }
 
    else if (second != 0) {                                                 //E�er denklem ikinci dereceden bir denklem ise iki defa (iki k�k i�in) bisection de�eri istenir.
        i = bisection (dom1);
        j = bisection (dom2);
 
        printf("Roots: x=%.3f, x=%.3f\n",i ,j );
    }
 
    else if (second == 0) {                                                 //E�er denklem birinci dereceden bir denklem ise sadece bir kez bisection istenir.
        i = bisection (dom1);
 
        printf("Root: x=%.3f\n",i);
    }
 
 
}
 
float bisection (float a){
    float b ,p;
 
 
    if      (second != 0)   b = criticalPoint;                              //E�er denklem ikinci dereceden bir denklem ise bisection s�n�rlar�ndan biri dom1, di�eri criticalPoint olarak belirlenir.
    else if (second == 0)   b = dom2;                                       //E�er denklem birinci dereceden bir denklem ise bisection s�n�rlar� dom1 ve dom2 olarak belirlenir.
 
    p=(a+b)/2;
    while (equation (p) >= 0.001 || -equation (p) >= 0.001) {             //bisection i�lemleri yap�l�r, hata pay� 0.001 olarak belirlenmi�tir.
 
        p=(a+b)/2;
 
        if      (equation (p) * equation (a) < 0)    b = p;
        else if (equation (p) * equation (b) < 0)    a = p;
        else                                        break;
    }
 
    return p;
}
 
 
float equation (float x){                                                   //polinom hesaplan�r
    return second*x*x + first*x + constant;
}
