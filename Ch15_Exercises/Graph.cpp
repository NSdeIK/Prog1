#include "Graph.h"
#include <map>

namespace Graph_lib {

inline pair<double,double> line_intersect(Point p1, Point p2, Point p3, Point p4, bool& parallel) 
{
    double x1 = p1.x;
    double x2 = p2.x;
	double x3 = p3.x;
	double x4 = p4.x;
	double y1 = p1.y;
	double y2 = p2.y;
	double y3 = p3.y;
	double y4 = p4.y;

	double denom = ((y4 - y3)*(x2-x1) - (x4-x3)*(y2-y1));
	if (denom == 0){
		parallel= true;
		return pair<double,double>(0,0);
	}
	parallel = false;
	return pair<double,double>( ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3))/denom,
								((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3))/denom);
}

bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection){
   bool parallel;
   pair<double,double> u = line_intersect(p1,p2,p3,p4,parallel);
   if (parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1) return false;
   intersection.x = p1.x + u.first*(p2.x - p1.x);
   intersection.y = p1.y + u.first*(p2.y - p1.y);
   return true;
} 

//class Shape's functions
void Shape::draw_lines() const
{
	if (color().visibility() && 1<points.size())
		for(int i = 1; i < points.size(); ++i)
			fl_line(points[i-1].x, points[i-1].y, points[i].x, points[i].y);
}

void Shape::move(int dx, int dy)
{
	for(int i = 0; i < points.size(); ++i){
		points[i].x += dx;
		points[i].y += dy;
	}
}

void Shape::draw() const
{
	Fl_Color oldc = fl_color();
	fl_color(lcolor.as_int());
	fl_line_style(ls.style(), ls.width());
	draw_lines();
	fl_color(oldc);
	fl_line_style(0);
}

void Lines::draw_lines() const
{
	if (color().visibility())
		for (int i = 1; i < number_of_points(); i+=2)
			fl_line(point(i-1).x, point(i-1).y, point(i).x, point(i).y);
}

void Open_polyline::draw_lines() const
{
		if (fill_color().visibility()) {
			fl_color(fill_color().as_int());
			fl_begin_complex_polygon();
			for(int i=0; i<number_of_points(); ++i){
				fl_vertex(point(i).x, point(i).y);
			}
			fl_end_complex_polygon();
			fl_color(color().as_int());
		}
		
		if (color().visibility())
			Shape::draw_lines();
}

void Closed_polyline::draw_lines() const
{
	Open_polyline::draw_lines();

	if (color().visibility())
		fl_line(point(number_of_points()-1).x, point(number_of_points()-1).y, point(0).x, point(0).y);
}

void Polygon::add(Point p)
{
	int np = number_of_points();

	if (1<np) {
		if (p==point(np-1)) error("Ugyanaz mint az előző pont");
		bool parallel;
		line_intersect(point(np-1),p,point(np-2),point(np-1),parallel);
		if (parallel)
			error("két poligon pont ugyanazon a vonalon");
	}

	for (int i = 1; i<np-1; ++i) {
		Point ignore(0,0);
		if (line_segment_intersect(point(np-1),p,point(i-1),point(i),ignore))
			error("kereszteződés");
	}
	

	Closed_polyline::add(p);
}


void Polygon::draw_lines() const
{
		if (number_of_points() < 3) error("kevesebb mint 3 pont");
		Closed_polyline::draw_lines();
}

void Rectangle::draw_lines() const
{
	if (fill_color().visibility()){
		fl_color(fill_color().as_int());
		fl_rectf(point(0).x, point(0).y, w, h);
		fl_color(color().as_int());
	}

	if (color().visibility()){
		fl_color(color().as_int());
		fl_rect(point(0).x, point(0).y, w, h);
	}
}

void Text::draw_lines() const
{
	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(fnt.as_int(), fnt_sz);
	fl_draw(lab.c_str(), point(0).x, point(0).y);
	fl_font(ofnt, osz);
}

void Circle::draw_lines() const
{
	if (fill_color().visibility()){
		fl_color(fill_color().as_int());
		fl_pie(point(0).x, point(0).y, r+r-1, r+r-1, 0, 360);
		fl_color(color().as_int());
	}

	if (color().visibility()){
		fl_color(color().as_int());
		fl_arc(point(0).x, point(0).y, r+r, r+r, 0, 360);
	}
}

