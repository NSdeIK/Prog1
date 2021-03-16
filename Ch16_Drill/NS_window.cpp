#include "NS_window.h"

NS_window::NS_window(Point xy, int szel, int mag, const string& cim) : Window{xy,szel,mag,cim},
next_button{Point{525,0}, 150, 40, "Kovetkezo pont", [](Address,Address pw) {reference_to<NS_window>(pw).kovetkezo();}},
quit_button{Point{x_max()-150,0}, 150, 40, "Kilepes", [](Address,Address pw) {reference_to<NS_window>(pw).kilepes();}},
kov_x{Point{300,0}, 50, 40, "Kov. x:"},
kov_y{Point{450,0}, 50, 40, "Kov. y:"},
kim_xy{Point{100,0}, 100, 40, "(x,y):"},
szin_menu{Point{x_max()-200,80}, 200, 40, Menu::vertical,"Szinek"},
vonal_stilusok{Point{x_max()-200,360}, 200, 40, Menu::vertical, "Vonal stilusok"}
{

	attach(next_button);
	attach(quit_button);
	attach(kov_x);
	attach(kov_y);
	attach(kim_xy);
	attach(vonalak);
	
	//Színek
	szin_menu.attach(new Button {Point(0,0), 0, 0, "Piros", cb_piros});
	szin_menu.attach(new Button {Point(0,0), 0, 0, "Kek", cb_kek});
	szin_menu.attach(new Button {Point(0,0), 0, 0, "Zold", cb_zold});
	szin_menu.attach(new Button {Point(0,0), 0, 0, "Sarga", cb_sarga});
	szin_menu.attach(new Button {Point(0,0), 0, 0, "Fekete", cb_fekete});
	attach(szin_menu);

	//Vonal stílusok
	vonal_stilusok.attach(new Button {Point(0,0), 0, 0, "Sima", [](Address, Address pw) {reference_to<NS_window>(pw).vonal_stilus(Line_style::solid);}});
	vonal_stilusok.attach(new Button {Point(0,0), 0, 0, "Szaggasztott", [](Address, Address pw) {reference_to<NS_window>(pw).vonal_stilus(Line_style::dash);}});
	vonal_stilusok.attach(new Button {Point(0,0), 0, 0, "Pontszeru", [](Address, Address pw) {reference_to<NS_window>(pw).vonal_stilus(Line_style::dot);}});
	attach(vonal_stilusok);

}


void NS_window::kilepes()
{
	hide();
}

void NS_window::kovetkezo()
{
	int x = kov_x.get_int();
	int y = kov_y.get_int();

	vonalak.add(Point{x,y});

	ostringstream ss;
	ss << '(' << x << ';' << y << ')';
	kim_xy.put(ss.str());

	redraw();
}

void NS_window::szin_valtas(Color c)
{
	vonalak.set_color(c);
	redraw();
}

void NS_window::vonal_stilus(Line_style ls)
{
	vonalak.set_style(ls);
	redraw();
}