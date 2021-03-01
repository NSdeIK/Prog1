/*Segéd parancs
    g++ ch13_NS_DRILL.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o ch13drill `fltk-config --ldflags --use-images`
*/

#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;


double RANDOM()
{
	int random = (rand() % 7) +1;
	return random*100;	//1-7 számokat generálja, aztán megszorozza *100-szor
}

int main()
try{
	using namespace Graph_lib;

	// 800x1000 méret
	int szelesseg = 800;
	int magassag = 1000;

	//Egyszerű window létrehozása
	Simple_window ablak {Point{100,100},szelesseg,magassag,"My window (ch13_NS_DRILL)"};

	//Grid létrehozása

	const double kocka = 100;
	const double gridmeret = 800;
	Lines grid;

	
	for (int i = kocka; i <= gridmeret; i += kocka)
	{
		grid.add(Point{i,0}, {Point(i, gridmeret)});
		grid.add(Point{0,i}, {Point(gridmeret, i)});
	}

	//Piros átló 
	Vector_ref<Rectangle> atlo;
	for (int i = 0; i < 800;i +=100)
	{
		atlo.push_back(new Rectangle{Point{i,i},100,100});
		atlo[atlo.size()-1].set_fill_color(Color::red);
		//atlo[atlo.size()-1].set_color(Color::red);
		ablak.attach(atlo[atlo.size()-1]);
	}

	grid.set_color(Color::black);
	ablak.attach(grid);

	//200x200 képek
	Vector_ref<Image> kepek;

	kepek.push_back(new Image(Point{0,300}, "200.gif"));
	kepek.push_back(new Image(Point{200,600}, "200.gif"));
	kepek.push_back(new Image(Point{600,100}, "200.gif"));
	
	constexpr int kep_meret = 200;
	
	for(int i = 0; i< kepek.size(); ++i)
	{
		ablak.attach(kepek[i]);
	}

	//Random kép mozgatások
	
	int randomX = RANDOM();
	int randomY = RANDOM();
	Image logo(Point{randomX,randomY},"200.jpg");
	ablak.attach(logo);


	while(ablak.wait_for_button())
	{
		randomX = RANDOM();
		randomY = RANDOM();
		logo.elhelyezes(randomX,randomY);
	}

}catch(exception& e)
{
	cerr << "Hiba - (1): " << e.what() << endl; 
	return 1;
}catch(...)
{
	cerr << "Hiba - (2)\n";
	return 2;
}
