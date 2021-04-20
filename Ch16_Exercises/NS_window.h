
#include "calculator.h"
#include "GUI.h"
#include "Graph.h"

using namespace Graph_lib;

struct NS_window : Graph_lib::Window
{
	NS_window(Point xy, int w, int h, const string& title);

private:

	Button clear_button,quit_button;
	Out_box input,output;
	vector<Button*> buttons;
	string input_value, result;
	
	void clear();
	void quit();
	void pressed(char c);
	
	Calc::Calculator Calcu;

};
