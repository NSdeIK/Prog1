
#include "calculator.h"

namespace Calc
{;

Token_stream::Token_stream() : full(false), buffer(0) { }
Token_stream::Token_stream(string s) : full(false), buffer(0), iss(s) { }

Token Token_stream::get()
{
	if (full) { full = false; return buffer; } 
	
	if(iss.eof()) return print;  
	char ch;
	iss.get(ch); 
	
	while(isspace(ch)) 
	{
	iss.get(ch); 
	if (iss.eof()) return print;
	}
	

	switch (ch) { 
	case '(':     
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
	case ',':
		return Token(ch);
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	
		iss.unget();
		double val;
		iss >> val; 
		return Token(number, val);
	}

	default: 
		if (isalpha(ch)) 
		{               
			string s;    
			s += ch;

			while (iss.get(ch) && !iss.eof() && (isalpha(ch) || isdigit(ch))) s+= ch;
			if(!iss.eof()) iss.unget();
		}
		error("Bad token");
		
	}
	return 0;
}

void Token_stream::unget(Token t)
{
	if(full) error ("unget() full buffer");
	buffer = t;
	full = true;
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (iss >> ch)
		if (ch == c) return;
}

double Calculator::primary(Token_stream& ts) 
{ 
	Token t = ts.get();
	switch (t.kind) 
	{
		case '(':
		{	
			double d = expression(ts);
			t = ts.get();
			if (t.kind != ')') error("'(' expected");
			return d; 
		}
	case '-':
		return - primary(ts);
	case number:
		return t.value;
	default:
		error("primary expected");
		return 0;
	}
}

double Calculator::term(Token_stream& ts) 
{
	double left = primary(ts);
	while (true) {
		Token t = ts.get();
		switch (t.kind) 
		{
		case '*':              
			left *= primary(ts);
			break;
		case '/':
		{	
			double d = primary(ts);
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		case '%': 
		{
			double d = primary(ts);           
			if (d == 0) error ("%: divide by zero");
			left = fmod(left, d);
			t = ts.get();
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double Calculator::expression(Token_stream& ts) 
{
	double left = term(ts);
	while (true) {
		Token t = ts.get();
		switch (t.kind) {        
		case '+':
			left += term(ts);
			break;
		case '-':
			left -= term(ts);
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double Calculator::statement(Token_stream& ts) 
{
	Token t = ts.get();
	switch (t.kind) {
	default:
		ts.unget(t);
		return expression(ts);
	}
}


string Calculator::calc(string input)
{
	Token_stream ts(input);
	ostringstream ofs;

	try 
	{ 

		ofs << statement(ts);
		return ofs.str();	

	}
	catch (exception& e) 
	{
		ofs << e.what();
		return ofs.str();
	}	
}

}
