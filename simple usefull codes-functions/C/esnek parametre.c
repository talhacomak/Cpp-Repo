#include <stdarg.h>
#include <stdio.h>
#include <math.h>

/* fonksiyon �rne�i */
double p(double, int, ...);


int main(void){

double x = 1.7;

   printf("x = %lf icin:\n",x);

   printf("p(x, 1,  1.0) = %lf\n", 
           p(x, 1,  1.0));

   printf("p(x, 2,  1.0, -2.0) = %lf\n", 
           p(x, 2,  1.0, -2.0));

   printf("p(x, 3,  1.0, -2.0, 0.2) = %lf\n", 
           p(x, 3,  1.0, -2.0, 0.2));

   printf("p(x, 4,  1.0, -2.0, 0.2, 1.1) = %lf\n", 
           p(x, 4,  1.0, -2.0, 0.2, 1.1));

   printf("p(x, 5,  1.0, -2.0, 0.2, 1.1, -0.6) = %lf\n", 
           p(x, 5,  1.0, -2.0, 0.2, 1.1, -0.6));

  return 0;
}

/* Verilen x, n ve ai katsay�lar� i�in, 
   P(x,n) = a0 + a1*x + a2*x^2 + ... + an*x^n polinomu hesaplar. 
   a0, a1, ..., an katsaylar� esnek arguman olarak bildirilmi�tir. */
double p(double x, int n, ...)
{
   double a, t = 0.0;
   int i;

   /* arguman g�stericisi; ag va_list tipinde */
   va_list  ag;

   /* ag i�in bellekten n adet h�cre ay�r */
   va_start(ag, n);

   for(i=0; i<n; i++)
   {
      /* herbir arguman� s�ras�yla al */
      a = va_arg(ag, double);

      /* polinomun de�erini hesapla */
      t += a*pow(x,i);
   }

   /* belle�i bo�alt */
   va_end(ag);

   return t;
}
