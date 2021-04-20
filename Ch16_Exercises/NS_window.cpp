#include "NS_window.h"

NS_window::NS_window(Point xy, int w, int h, const string& title) : Window{xy,w,h,title},
clear_button{Point{400,150}, 150, 40, "Clear", [](Address,Address pw) {reference_to<NS_window>(pw).clear();}},
quit_button{Point{400,210}, 150, 40, "Quit", [](Address,Address pw) {reference_to<NS_window>(pw).quit();}},
input{Point{100,100}, 400, 25, "Input: "},
output{Point{100,30}, 400, 25, " Result: "}
{
	buttons.push_back(new Button{ Point(150,350), 100, 50, "C",[](Address, Address window) 					{ reference_to<NS_window>(window).pressed('x'); } });
	
	buttons.push_back(new Button{ Point(150,150), 50, 50, "(",[](Address, Address window) 					{ reference_to<NS_window>(window).pressed('('); } });
	buttons.push_back(new Button{ Point(200,150), 50, 50, ")",[](Address, Address window) 					{ reference_to<NS_window>(window).pressed(')'); } });
	buttons.push_back(new Button{ Point(250,150), 50, 50, "%",[](Address, Address window) 					{ reference_to<NS_window>(window).pressed('%'); } });
	buttons.push_back(new Button{ Point(300,150), 50, 50, "/",[](Address, Address window) 					{ reference_to<NS_window>(window).pressed('/'); } });
	
	buttons.push_back(new Button{ Point(150,200), 50, 50, "7",[](Address, Address window) 					{ reference_to<NS_window>(window).pressed('7'); } });
	buttons.push_back(new Button{ Point(200,200), 50, 50, "8",[](Address, Address window) 					{ reference_to<NS_window>(window).pressed('8'); } });
	buttons.push_back(new Button{ Point(250,200), 50, 50, "9",[](Address, Address window) 					{ reference_to<NS_window>(window).pressed('9'); } });
	buttons.push_back(new Button{ Point(300,200), 50, 50, "*",[](Address, Address window) 					{ reference_to<NS_window>(window).pressed('*'); } });
	
	buttons.push_back(new Button{ Point(150,250), 50, 50, "4",[](Address, Address window) 					{ reference_to<NS_window>(window).pressed('4'); } });
	buttons.push_back(new Button{ Point(200,250), 50, 50, "5",[](Address, Address window) 					{ reference_to<NS_window>(window).pressed('5'); } });
	buttons.push_back(new Button{ Point(250,250), 50, 50, "6",[](Address, Address window) 					{ reference_to<NS_window>(window).pressed('6'); } });
	buttons.push_back(new Button{ Point(300,250), 50, 50, "-",[](Address, Address window) 					{ reference_to<NS_window>(window).pressed('-'); } });
	
	buttons.push_back(new Button{ Point(150,300), 50, 50, "1",[](Address, Address window) 					{ reference_to<NS_window>(window).pressed('1'); } });
	buttons.push_back(new Button{ Point(200,300), 50, 50, "2",[](Address, Address window) 					{ reference_to<NS_window>(window).pressed('2'); } });
	buttons.push_back(new Button{ Point(250,300), 50, 50, "3",[](Address, Address window) 					{ reference_to<NS_window>(window).pressed('3'); } });
	buttons.push_back(new Button{ Point(300,300), 50, 50, "+",[](Address, Address window) 					{ reference_to<NS_window>(window).pressed('+'); } });
	
	buttons.push_back(new Button{ Point(250,350), 50, 50, "0",[](Address, Address window) 					{ reference_to<NS_window>(window).pressed('0'); } });
	buttons.push_back(new Button{ Point(300,350), 50, 50, "=",[](Address, Address window) 					{ reference_to<NS_window>(window).pressed('='); } });

	
	
	for(Button* b: buttons)
	{
		attach(*b);
	}

	attach(clear_button);
	attach(quit_button);
	
	attach(output);
	attach(input);
	
	result = "0";
	output.put(result);

}
void NS_window::clear()
{
	input_value.clear();
	input.put(input_value);
	
	result = "0";
	output.put(result);
	
	redraw();
}

void NS_window::quit()
{
	hide();
}

void NS_window::pressed(char c)
{
	if(c == '=')
	{
		input_value += c;
		result = Calcu.calc(input_value);
		input_value += result;
	}
	else if(c == 'x')
	{
		if(!input_value.empty())
		{
			input_value.pop_back();
		}
	}
	else
		input_value += c;
	
	input.put(input_value);
	output.put(result);
	
	redraw();
}


