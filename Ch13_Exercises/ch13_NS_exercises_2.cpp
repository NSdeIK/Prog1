/*Segéd parancs
    g++ ch13_NS_exercises_2.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o ch13exercises_2 `fltk-config --ldflags --use-images`
*/

#include "Simple_window.h"
#include "Graph.h"

int main()
try{
	using namespace Graph_lib;

	// 1200x1200 méret
	int szelesseg = 1200;
	int magassag = 1200;

	//Egyszerű window létrehozása
	Simple_window ablak {Point{100,100},szelesseg,magassag,"NS_DEIK - CH13 Exercises - 2 feladat"};
	Box box(Point(100,100), 300, 100, 3);
		box.set_color(Color::red);
	box.set_fill_color(Color::cyan);
	ablak.attach(box);
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
