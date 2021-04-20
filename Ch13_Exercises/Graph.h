#ifndef GRAPH_GUARD
#define GRAPH_GUARD

#include "Point.h"
#include <vector>
#include "fltk.h"
#include "std_lib_facilities.h"

namespace Graph_lib {

#undef major
#undef minor

bool intersect(Point p1, Point p2, Point p3, Point p4);

struct Color {
	enum Color_type {
		red=FL_RED, blue=FL_BLUE, green=FL_GREEN,
		yellow=FL_YELLOW, white=FL_WHITE, black=FL_BLACK,
		magenta=FL_MAGENTA, cyan=FL_CYAN, dark_red=FL_DARK_RED,
		dark_green=FL_DARK_GREEN, dark_yellow=FL_DARK_YELLOW, dark_blue=FL_DARK_BLUE,
		dark_magenta=FL_DARK_MAGENTA, dark_cyan=FL_DARK_CYAN
	};
	enum Transparency { invisible = 0, visible = 255 };

	Color(Color_type cc): c(Fl_Color(cc)), v(visible) {}
	Color(Color_type cc, Transparency vv): c(Fl_Color(cc)), v(vv) {}
	Color(int cc): c(Fl_Color(cc)), v(visible) {}
	Color(Transparency vv): c(Fl_Color()), v(vv) {}

	int as_int() const { return c; }
	char visibility() const { return v; }
	void set_visibility(Transparency vv) { v = vv; }

private:
	unsigned char v;
	Fl_Color c;
};

struct Line_style {
	enum Line_style_type {
		solid=FL_SOLID,				// -------
		dash=FL_DASH,				// - - - -
		dot=FL_DOT,					// ....... 
		dashdot=FL_DASHDOT,			// - . - . 
		dashdotdot=FL_DASHDOTDOT,	// -..-..
	};

	Line_style(Line_style_type ss): s(ss), w(0) { }
	Line_style(Line_style_type ss, int ww): s(ss), w(ww) { }
	Line_style(int ss): s(ss), w(0) { }

	int width() const { return w; }
	int style() const { return s; }
private:
	int s;
	int w;
};

class Font {
public:
	enum Font_type {
		helvetica=FL_HELVETICA,
		helvetica_bold=FL_HELVETICA_BOLD,
		helvetica_italic=FL_HELVETICA_ITALIC,
		helvetica_bold_italic=FL_HELVETICA_BOLD_ITALIC,
		courier=FL_COURIER,
  		courier_bold=FL_COURIER_BOLD,
  		courier_italic=FL_COURIER_ITALIC,
  		courier_bold_italic=FL_COURIER_BOLD_ITALIC,
		times=FL_TIMES,
		times_bold=FL_TIMES_BOLD,
		times_italic=FL_TIMES_ITALIC,
		times_bold_italic=FL_TIMES_BOLD_ITALIC,
		symbol=FL_SYMBOL,
		screen=FL_SCREEN,
		screen_bold=FL_SCREEN_BOLD,
		zapf_dingbats=FL_ZAPF_DINGBATS
	};

	Font(Font_type ff) :f(ff) { }
	Font(int ff) :f(ff) { }

	int as_int() const { return f; }
private:
	int f;
};

struct Fill {
	Fill() :no_fill(true), fcolor(0) { }
	Fill(Color c) :no_fill(false), fcolor(c) { }

	void set_fill_color(Color col) { fcolor = col; }
	Color fill_color() { return fcolor; }
protected:
	bool no_fill;
	Color fcolor;
};

//class Shape
class Shape {
public:
	void draw() const;

	virtual void move(int dx, int dy);

	void set_color(Color col) { lcolor = col; }
	Color color() const { return lcolor; }

	void set_style(Line_style sty) { ls = sty; }
	Line_style style() const { return ls; }

	void set_fill_color(Color col) { fcolor = col; }
	Color fill_color() const { return fcolor; }

	Point point(int i) const { return points[i]; }
	int number_of_points() const { return int(points.size()); }