void Ellipse::draw_lines() const
{
	if (fill_color().visibility()){
		fl_color(fill_color().as_int());
		fl_pie(point(0).x, point(0).y, w+w-1, h+h-1, 0,  360); 
		fl_color(color().as_int());
	}

	if (color().visibility()){
		fl_color(color().as_int());
		fl_arc(point(0).x, point(0).y, w+w, h+h, 0, 360);
	}
}

void Arc::draw_lines() const // CH13_Exercises#1
{
	if(fill_color().visibility())
	{
		fl_color(fill_color().as_int()); 
		fl_pie(point(0).x, point(0).y, w, h, szog1, szog2);//Paraméter
		fl_color(color().as_int()); //Alapértelmezett
	}
	
	if (color().visibility()){
		fl_color(color().as_int());
		fl_arc(point(0).x, point(0).y, w, h, szog1, szog2);
	}
}
void Arc::set_szog(int ertek1, int ertek2)
{
	szog1 = ertek1;
	szog2 = ertek2;
	Arc::draw_lines();
}


void Box::draw_lines() const
{
	if(fill_color().visibility())
	{
		fl_color(fill_color().as_int());
			
		fl_pie(a1.x -r, a2.y-r, r+r, r+r, 90, 180);
		fl_pie(b2.x-(2*r), b2.y-r, r+r, r+r, 0, 90);
		fl_pie(c2.x - r,c2.y - (2*r), r+r, r+r, 270, 360);
		fl_pie(d2.x,d2.y -r , r+r, r+r, 180, 270);
		
		fl_rectf(a1.x, a1.y, w-(2*r), h);
		fl_rectf(a1.x - r, a2.y, r, h-(2*r));	
		fl_rectf(b1.x, b2.y, r, h-(2*r));		
		fl_color(color().as_int());
	}
	if(color().visibility())
	{
		fl_line(a1.x,a1.y,b1.x,b1.y);
		fl_line(b2.x,b2.y,c1.x,c1.y);
		fl_line(c2.x,c2.y,d1.x,d1.y);
		fl_line(d2.x,d2.y,a2.x,a2.y);
		
		fl_arc(a2.x,a2.y-r, r+r, r+r, 90, 180);
		fl_arc(b2.x-(2*r), b2.y-r, r+r, r+r, 0, 90);
		fl_arc(c2.x - r,c2.y - (2*r), r+r, r+r, 270, 360);
		fl_arc(d2.x,d2.y -r , r+r, r+r, 180, 270);
	}
}

void Nyil::draw_lines() const
{
		double fej = nyilhegy_meret / 2; 
		Point kezdopont(point(0).x, point(0).y);
		Point vegpont(point(1).x, point(1).y);
		
		//Tavolsag
		double tavolsag = sqrt(pow((vegpont.x - kezdopont.x), 2) + pow((vegpont.y - kezdopont.y), 2));
		//double tavolsag = (vegpont.x - kezdopont.x) + (vegpont.y - kezdopont.y);
		//double tavolsag = abs((vegpont.x - kezdopont.x) + (vegpont.y - kezdopont.y));
		//std::cout << "Kezdőpont([x-y]: ["<< kezdopont.x << " - "<< kezdopont.y << " Végpont[x-y]: [" << vegpont.x << "-" << vegpont.y <<"] Távolság: "<< tavolsag << endl;

		//Nyilfej
		Point p3(fej / tavolsag * kezdopont.x + (1 - fej / tavolsag) * vegpont.x,
			 fej / tavolsag * kezdopont.y + (1 - fej / tavolsag) * vegpont.y );
		//std::cout << "Nyilfej x:" << (fej / tavolsag * kezdopont.x + (1 - fej / tavolsag) * vegpont.x) << " - y:" << (fej / tavolsag * kezdopont.y + (1 - fej / tavolsag) * vegpont.y ) << endl;
	
		//Baloldali oldal
		 double bx = p3.x + ((fej * (vegpont.y - kezdopont.y)) / tavolsag);
		 double by = p3.y + ((fej * (kezdopont.x - vegpont.x)) / tavolsag);
		// std::cout << "bx: " << bx << " by: " << by << endl;
		 
		 //Jobboldali oldal
		 double jx = p3.x + ((fej * (kezdopont.y - vegpont.y)) / tavolsag);
		 double jy = p3.y + ((fej * (vegpont.x - kezdopont.x)) / tavolsag);
		 //std::cout << "jx: " << jx << " jy: " << jy << endl;
		
		if(fill_color().visibility())
		{
			fl_color(fill_color().as_int());
				fl_begin_complex_polygon();
					fl_vertex(vegpont.x, vegpont.y);
					fl_vertex(bx, by);
					fl_vertex(jx, jy);
				fl_end_complex_polygon();
			fl_color(color().as_int());
		}
		
		if (color().visibility())
		{
			//lines
			
			fl_line(kezdopont.x, kezdopont.y, p3.x, p3.y);
			fl_line(bx, by, jx, jy);
			fl_line(vegpont.x, vegpont.y, jx, jy);
			fl_line(bx, by, vegpont.x, vegpont.y);
		}
		
		
}

