/*Segéd parancs
    g++ ch14_NS_exercises.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o ch14exercises `fltk-config --ldflags --use-images`
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
	Simple_window ablak {Point{100,100},szelesseg,magassag,"NS_DEIK - CH14 Exercises - 1,11-14 feladat"};

	
	Smiley mosoly (Point{300,300},60);
	mosoly.set_fill_color(Color::yellow);
	Frowny szomoru (Point{600,600},60);
	szomoru.set_fill_color(Color::red);
	
	ablak.attach(szomoru);
	ablak.attach(mosoly);
	ablak.wait_for_button();
	
	ablak.detach(mosoly);
	ablak.detach(szomoru);
	Binaris_fa fa(Point(800, 100), 3, "egyenes");
	
	fa.set_fill_color(Color::blue);
	fa.set_color(Color::red);
	ablak.attach(fa);

	ablak.wait_for_button();
	ablak.detach(fa);
	
	Binaris_fa_kocka fa2(Point(600,100), 3, "egyenes");
	fa2.set_fill_color(Color::yellow);
	ablak.attach(fa2);
	
	ablak.wait_for_button();
	ablak.detach(fa2);
	
	Binaris_fa_haromszog fa3(Point(600,100), 3, "nyil");
	fa3.set_fill_color(Color::magenta);
	ablak.attach(fa3);
	//fa3.cimkek("b","Root");
	//fa3.cimkek("bb","Bal");
	fa3.cimkek("bbb","Bal-Bal");
	//fa3.cimkek("bbbbbb","Utolso-Bal");
	//fa3.cimkek("bj","Jobb");
	//fa3.cimkek("bjj","Jobb-Jobb");
	//fa3.cimkek("bjjjjj","Utolso-Jobb");



	
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
