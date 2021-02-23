/*Segéd parancs
    g++ ch12_NS_DRILL.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o ch12drill `fltk-config --ldflags --use-images`
*/

#include "Simple_window.h"
#include "Graph.h"

int main()
try{
	using namespace Graph_lib;

	// 600x400 méret
	int szelesseg = 600;
	int magassag = 400;

	//Egyszerű window létrehozása
	Simple_window ablak {Point{100,100},szelesseg,magassag,"My window (ch12_NS_DRILL)"};

	//Tengely létrehozása
	//X tengely

	Axis xa {Axis::x, Point{20,300},120, 12,"x tengely"};

	//Y tengely
	Axis ya {Axis::y, Point{20,300},120, 12, "y tengely"};

	//Tengely színek
	xa.set_color(Color::blue);
	ya.set_color(Color::red);

	//Tengely label színek
	xa.label.set_color(Color::cyan);
	ya.label.set_color(Color::yellow);

	// Sin fgv.     (sin,0-20 range, honnan (pont x,y), 120 pixel pont x,y * 6 - skála)
	Function sinfgv {sin,0,20,Point{20,275},1200,6,6};

	//Poly
	Polygon poly;
	poly.add(Point{300,300});
	poly.add(Point{250,180});
	poly.add(Point{200,300});

	//Poly színek
	poly.set_color(Color::white);

	//Poly szaggatott vonal
	poly.set_style(Line_style(Line_style::dash,4));

	//Poly kitöltés színe
	poly.set_fill_color(Color::red);

	//Rectangle - Nyitott
	Rectangle r {Point{20,20}, 560,40};
		//Szín
		r.set_fill_color(Color::cyan);
	Rectangle r2 {Point{100,60}, 400,40};
		r2.set_fill_color(Color::red);

	//Rectangle - Zárt
	Closed_polyline poly_rect;
	poly_rect.add(Point{20,20});
	poly_rect.add(Point{100,20});
	poly_rect.add(Point{100,75});
	poly_rect.add(Point{20,75});
		//Szín
		poly_rect.set_fill_color(Color::white);

	//Szövegek
	Text t {Point{150,50}, "Debreceni Egyetem - Prog1"};
	t.set_font(Font::times_bold);
	t.set_font_size(24);

	//Képek
	Image logo {Point{32,21}, "logo.jpg"};

	//Kör
	Circle c {Point{450,240},50};
	c.set_fill_color(Color::blue);

	//Nem működik
	//Ellipse e {Point{450,240},75,25};
	//e.set_color(Color::green);

	//Jelölő pont
	Mark m{Point{250,270},'x'};

	//Képernyő méret kiiratása
	ostringstream oss;
	oss << "Kepernyo meret: " << x_max() <<" * "<< y_max() 
		<< "; Ablak meret: " << ablak.x_max() << " * " << ablak.y_max();
	Text t2 {Point{110,80},oss.str()}; 

	//Csatolások
	ablak.attach(c);
	ablak.attach(r2);
	ablak.attach(r);
	ablak.attach(poly_rect);
	ablak.attach(poly);
	ablak.attach(sinfgv);
	ablak.attach(xa);
	ablak.attach(ya);
	ablak.attach(t);
	ablak.attach(t2);
	ablak.attach(logo);
	ablak.attach(m);


	// Next (Kilépés...)
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