	virtual ~Shape() { }
	
	//Shape(const Shape&) = delete; 
	//Shape& operator=(const Shape&) = delete;

protected:
	Shape() {}
	Shape(initializer_list<Point> lst) { for (Point p : lst) add(p); }
	void add(Point p) { points.push_back(p); }
	void set_point(int i, Point p) { points[i] = p; }
	virtual void draw_lines() const;

private:
	vector<Point> points;
	Color lcolor {fl_color()};
	Line_style ls {0};
	Color fcolor {Color::invisible};
	
};

template<class T> class Vector_ref {
	vector<T*> v;
	vector<T*> owned;
public:
	Vector_ref(){}
	Vector_ref(T* a, T* b=0, T* c=0, T* d=0)
	{
		if (a) push_back (a);
		if (b) push_back (b);
		if (c) push_back (c);
		if (d) push_back (d);
	}
	~Vector_ref(){ for (int i = 0; i < owned.size(); ++i) delete owned[i]; }

	void push_back(T& s) { v.push_back(&s); }
	void push_back(T* p) { v.push_back(p); owned.push_back(p); }

	T& operator[](int i){ return *v[i]; }
	const T& operator[](int i) const { return *v[i]; }
	int size() { return v.size(); }
};

struct Line : Shape {
	Line (Point p1, Point p2) { add(p1); add(p2); }
};

struct Lines : Shape {
	Lines(){}
	Lines(initializer_list<Point> lst): Shape{lst} 
		{if ( lst.size() % 2 ) error("páratlan számú pontok");}
	void draw_lines() const;
	void add(Point p1, Point p2) { Shape::add(p1); Shape::add(p2); }
};

struct Open_polyline : Shape {
	using Shape::Shape;
	void add(Point p) { Shape::add(p); }
	void draw_lines() const;
};

struct Closed_polyline : Open_polyline {
	using Open_polyline::Open_polyline;
	void draw_lines() const;
};

struct Polygon : Closed_polyline {
	using Closed_polyline::Closed_polyline;
	void add(Point p);
	void draw_lines() const;
};

struct Rectangle : Shape {

	Rectangle(Point xy, int ww, int hh): w{ww}, h{hh}
	{
		if (h<=0 || w<=0) error("Nem jó oldalhossz.");
		add(xy);
	}
	Rectangle(Point x, Point y): w{ y.x - x.x }, h{ y.y - x.y }
	{
		if (h<=0 || w<=0) error("Nem jó pontok.");
		add(x);
	}
	
	void draw_lines() const;

	int height() const { return h; }
	int width() const { return w; }
private:
	int h, w;

};

struct Text : Shape {
private:
	string lab;
	Font fnt { fl_font() };
	int fnt_sz { 14<fl_size() ? fl_size() : 14 };
public:
	Text(Point x, const string& s): lab {s} { add(x); }

	void draw_lines() const;

	void set_label(const string& s) { lab = s; }
	string label() const { return lab; }

	void set_font(Font f) {fnt = f;}
	Font font() const { return Font(fnt); }

	void set_font_size(int sz) { fnt_sz = sz; }
	int font_size() const { return fnt_sz; }
};

struct Circle : Shape
{
private:
	int r;
public:
	Circle(Point p, int rr): r{rr} {
		add(Point{ p.x-r, p.y-r });
	}

	void draw_lines() const;

	Point center() const { return { point(0).x+r, point(0).y+r }; }

	void set_radius(int rr) { r=rr; }
	int radius() const { return r; }
};
struct Ellipse : Shape {
	Ellipse(Point p, int ww, int hh): w(ww), h(hh)
	{
		add(Point(p.x-ww, p.y-hh));
	}
	void draw_lines() const;
private:
	int w, h;
};

struct Arc : Shape
{
	Arc(Point p, int ww, int hh, int sz1, int sz2) : w{ ww }, h{ hh }, szog1{ sz1 }, szog2{ sz2 } 
	{
		add(Point{p.x - ww, p.y - hh });
	}
	
