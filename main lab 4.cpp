#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "rk4.h"
#define l 0.3
#define t0 0
#define y0 5

double fun(double t,double y);
double analitycznie(double t);
double euler(double t,double y,double h,double (*fun)(double,double));

void main()
{
	double h,t,N,tk;
	double wynik_e,wynik_rk,be,brk;
	wynik_e=wynik_rk=y0;
	t=t0;
	printf("Podaj koniec przedzialu calkowania (wieksze od t0):\n");
	scanf("%lf",&tk);
	tk-=t0;
	FILE* w;
	w=fopen("wyniki.txt","w");
	printf("\t\tt:\ty dla Eulera:\tblad dla Eulera:\ty dla RK:\tblad dla RK:\n");
	fprintf(w,"N:\th:\tb³¹d Eulera:\tb³¹d RK:\n");
	for(int j=0;j<7;j++)
	{
		N=pow(2.,j);
		printf("Dla N=%lf\n",N);	
		h=tk/N;
		for(int i=0;i<N;i++)
		{
			t+=h;
			wynik_e=euler(t,wynik_e,h,fun);
			be=abs((wynik_e-analitycznie(t))/analitycznie(t));
			wynik_rk=rk4(t,wynik_rk,h,fun);
			brk=abs((wynik_rk-analitycznie(t))/analitycznie(t));
			printf("\t\t%.3lf\t%.3lf\t\t%lf\t\t%.3lf\t\t%lf\n",t,wynik_e,be,wynik_rk,brk);
			if(i==N-1)

			{
				fprintf(w,"%.lf\t%.3lf\t%lf\t%lf\n",N,h,be,brk);
			}
		}
		printf("\n");
		wynik_e=wynik_rk=y0;
		t=t0;
	}
	fclose(w);

}
double euler(double t,double y,double h,double (*fun)(double,double))
{
		y+=h*fun(t,y);
		return y;
}
double fun(double t,double y)
{
	return l*y;
}
double analitycznie(double t)
{
	return y0*exp(l*(t-t0));
}