void SzovegBox::draw_lines() const
{
	box.draw_lines();
	Text::draw_lines();
}
void SzovegBox::szinvaltas(Color szin, Color kitoltes, Color szovegszin)
{
	box.set_color(szin);
	box.set_fill_color(kitoltes);
	set_color(szovegszin);
}
void Smiley::draw_lines() const
{
	Circle::draw_lines();
	int kozep = radius()/2;
	
	if(fill_color().visibility())
	{
		//Szem méret
		int szem = (radius() / 10) * 3;
		
		fl_color(Color::black);
		fl_pie(point(0).x+kozep,point(0).y+kozep, szem, szem, 0, 360); //egyik szeme
		fl_pie(point(0).x+kozep+radius()-szem,point(0).y+kozep, szem, szem, 0, 360);
		fl_color(color().as_int());	// reset color
	}
	
	if(color().visibility())
	{
		int mosoly = radius();
		fl_color(Color::black);
		fl_arc(point(0).x + kozep, point(0).y + kozep, mosoly, mosoly, 180, 360);
	
	}
}

void Frowny::draw_lines() const
{
	Circle::draw_lines();
	int kozep = radius()/2;
	
	if(fill_color().visibility())
	{
		//Szem méret
		int szem = (radius() / 10) * 3;
		
		fl_color(Color::black);
		fl_pie(point(0).x+kozep,point(0).y+kozep, szem, szem, 0, 360); //egyik szeme
		fl_pie(point(0).x+kozep+radius()-szem,point(0).y+kozep, szem, szem, 0, 360);
		fl_color(color().as_int());	// reset color
	}
	
	if(color().visibility())
	{
		int szomoru = radius();
		fl_color(Color::black);
		fl_arc(point(0).x + kozep, point(0).y + radius(), szomoru, szomoru, 0, 180);
	
	}
}


void draw_mark(Point x, char c){
	
	static const int dx = 4;
	static const int dy = 4;
	string m(1,c);
	fl_draw(m.c_str(), x.x-dx,x.y-dy);

}

void Marked_polyline::draw_lines() const
{
	Open_polyline::draw_lines();
	for( int i = 0; i < number_of_points(); ++i)
		draw_mark(point(i), mark[i%mark.size()]);
}

std::map<string,Suffix::Encoding> suffix_map;

int init_suffix_map()
{
	suffix_map["jpg"] = Suffix::jpg;
	suffix_map["JPG"] = Suffix::jpg;
	suffix_map["jpeg"] = Suffix::jpg;
	suffix_map["JPEG"] = Suffix::jpg;
	suffix_map["gif"] = Suffix::gif;
	suffix_map["GIF"] = Suffix::gif;
	suffix_map["bmp"] = Suffix::bmp;
	suffix_map["BMP"] = Suffix::bmp;
	suffix_map["PNG"] = Suffix::png;
	suffix_map["png"] = Suffix::png;
	return 0;
}

Suffix::Encoding get_encoding(const string& s)
{
	static int x = init_suffix_map();

	string::const_iterator p = find(s.begin(),s.end(),'.');
	if (p==s.end()) return Suffix::none;

	string suf(p+1,s.end());
	return suffix_map[suf];
}

bool can_open(const string& s){
	ifstream ff(s.c_str());
	return ff.is_open();
}

Image::Image(Point xy, string s, Suffix::Encoding e)
	:w(0), h(0), fn(xy,"")
{
	add(xy);

	if (!can_open(s)){
		fn.set_label("Nem nyithato a file!");
		p = new Bad_image(30,20);
		return;
	}

	if (e == Suffix::none) e = get_encoding(s);

	switch(e){
		case Suffix::jpg:
		p = new Fl_JPEG_Image(s.c_str());
		break;
		case Suffix::gif:
		p = new Fl_GIF_Image(s.c_str());
		break;
		case Suffix::png:
		p = new Fl_PNG_Image(s.c_str());
		break;
		default:
		fn.set_label("Nem tamogatott formatum!");
		p = new Bad_image(30,20);
	}
}

