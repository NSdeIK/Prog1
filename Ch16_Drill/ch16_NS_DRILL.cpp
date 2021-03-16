/*Segéd parancs
 
g++ ch16_NS_DRILL.cpp Graph.cpp Window.cpp GUI.cpp NS_window.cpp -o ch16_NS_DRILL `fltk-config --ldflags --use-images`

*/


#include "NS_window.h"
#include "Graph.h"


using namespace Graph_lib;

int main()
{
	const int szelesseg = 1920;
	const int magassag = 1080;
	NS_window ablak {Point{100,100}, szelesseg, magassag, "Vonalak"};

	return gui_main();
}
