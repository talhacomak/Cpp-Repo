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
 
    criticalPoint = -first/(2*second);                                      //Denklemin türevi alýnýr, kritik nokta hesaplanýr.
 
    findRoots (root1, root2);
 
    return 0;
}
 
void findRoots (float i, float j){
 
    if ( (equation(criticalPoint) > 0 && second > 0) || (equation(criticalPoint) < 0 && second < 0) || (second == 0 && first == 0) ){ //Eðer denklemin reel kökü yoksa ve ya denklem ikinci ve birinci dereceden bir denklem deðilse "No roots found" çýktýsý yazdýrýlýr.
        printf("No roots found\n");
    }
 
    else if (second != 0) {                                                 //Eðer denklem ikinci dereceden bir denklem ise iki defa (iki kök için) bisection deðeri istenir.
        i = bisection (dom1);
        j = bisection (dom2);
 
        printf("Roots: x=%.3f, x=%.3f\n",i ,j );
    }
 
    else if (second == 0) {                                                 //Eðer denklem birinci dereceden bir denklem ise sadece bir kez bisection istenir.
        i = bisection (dom1);
 
        printf("Root: x=%.3f\n",i);
    }
 
 
}
 
float bisection (float a){
    float b ,p;
 
 
    if      (second != 0)   b = criticalPoint;                              //Eðer denklem ikinci dereceden bir denklem ise bisection sýnýrlarýndan biri dom1, diðeri criticalPoint olarak belirlenir.
    else if (second == 0)   b = dom2;                                       //Eðer denklem birinci dereceden bir denklem ise bisection sýnýrlarý dom1 ve dom2 olarak belirlenir.
 
    p=(a+b)/2;
    while (equation (p) >= 0.001 || -equation (p) >= 0.001) {             //bisection iþlemleri yapýlýr, hata payý 0.001 olarak belirlenmiþtir.
 
        p=(a+b)/2;
 
        if      (equation (p) * equation (a) < 0)    b = p;
        else if (equation (p) * equation (b) < 0)    a = p;
        else                                        break;
    }
 
    return p;
}
 
 
float equation (float x){                                                   //polinom hesaplanýr
    return second*x*x + first*x + constant;
}