void Image::draw_lines() const
{
	if (fn.label() != "") fn.draw_lines();

	if (w && h){
		p->draw(point(0).x, point(0).y, w, h, cx, cy);
	}
	else {
		p->draw(point(0).x, point(0).y);
	}
}

Function::Function(Fct f, double r1, double r2, Point xy, int count, double xscale, double yscale){
	if (r2-r1<=0) error ("Rossz range!");
	if (count<=0) error ("Rossz count!");
	double dist = (r2-r1)/count;
	double r = r1;
	for (int i = 0; i < count; ++i){
		add(Point(xy.x+int(r*xscale), xy.y-int(f(r)*yscale)));
		r += dist;
	}
}

Exercises_function::Exercises_function(Fct f, double r1, double r2, Point xy, int count, double xscale, double yscale, double precision) : Function(f,r1,r2,xy,count,xscale,yscale), fct(f), min(r1),max(r2), origin(xy), c(count), xsk(xscale), ysk(yscale), prec(precision)
{
	reset();
}

void Exercises_function::reset()
{
	double tavolsag = (max-min)/c;
	double r = min;
	pontok_torlese();
	for (int i = 0; i < c; ++i)
	{
		add(Point(origin.x+int(int(r*xsk)/prec)*prec, origin.y-(int(int(fct(r)*ysk)/prec)*prec)));
		r += tavolsag;
	}
}

void Exercises_function::reset_range(double r1, double r2)
{
	if(r2<=r1) error("Rossz...");
	min = r1;
	max = r2;
	reset();
}

void Exercises_function::reset_count(int count)
{
	if(count<=0) error("Rossz...");
	c = count;
	reset();
}
void Exercises_function::reset_xskala(double xskala)
{
	if(xskala==0) error("Rossz...");
	xsk = xskala;
	reset();
}
void Exercises_function::reset_yskala(double yskala)
{
	if(yskala==0) error("Rossz...");
	ysk = yskala;
	reset();
}

Axis::Axis(Orientation d, Point xy, int length, int n, string lab )
	:label(Point(0,0), lab)
{
	if (length < 0) error ("Rossz tengely méret.");
	switch (d){
		case Axis::x:
		{
			Shape::add(xy);
			Shape::add(Point(xy.x+length, xy.y));
			if (1<n){
				int dist = length/n;
				int x = xy.x+dist;
				for (int i = 0; i < n; ++i){
					notches.add(Point(x, xy.y), Point(x, xy.y-5));
					x += dist;
				}
			}
			label.move(length/3, xy.y+20);
			break;
		}
		case Axis::y:
		{
			Shape::add(xy);
			Shape::add(Point(xy.x, xy.y-length));
			if (1<n){
				int dist = length/n;
				int y = xy.y-dist;
				for (int i = 0; i < n; ++i){
					notches.add(Point(xy.x, y), Point(xy.x+5, y));
					y -= dist;
				}
			}
			label.move(xy.x-10, xy.y-length-10);
			break;
		}
		case Axis::z:
			error("Nincs z!");
	}
}

void Axis::draw_lines() const
{
	Shape::draw_lines();
	notches.draw();
	label.draw();
}

void Axis::set_color(Color c)
{
	Shape::set_color(c);
	notches.set_color(c);
	label.set_color(c);
}

void Axis::move(int dx, int dy)
{
	Shape::move(dx, dy);
	notches.move(dx, dy);
	label.move(dx, dy);
}


