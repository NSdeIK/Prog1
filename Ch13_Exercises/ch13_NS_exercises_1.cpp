/*Segéd parancs
    g++ ch13_NS_exercises_1.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o ch13exercises_1 `fltk-config --ldflags --use-images`
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
	Simple_window ablak {Point{100,100},szelesseg,magassag,"NS_DEIK - CH13 Exercises - 1 feladat"};
	
	//Graph.h + graph.cpp új Arc létrehozása
	Arc arc(Point{ 100, 100 }, 70, 70, 0, 210); //Pont + szélesség + magasság + szög1-től szög2-ig
	arc.set_color(Color::black);
	arc.set_fill_color(Color::red);
	
	ablak.attach(arc);
	ablak.wait_for_button();
	
	//Szögváltozása
	/*arc.set_szog(210,270);
	arc.set_color(Color::black);
	arc.set_fill_color(Color::blue);
	ablak.wait_for_button();*/
	
	
}catch(exception& e)
{
	cerr << "Hiba - (1): " << e.what() << endl; 
	return 1;
}catch(...)
{
	cerr << "Hiba - (2)\n";
	return 2;
}
