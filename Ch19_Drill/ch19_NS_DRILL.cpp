#include "std_lib_facilities.h"

template<typename T>

struct S
{
	S() : val(T()) {} //Alapértelmezett 
	S(T d) : val(d) {} //2.Drill hozzáadva (konstruktor)

	//Operátorok
	istream operator>>(T d) { return cin >> val; } //4. Drill - beolvasás
	S& operator=(const T& ujval) { val = ujval; return *this;} //10. Drill

	//Függvények
	const T& get() const { return val;} //5.Drill - Const get
	T& get() { return val;} //11.Drill - Non-const get

	void set(T d) { val = d; } //9.Drill set függvény hozzáadva

	//T val; -- eltávolítva, átkerül privátba

private:
	T val;
};

template<typename T> 
const T& get(S<T>& s) //6.Drill Classon kívüli get ...
{
	//return s.val; //Privát miatt eltávolítva
	return s.get();
}

template<typename T>
void read_val(T& v) //12.Drill 
{
	cin >> v;
}

//Bónusz - 14 Drill
template<typename T>
istream& operator>>(istream& is, vector<T>& lista) // {val, val, val}
{
	T seged;
	string s; //Mivel {} és , miatt...
	while(is >> s)
	{
		if(s == "}") //Ha végére van '}' 
			break; //Legyen vége a while ciklusnak

		if(s != "{" && s != " " && s != ",") //Ami nem {, ' ', ',' karakter
		{
			stringstream ss;
			ss << s;
			ss >> seged;
			lista.push_back(seged);
		}
	}
	return is;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T>& lista)
{
	os << "{ ";
	for (int i = 0; i < lista.size()-1; ++i)
	{
		os << lista[i] << ", ";
	}
	os << lista[lista.size()-1] << " }" << endl;
	return os;
}

/*void Drill1()
{
	S<double> Sd;
	S<string> Ss;
	Sd.val = 99.99;
	Ss.val = "%";
	cout << Sd.val << Ss.val << endl;
}*/

/*void Drill3()
{
	S<int> Si(5); 
	S<char> Sc('p'); 
	cout << Si.val << " " << Sc.val << endl;

	S<double> Sd(99.99);
	S<string> Ss("%");
	cout << Sd.val << Ss.val << endl;

	S<vector<int>> Svi(vector<int>(1,10));
	for (int i : Svi.val)
	{
		cout << i << " " ;
	}
	cout << endl;
}*/

/*void Drill4()
{
	S<int> Si;
	cout << "Írj egy int számot: ";
	cin >> Si.val;
	cout << Si.val << endl;

	S<double> Sd;
	cout << "Írj egy doublet: ";
	cin >> Sd.val;
	cout << Sd.val << endl;

	S<char> Sc;
	cout << "Írj egy chart: ";
	cin >> Sc.val;
	cout << Sc.val << endl;

	S<string> Ss;
	cout << "Írj egy stringet: ";
	cin >> Ss.val;
	cout << Ss.val << endl;
}*/

/*void Drill5()
{
	S<int> Si;
	cout << "Írj egy int számot: ";
	cin >> Si.val;
	cout << Si.get() << endl;
}*/

/*void Drill6()
{
	S<int> Si;
	cout << "Írj egy int számot: ";
	cin >> Si.pval;
	cout << get(Si) << endl;
}*/

void Drill7()
{
	S<int> Si(100);
	cout << get(Si) << endl;
	//-----------------------
	S<char> Sc('H');
	cout << get(Sc) << endl;
	//-----------------------
	S<string> Ss("oppá!");
	cout << get(Ss) << endl;
	//-----------------------
	S<double> Sd(1.999);
	cout << get(Sd) << endl;
	//-----------------------
	S<vector<int>> Svi (vector<int>(3, 0));
	for (int i : Svi.get())
	{
		cout << i << " ";
	}
	cout << endl;
}

