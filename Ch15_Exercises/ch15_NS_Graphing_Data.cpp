#include "Graph.h"
#include "Window.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"
#include <fstream>
using namespace Graph_lib;

//g++ ch15_NS_Graphing_Data.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o ch15_graph `fltk-config --ldflags --use-images`

struct Beolvasas
{
	int ev, osszesen, felvettek;
};

class Scale
{
	int cbase;		
	int vbase;		
	double scale;
public:
	Scale(const int b, const int vb, const double s) : cbase{ b }, vbase{ vb }, scale{ s } { }
	int operator()(int v) const { return cbase + (v - vbase) * scale; }
};

std::istream &operator>>(std::istream &is, Beolvasas &d);

int main()
{

	try
	{
		constexpr int xmax = 600;	// Ablak meret
		constexpr int ymax = 400;

		constexpr int xoffset = 100;	
		constexpr int yoffset = 60;		

		constexpr int xspace = 40;		
		constexpr int yspace = 40;

		constexpr int xlength = xmax - xoffset - xspace;	
		constexpr int ylength = ymax - yoffset - yspace;

		constexpr int kezdo_ev = 2005;
		constexpr int vege_ev = 2022;

		constexpr double xscale = double(xlength) / (vege_ev - kezdo_ev);
		constexpr double yscale = double(ylength) / 1750;

		Scale xs{ xoffset, kezdo_ev, xscale };
		Scale ys{ ymax - yoffset, 0, -yscale };

		Simple_window ablak{ Point{100, 100}, xmax, ymax, "DE-IK - Jelentkezok/Felvettek" };

		Axis x{ Axis::x, Point{xoffset, ymax - yoffset}, xlength,
			(vege_ev - kezdo_ev) / 5, "ev      2005                      2010                       2015                        2020    "};
		x.label.move(-100, 0);

		Axis y{ Axis::y, Point{xoffset, ymax - yoffset}, ylength, 10, "Max:1750" };


		string fajlnev = "egyetem.txt";
		ifstream ifs{ fajlnev };
		if (!ifs)
		{
			error("nem lehet megnyitni ", fajlnev);
		}

		Open_polyline osszesen;
		Open_polyline felvettek;

		for (Beolvasas d; ifs >> d;)
		{
			if (d.ev < kezdo_ev || d.ev > vege_ev)
			{
				error("Range kivul van az evszamok");
			}
			
			const int x = xs(d.ev);
			osszesen.add(Point{ x, ys(d.osszesen) });
			felvettek.add(Point{ x, ys(d.felvettek) });
		}

		Text osszesen_label{ Point{20, osszesen.point(0).y}, "Osszesen" };
		osszesen.set_color(Color::red);
		osszesen_label.set_color(Color::red);

		Text felvettek_label{ Point{20, felvettek.point(0).y}, "Felvettek" };
		felvettek.set_color(Color::blue);
		felvettek_label.set_color(Color::blue);


		ablak.attach(osszesen);
		ablak.attach(felvettek);
		ablak.attach(osszesen_label);
		ablak.attach(felvettek_label);
		ablak.attach(x);
		ablak.attach(y);

		ablak.wait_for_button();

	}catch(exception&e)
	{
		cerr << e.what() << endl;
	}
}

std::istream &operator>>(std::istream &is, Beolvasas &d)
	// Formaja: (ev: osszesen felvettek )
{
	char ch1 = 0;
	char ch2 = 0;
	char ch3 = 0;
	Beolvasas dd;

	if (is >> ch1 >> dd.ev >> ch2 >> dd.osszesen >> dd.felvettek >> ch3)
	{
		if (ch1 != '(' || ch2 != ':' || ch3 != ')')
		{
			is.clear(std::ios_base::failbit); //
			return is;
		}
	}
	else
	{
		return is;
	}
	d = dd;
	return is;
}
