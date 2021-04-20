/*Help command
 
g++ NS_main.cpp Graph.cpp Window.cpp GUI.cpp NS_window.cpp calculator.cpp -o NS_calculator `fltk-config --ldflags --use-images`

*/


#include "NS_window.h"
//#include "Graph.h"


int main()
{
	const int width = 1920;
	const int height = 1080;
	NS_window window {Point{100,100}, width, height, "NS - Calculator"};

	return gui_main();
}
