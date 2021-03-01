/*Segéd parancs
    g++ ch12_NS_exercises.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o ch12exercises `fltk-config --ldflags --use-images`
*/

#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;
//4-es feladat segéd 
Rectangle alap(Color szin, int x, int y)
{
	Rectangle rect(Point{ x, y }, 100,100);
	rect.set_fill_color(szin);
	rect.set_color(Color::black);
	return rect;

}
int main()
try{
	using namespace Graph_lib;

	// 1920x1080 méret
	int szelesseg = 1920;
	int magassag = 1080;

	//Egyszerű window létrehozása
	Simple_window ablak {Point{100,100},szelesseg,magassag,"NS_DEIK - CH12 Exercises"};
	
	
	//Visszatérő 6-os feladat
	//Simple_window ablak{ Point{100,100}, 2000, 2000, "NS_DEIK - CH12 Exercises - 6 feladat" };
	
//1. feladat 
	//Piros színnel
	Polygon p;
	p.add(Point { 700, 300 });
	p.add(Point { 700, 250 });
	p.add(Point { 800, 250 });
	p.add(Point { 800, 300});
	p.set_color(Color::red);
	ablak.attach(p);
	
	//Kék színnel
	Rectangle r {Point{700,150}, 100, 50}; // 100 px széles, 50 px magas
	r.set_color(Color::blue);
	ablak.attach(r);

//2.feladat
	Rectangle r2 {Point{700,210}, 100, 30}; //100x30 
	Text t {Point{715,230},"Howdy!"}; //Belülről legyen "Howdy" felirat
	ablak.attach(t);
	ablak.attach(r2);
	
//3.feladat NS felirat (vastasággal, és színekkel együtt)
	Open_polyline N;
	N.add(Point{ 220, 350 });
	N.add(Point{ 220, 200 });
	N.add(Point{ 370, 350 });
	N.add(Point{ 370, 200 });
	N.set_style(Line_style{Line_style::solid, 12});
	N.set_color(Color::dark_cyan);
	ablak.attach(N);

	Open_polyline S;
	S.add(Point{ 450, 200 });
	S.add(Point{ 375, 250 });
	S.add(Point{ 450, 300 });
	S.add(Point{ 375, 350 });
	S.set_style(Line_style{ Line_style::solid, 12 });
	S.set_color(Color::blue);
	ablak.attach(S);

//4.feladat 3-3 tic-tac-toc
	//Leegyszerűsítve egy picit
	typedef Graph_lib::Rectangle rect;
	
	vector<rect> v_rects{
		alap(Color::red, 1000,200),
		alap(Color::white, 1100,200),
		alap(Color::red, 1200,200),
		alap(Color::white, 1000,300),
		alap(Color::red, 1100,300),
		alap(Color::white, 1200,300),
		alap(Color::red, 1000,400),
		alap(Color::white, 1100,400),
		alap(Color::red, 1200,400)
	};
	
	for(int i=0; i < v_rects.size(); ++i)
		ablak.attach(v_rects[i]);

//5.feladat frame ...

	rect frame(Point{100,100}, 1440,720);
	frame.set_style(Line_style {Line_style::solid, 24});
	frame.set_color(Color::red);
	ablak.attach(frame);	

//6.feladat
	//Simple_window ablak{ Point{100,100}, 2000, 2000, "NS_DEIK - CH12 Exercises - 6 feladat" };
	//Mi a helyzet, hogyha ablak nagyobb mint a monitor mérete?
	// - Folytatja, átfedi akár másik monitorra is
	
	//Mi a helyzet, hogyha shape nagyobb mint az ablak mérete?
	// Alak le van vágva,amikor az ablak széleihez ér (ha csak nem sizeolunk ki)
	//rect hatos(Point{ 100, 100 }, 700, 600);
	//hatos.set_color(Color::yellow);
	//ablak.attach(hatos);

//7.feladat (háttér, smoke, ház, fű)
	Image hetes {Point{625,600}, "haziko.jpeg"};
	ablak.attach(hetes);

//8.feladat (olimpia)
	Circle kek{ Point{200, 650},75 };
	kek.set_color(Color::blue);
	kek.set_style(Line_style {Line_style::solid, 10});
	ablak.attach(kek);

	Circle sarga{ Point{260, 700},75 };
	sarga.set_color(Color::yellow);
	sarga.set_style(Line_style {Line_style::solid, 10 });
	ablak.attach(sarga);

	Circle fekete{ Point{320, 650},75 };
	fekete.set_color(Color::black);
	fekete.set_style(Line_style{Line_style::solid, 10 });
	ablak.attach(fekete);

	Circle zold{ Point{380, 700},75 };
	zold.set_color(Color::green);
	zold.set_style(Line_style {Line_style::solid, 10 });
	ablak.attach(zold);

	Circle piros{ Point{420, 650},75 };
	piros.set_color(Color::red);
	piros.set_style(Line_style{Line_style::solid, 10 });
	ablak.attach(piros);

//9.feladat

	Image kep { Point{1100,650}, "baratom.jpg" };
	ablak.attach(kep);
	
	Text baratszoveg{ Point{1100,625}, "My friend (A kep illusztracio)" };
	baratszoveg.set_font_size(20);
	baratszoveg.set_color(Color::dark_blue);
	ablak.attach(baratszoveg);
	
	
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
