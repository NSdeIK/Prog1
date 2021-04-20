/*Segéd parancs
    g++ ch15_NS_Approximation.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o ch15_approx `fltk-config --ldflags --use-images`
*/

#include "Simple_window.h"
#include "Graph.h"
#include <cmath>

using namespace Graph_lib;

double fakt(unsigned long long int n) { return n > 1 ? n*fakt(n-1) : 1;} //Fakt n!

/*
double exp0(x)  {return 0;} // no terms
double exp1(x)  {return 1;} // one term
double exp2(x)  {return 1+x;}  // two terms; pow(x,1)/fac(1)==x
double exp3(x)  {return 1+x+pow(x,2)/fakt(2);}
double exp4(x)  {return 1+x+pow(x,2)/fac(2)+pow(x,3)/fac(3);} 
double exp5(x)  {return 1+x+pow(x,2)/fac(2)+pow(x,3)/fac(3)+pow(x,4)/fac(4);}*/

//Sok double helyett egyszerűsítve
double term(double x, int n) { return pow(x, n) / fakt(n); }

double expe(double x, int n) //term() segítségével könnyen kiszámolható exponenciáját
{
	double osszeg = 0;
	for (int i = 0; i < n; ++i) 
	{ 
		osszeg += term(x, i); 
	}
	return osszeg;
}

int exp_N = 0;

double expN(double x)
{
    return expe(x,exp_N);
}


int main()
try{
	using namespace Graph_lib;

	// 600x600 méret
	const int szelesseg = 600;
	const int magassag = 600;

	//Egyszerű window létrehozása
	Simple_window ablak {Point{100,100},szelesseg,magassag,"Function Approximation #15.5"};

	//Információk
	const int axishossz = 400;
	const int notches = axishossz/20;
	const int xorigin = szelesseg/2;
	const int yorigin = magassag/2;
	Point origo {xorigin, yorigin};
	double min = -10;
	double max = 11;
	const double xskala = 20;
	const double yskala = 20;
	
	//Tengelyek
	Axis xtengely(Axis::x, Point(100, yorigin), axishossz, notches, "x 1 == 20 pixels");
	Axis ytengely(Axis::y, Point(xorigin, magassag-100), axishossz, notches, "y 1 == 20 pixels");
	ablak.attach(xtengely);
	ablak.attach(ytengely);

	//Függvények...
	Function real_exp(exp, min, max, origo, 200, xskala, yskala);
	real_exp.set_color(Color::blue);
	ablak.attach(real_exp);

	for (unsigned long long int n = 0; n < 50; ++n)
	{
		ostringstream ss;
		ss << "exp approximation, n == " << n;
		ablak.set_label(ss.str());
		//get next approximation:
		//Function e{ [n](double x) { return expe(x, n); },  min, max, origo, 200, xskala, yskala }; //Hibás...
		cout << fixed;
		exp_N = n;
		Function e(expN,min,max,origo,200,xskala,yskala);
		cout << n << "! --> " <<fakt(n) << endl;
		e.set_color(Color::red);
		ablak.attach(e);
		ablak.wait_for_button();
		ablak.detach(e);
	}
	ablak.wait_for_button();
	
}catch(exception& e)
{
	cerr << "Hiba - (1): " << e.what() << endl; 
	return 1;
}catch(...)
{
	cerr << "Hiba - (2)\n";
	return 2;
}