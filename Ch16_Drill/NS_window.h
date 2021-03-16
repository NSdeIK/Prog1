#include "GUI.h"

using namespace Graph_lib;

struct NS_window : Graph_lib::Window
{
	NS_window(Point xy, int szel, int mag, const string& cim);
	Open_polyline vonalak;

	bool wait_for_button();

private:
	Button next_button;
	Button quit_button;
	Menu szin_menu;
	Menu vonal_stilusok;

	In_box kov_x; //Input köv. x
	In_box kov_y; //Input köv. y

	Out_box kim_xy; //Kimeneti x-y

	void szin_valtas(Color c);
	void vonal_stilus(Line_style ls);
	void kovetkezo();
	void kilepes();


	//Színek
	void Piros_jel() { szin_valtas(Color::red);}
	static void cb_piros(Address,Address pw) {reference_to<NS_window>(pw).Piros_jel();}

	void Kek_jel() { szin_valtas(Color::blue);}
	static void cb_kek(Address,Address pw) {reference_to<NS_window>(pw).Kek_jel();}

	void Zold_jel() { szin_valtas(Color::green);}
	static void cb_zold(Address,Address pw) {reference_to<NS_window>(pw).Zold_jel();}

	void Sarga_jel() { szin_valtas(Color::yellow);}
	static void cb_sarga(Address,Address pw) {reference_to<NS_window>(pw).Sarga_jel();}

	void Fekete_jel() { szin_valtas(Color::black);}
	static void cb_fekete(Address,Address pw) {reference_to<NS_window>(pw).Fekete_jel();}

};