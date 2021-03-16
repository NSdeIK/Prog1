/*Segéd parancs
    g++ ch15_NS_DRILL1.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o ch15drill_1 `fltk-config --ldflags --use-images`
*/

#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

//1.feladat

double one(double x)
{
	return 1;
}

//4.feladat

double slope(double x)
{
	return x/2;
}

//6.feladat

double square(double x) 
{ 
	return x*x; 
}

//9.feladat

double sloping_cos(double x)
{
	return cos(x) + slope(x);
}


int main()
try{
	using namespace Graph_lib;

	// 600x600 méret
	const int szelesseg = 600;
	const int magassag = 600;

	//Egyszerű window létrehozása
	Simple_window ablak {Point{100,100},szelesseg,magassag,"Function graphs.#2 (ch15_NS_DRILL_2)"};

	//Információk
	const int axishossz = 400;
	const int notches = 400/20;
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
	
	//Lehívások
	
	Function f_one {one, min, max, origo, axishossz, xskala, yskala};
	f_one.set_color(Color::red);
	ablak.attach(f_one);
	
	Function f_slope {slope, min, max, origo, axishossz, xskala, yskala};
	f_slope.set_color(Color::dark_green);
	Text slope_text {Point{f_slope.point(0).x, f_slope.point(0).y-15},"x/2"};
	ablak.attach(f_slope);
	ablak.attach(slope_text);
	
	
	Function f_square {square, min, max, origo, axishossz, xskala, yskala};
	f_square.set_color(Color::blue);
	ablak.attach(f_square);
	
	Function f_cos {cos, min, max, origo, axishossz, xskala, yskala};
	f_cos.set_color(Color::cyan);
	ablak.attach(f_cos);
	
	Function f_sloping_cos {sloping_cos, min, max, origo, axishossz, xskala, yskala};
	f_sloping_cos.set_color(Color::magenta);
	ablak.attach(f_sloping_cos);
	
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