	void draw_lines() const;
	void set_szog(int ertek1, int ertek2);

private:
	int w, h;
	int szog1, szog2;
};

struct Box : Shape
{
	Box(Point p, int ww , int hh, int radius) : w {ww}, h {hh}, r {radius}
	{
	if((ww-(radius*2) < 0) or (hh-(radius*2) <0)) //Azt jelzi, ha radius nagyobb, és kijön a negatív végeredmény--> dobjon errort
	{
		error("Hiba: Nem lehet lekerekíteni - Túl kicsi a magasság/szélesség");
	}
	else
	{
		//Bal felső sarok
		a1 = Point(p.x + r, p.y);
		a2 = Point(p.x, p.y + r);
		
		//Jobb felső sarok
		b1 = Point(p.x + w - r, p.y);
		b2 = Point(p.x + w, p.y + r);
		
		//Jobb alsó sarok
		c1 = Point(p.x + w , p.y + h - r);
		c2 = Point(p.x + w - r, p.y + h);
		
		//Bal alsó sarok
		d1 = Point(p.x + r , p.y + h);
		d2 = Point(p.x, p.y + h - r);
	}

}

	void draw_lines() const;	
private:
	Point p;
	Point a1,a2,b1,b2,c1,c2,d1,d2;
	Point a3,b3,c3,d3;
	int w, h, r;
};

struct Nyil : Shape
{
	Nyil(Point kezdo, Point vege, int meret) : nyilhegy_meret(meret)
	{
		add(kezdo);
		add(vege);
	} 
	
	void draw_lines() const;

private:
	int nyilhegy_meret;
};

struct SzovegBox : Text
{
	SzovegBox(Point p, string szoveg, int rsarok) : Text(Point(p.x + 15, p.y + 20), szoveg), box(p, szoveg.size() * font_size(), font_size() + 15, rsarok) {}
	//x,y pont --> szöveg --> mekkora legyen box_radiusa
	//Eltoljuk 15px x 20px --> Dobox (xy koord., szöveg hosszúság * betűmérettel, font_size + 15 méret, radius)
	
	void szinvaltas(Color szin, Color kitoltes, Color szovegszin);
	void draw_lines() const;
	
	Box box;
	
private:
	string szoveg;	
};

struct Marked_polyline : Open_polyline
{
	Marked_polyline(const string& m): mark(m) { }
	void draw_lines() const;
private:
	string mark;
};

struct Marks : Marked_polyline
{
	Marks(const string& m) : Marked_polyline(m) 
	{ set_color(Color(Color::invisible)); }

};

struct Mark : Marks
{
	Mark(Point xy, char c) : Marks(string(1,c)) { add(xy); }
};

struct Bad_image : Fl_Image {
	Bad_image(int h, int w) : Fl_Image(h,w,0) { }
	void draw(int x, int y, int, int, int, int) { draw_empty(x,y); }
};

struct Suffix {
	enum Encoding { none, jpg, gif, bmp };
};

Suffix::Encoding get_encoding(const string& s);

struct Image : Shape {
private:
	int w, h, cx, cy;
	Fl_Image* p;
	Text fn;
public:
	Image(Point xy, string s, Suffix::Encoding e = Suffix::none);
	~Image() { delete p; }
	void draw_lines() const;
	void set_mask(Point xy, int ww, int hh) { w = ww; h = hh; cx=xy.x; cy=xy.y; }
	void move(int dx, int dy) { Shape::move(dx,dy); p->draw(point(0).x,point(0).y); }
};

typedef double Fct(double);

struct Function : Shape {
	Function(Fct f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25);
};

struct Axis : Shape {
	enum Orientation { x, y, z };
	Axis (Orientation d, Point xy, int length, int number_of_notches = 0, string label = "");
	void draw_lines() const;
	void move(int dx, int dy);
	void set_color(Color c);

	Text label;
	Lines notches;
};

}
#endif
