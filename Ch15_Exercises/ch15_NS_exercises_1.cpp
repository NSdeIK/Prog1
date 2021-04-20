#include "std_lib_facilities.h"

double fakt(int n) { return n > 1 ? n*fakt(n-1) : 1;} //Kijavítva...double*

//int fakt(int n) { return n > 1 ? n*fakt(n-1) : 1;} //Bugos - Könyv alapján...

int main()
{
	cout << fixed; //e miatt
	double eredmeny = 0;
	
	for(int i = 0; i <= 20; ++i)
	{
		cout << i<< "! = " << fakt(i) << endl;
	}
}