void Drill9()
{
	S<int> Si(100);
	cout << get(Si) << endl;
	Si.set(500);
	cout << get(Si) << endl;
	//-----------------------
	S<char> Sc('H');
	cout << get(Sc) << endl;
	Sc.set('S');
	cout << get(Sc) << endl;
	//-----------------------
	S<string> Ss("oppá!");
	cout << get(Ss) << endl;
	Ss.set("zuper!");
	cout << get(Ss) << endl;
	//-----------------------
	S<double> Sd(1.999);
	cout << get(Sd) << endl;
	Sd.set(2.999);
	cout << get(Sd) << endl;
	//-----------------------
	S<vector<int>> Svi (vector<int>(3, 0));
	for (int i : Svi.get())
	{
		cout << i << " ";
	}
	cout << endl;

	Svi.set(vector<int>(3, 9));
	for (int i : Svi.get())
	{
		cout << i << " ";
	}
	cout << endl;


}

void Drill10() //Pl. non const példa
{
	S<int> Si(100);
	cout << get(Si) << endl;
	Si = 500;
	cout << get(Si) << endl;

	S<char> Sc('H');
	cout << get(Sc) << endl;
	Sc = 'S';
	cout << get(Sc) << endl;

	S<string> Ss("oppá!");
	cout << get(Ss) << endl;
	Ss = "zuper!";
	cout << get(Ss) << endl;

	S<double> Sd(1.999);
	cout << get(Sd) << endl;
	Sd = 2.999;
	cout << get(Sd) << endl;

	S<vector<int>> Svi (vector<int>(3, 0));
	for (int i : Svi.get())
	{
		cout << i << " ";
	}
	cout << endl;

	Svi = vector<int>(3, 9);
	for (int i : Svi.get())
	{
		cout << i << " ";
	}
	cout << endl;
}

void Drill11() //Pl. const példa
{
	const S<int> Si(500);
	cout << Si.get() << endl;

	const S<char> Sc('H');
	cout << Sc.get() << endl;

	const S<string> Ss("oppá!");
	cout << Ss.get() << endl;

	const S<double> Sd(1.999);
	cout << Sd.get() << endl;
}

void Drill12_13()
{
	S<int> Si;
	cout << "Írj egy int számot: "; 
	read_val(Si.get());
	cout << endl << Si.get() << endl << endl;

	S<double> Sd;
	cout << "Írj egy double számot: "; 
	read_val(Sd.get());
	cout << endl << Sd.get() << endl << endl;
	S<char> Sc;
	cout << "Írj egy chart: "; 
	read_val(Sc.get());
	cout << endl << Sc.get() << endl << endl;
	S<string> Ss;
	cout << "Írj egy szöveget: "; 
	read_val(Ss.get());
	cout << endl << Ss.get() << endl << endl;

	S<vector<int>> Svi (vector<int>(3, 0));
	cout << "Írj 3 db int számot: ";
	for (int i = 0; i < 3; ++i)
	{
		read_val(Svi.get()[i]);
	}
	cout << endl;
	for (int i : Svi.get())
	{
			cout << i << " ";
	}
	cout << endl;

}

void Drill14()
{
	
	S<vector<int>> Svi;
	cout << "Írj int számokat ebben a formátumban { érték, érték, érték } : " ;
	cin >> Svi.get();
	cout << Svi.get();

	S<vector<char>> Svc;
	cout << "Írj char-okat ebben a formátumban { érték, érték, érték } : " ;
	cin >> Svc.get();
	cout << Svc.get();

	S<vector<double>> Svd;
	cout << "Írj double számokat ebben a formátumban { érték, érték, érték } : " ;
	cin >> Svd.get();
	cout << Svd.get();

	S<vector<string>> Svs;
	cout << "Írj string-eket ebben a formátumban { érték, érték, érték } : " ;
	cin >> Svs.get();
	cout << Svs.get();

}



int main()
{
	//Drill1(); //Template teszt
	//Drill3(); //Változók definiálása
	//Drill4(); //Érték beolvasása, és kiiratása
	//Drill5(); //Get structon belül
	//Drill6(); //Get függvény osztályon kívül tesztelése
	//Drill7(); //Privát val tesztelése
	//Drill9(); //Set függvény
	//Drill10(); //Non Const teszt
	//Drill11(); //Const teszt
	//Drill12_13(); //Read_val listával
	Drill14(); //Bónusz - Nem tökéletes még. 

	return 0;
}