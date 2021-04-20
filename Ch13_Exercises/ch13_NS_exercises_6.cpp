/*Segéd parancs
    g++ ch13_NS_exercises_6.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o ch13exercises_6 `fltk-config --ldflags --use-images`
*/

#include "Simple_window.h"
#include "Graph.h"

int main()
try{
	using namespace Graph_lib;
	typedef Graph_lib::SzovegBox box;
	typedef Graph_lib::Nyil nyil;
	// 1200x1200 méret
	int szelesseg = 1200;
	int magassag = 1200;

	//Egyszerű window létrehozása
	Simple_window ablak {Point{100,100},szelesseg,magassag,"NS_DEIK - CH13 Exercises - 6 feladat"};
	
	
	vector<box> dobozok{
		SzovegBox(Point{50,50}, "Window", 2),
		SzovegBox(Point{150,50}, "Line_style", 2),
		SzovegBox(Point{320,50}, "Color", 2),
		SzovegBox(Point{30,150}, "Simple_window", 2),
		SzovegBox(Point{250,125}, "Shape", 2),
		SzovegBox(Point{450,150}, "Point", 2),
		SzovegBox(Point{50,225}, "Line", 2),
		SzovegBox(Point{50,225}, "Line", 2),
		SzovegBox(Point{125,225}, "Lines", 2),
		SzovegBox(Point{220,225}, "Polygon", 2),
		SzovegBox(Point{345,225}, "Axis", 2),
		SzovegBox(Point{430,225}, "Rectangle", 2),
		SzovegBox(Point{560,225}, "Text", 2),
		SzovegBox(Point{650,225}, "Image", 2)
	};
	
	for(int i=0; i < dobozok.size(); ++i)
	{
		dobozok[i].szinvaltas(Color::black, Color::green, Color::black);
		ablak.attach(dobozok[i]);
	}
	
	vector<nyil> nyilak
	{
		Nyil (Point{100,150}, Point{100,80}, 10),
		Nyil (Point{100,225}, Point{285,155}, 5),
		Nyil (Point{175,225}, Point{285,155}, 5),
		Nyil (Point{270,225}, Point{285,155}, 5),
		Nyil (Point{395,225}, Point{285,155}, 5),
		Nyil (Point{470,225}, Point{285,155}, 5),
		Nyil (Point{610,225}, Point{285,155}, 5),
		Nyil (Point{700,225}, Point{285,155}, 20)
	};
	
	
	for(int i=0; i < nyilak.size(); ++i)
	{
		nyilak[i].set_fill_color(Color::black);
		nyilak[i].set_color(Color::black);
		ablak.attach(nyilak[i]);
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