Binaris_fa::Binaris_fa(Point xy, int szint, string el_tipus) : szintek(szint)
{
	if(szint<0) 
	{
		error("Binaris_fa: Negatív szám nem lehet/Nullánál kisebb szint");
	}
	if(szint==0) 
	{
		return; //Üres fa
	}
	add(xy); //Ha szint==1, akkor lesz egy főgyökér
	
	int xtav = 25; //Mekkora távolság legyen egymásttól
	int ytav = 50; //Mekkora magasság legyen egymásttól
	int x,y;
	
	for(int i=2; i<=szint; ++i) //...
		for(int j=0; j<pow(2,i-1); ++j)
		{
		x = xy.x - ((pow(2,i-1)-1)/2-j) * pow(2, szint-i) * xtav;
		y = xy.y + (i-1) * ytav;
		add(Point(x,y));
		}
	
	for(int i=0; i<number_of_points()/2; ++i)
	{
		if(el_tipus== "egyenes")
		{
		elek.push_back(new Line(point(i),point(2*i+1))); //Bal oldal
		elek.push_back(new Line(point(i),point(2*i+2))); //Jobb oldal
		}
		if(el_tipus == "nyil")
		{
		elek.push_back(new Nyil(point(i),Point(point(2*i+1).x,point(2*i+1).y-10),10));
		elek.push_back(new Nyil(point(i),Point(point(2*i+2).x,point(2*i+2).y-10),10));  //Bugos O:)

		
		}
		
		for(int i =0; i<number_of_points(); ++i)
		{
			cimkek_v.push_back(new Text(Point(point(i).x+13, point(i).y-13),""));
		}
	}
	
}
void Binaris_fa::draw_lines() const
{
	const int r = 10;
	if(color().visibility())
	{
		for(int i = 0; i < elek.size(); ++i)
		{
			elek[i].draw();
			
		}
	
		for(int i =0; i < number_of_points(); ++i)
		{
			cimkek_v[i].draw();
		}
		for (int i = 0; i < number_of_points(); ++i) //Kör kirajzolása
		{ 
		
			Circle c({point(i).x, point(i).y}, r);
			c.draw();	
		}
		fl_color(color().as_int());
	}
	if (fill_color().visibility())
	{
		fl_color(fill_color().as_int());
		for (int i = 0; i < number_of_points(); i++) //Kör kirajzolása
		{ 
			fl_pie(point(i).x-r, point(i).y-r,r+r, r+r, 0, 360);
		}
		fl_color(color().as_int());
	}
}

void Binaris_fa_kocka::draw_lines() const
{
	const int k = 10;
	if(color().visibility())
	{
		for(int i = 0; i < elek.size(); ++i)
		{
			elek[i].draw();
		}
	
		for (int i = 0; i < number_of_points(); i++) //Kocka rajzolása
		{ 
			fl_rectf(point(i).x-k, point(i).y-k, k+k, k+k);
		}
		fl_color(color().as_int());
	}
	if (fill_color().visibility())
	{
		fl_color(fill_color().as_int());
		for (int i = 0; i < number_of_points(); i++) //Kör kirajzolása
		{ 
			fl_rectf(point(i).x-k, point(i).y-k, k+k, k+k);
		}
		fl_color(color().as_int());
	}
}

void Binaris_fa_haromszog::draw_lines() const
{
	const int h = 10;
	if(color().visibility())
	{
		for(int i = 0; i < elek.size(); ++i)
		{
			elek[i].draw();
		}
		for(int i =0; i < number_of_points(); ++i)
		{
			cimkek_v[i].draw();
		}
	
		for (int i = 0; i < number_of_points(); i++) //Háromszög
		{ 
			Haromszog haromszog({point(i).x-h,point(i).y+h}, {point(i).x+h, point(i).y+h}, {point(i).x,point(i).y-h});
			haromszog.draw();
		}
		fl_color(color().as_int());
	}
	
	if (fill_color().visibility())
	{
		fl_color(fill_color().as_int());
					
		for (int i = 0; i < number_of_points(); i++) //Háromszög
		{ 
			fl_begin_complex_polygon();
			fl_vertex(point(i).x-h,point(i).y+h);
			fl_vertex(point(i).x,point(i).y-h);
			fl_vertex(point(i).x+h, point(i).y+h);
			fl_end_complex_polygon();
		}
		
		fl_color(color().as_int());
	}
}

void Binaris_fa::cimkek(string cimke1, string cimke2)
{
	istringstream iss(cimke1);
	char ch;
	iss.get(ch);
	if(cimke1.size()==1)
	{
	switch (ch)
	{
	case 'b':
	case 'j':
		cimkek_v[0].set_label(cimke2);
		return;
	}
	}
	int node_x = 0;
	while (iss.get(ch))
	{
		switch(ch)
		{
		case 'b':
			node_x = 2*node_x+1;
			break;
		case 'j':
			node_x = 2*node_x+2;
			break;
		}
	}
	cimkek_v[node_x].set_label(cimke2);
}


} //end Graph
