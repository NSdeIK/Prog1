#ifndef CALC_GUARD
#define CALC_GUARD

#include "std_lib_facilities.h"

namespace Calc
{;

class Token {
public:
	char kind; 
	double value; 
	string name; 
	Token(char ch) :kind(ch), value(0) { } 
	Token(char ch, double val) :kind(ch), value(val) { } 
	Token(char ch, string n) : kind(ch), name(n) {} 
};

class Token_stream {  
	bool full; 
	Token buffer; 
	istringstream iss;
	
public:
	Token_stream();
	Token_stream(string s);

	Token get(); 
	void unget(Token t);
	void ignore(char c); 
	
};

constexpr char print = ';';
constexpr char number = '8';

class Calculator
{
public:
	string calc(string input);
private:
	double primary(Token_stream& ts);
	double term(Token_stream& ts);
	double expression(Token_stream& ts);
	double statement(Token_stream& ts);
};

}

#endif
