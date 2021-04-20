/*Segéd parancs
    g++ ch13_NS_exercises_7.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o ch13exercises_7 `fltk-config --ldflags --use-images`
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
	Simple_window ablak {Point{100,100},szelesseg,magassag,"NS_DEIK - CH13 Exercises - 7 feladat"};
	
	typedef Graph_lib::Rectangle rect;
	Vector_ref<rect> r;
	
	for(int i=0; i<= 128; ++i)
		for(int j=0; j<= 128; ++j)
		{
				r.push_back(new rect{ Point{i*8, j*8},10,10});
				r[r.size()-1].set_fill_color(Color{i+j});
				ablak.attach(r[r.size()-1]);
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
