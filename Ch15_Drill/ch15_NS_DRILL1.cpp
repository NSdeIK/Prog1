/*Segéd parancs
    g++ ch15_NS_DRILL1.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o ch15drill_1 `fltk-config --ldflags --use-images`
*/

#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

int main()
try{
	using namespace Graph_lib;

	// 600x600 méret
	int szelesseg = 600;
	int magassag = 600;

	//Egyszerű window létrehozása
	Simple_window ablak {Point{100,100},szelesseg,magassag,"Function graphs. (ch15_NS_DRILL_1)"};

	//4-es feladat
	int axishossz = 400;
	int notches = 400/20;
	int xorigin = szelesseg/2;
	int yorigin = magassag/2;
	
	Axis xtengely(Axis::x, Point(100, yorigin), axishossz, notches, "x 1 == 20 pixels");
	//            x tengely, honnan induljon ki, hosszúság, notches,    label
	xtengely.set_color(Color::red);
	
	Axis ytengely(Axis::y, Point(xorigin, magassag-100), axishossz, notches, "y 1 == 20 pixels");
	ytengely.set_color(Color::red);
	
	ablak.attach(xtengely);
	ablak.attach(ytengely);
	
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
