#include <stdio.h>

void csere(int* x, int* y)
{
	int seged = *x;
	*x = *y;
	*y = seged;
}

int main()
{
	int szam1 = 99, szam2 = 100;
	printf("Előtte: %i - %i\n",szam1,szam2 );

	csere(&szam1,&szam2);
	printf("Csere után: %i - %i\n",szam1,szam2 );
}