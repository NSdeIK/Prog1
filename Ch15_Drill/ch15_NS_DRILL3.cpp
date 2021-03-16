#include "std_lib_facilities.h"

int hu( char c )
{
  return (unsigned char)c;
}

struct Person
{
public:
	Person() {}
	//Person(string n, int k) { init(n, k); }
	Person(string vez, string ker, int k) { init(vez,ker,k); }
	
	//void init(string n, int k)
	void init(string vez, string ker, int k)
	{
		//checkNev(n);
		checkNev(vez,ker);
		checkKor(k);
	
		//nev = n;
		vezeteknev = vez;
		keresztnev = ker;
		kor = k;	
	}
	
	//string nevlekeres() const { return nev; }
	string vezeteknev_lekeres() const { return vezeteknev; }
	string keresztnev_lekeres() const { return keresztnev; }
	int korlekeres() const { return kor; }
private:
	void checkKor(int k);
	//void checkNev(string n);
	void checkNev(string vez, string ker);
	
	//string nev;
	string vezeteknev, keresztnev;
	int kor;
	
};

void Person::checkKor(int k)
{
		if(k < 0 || k > 150) 
			error("Érvénytelen kor - Kor range [0-150] között lehet");
		else if(cin.fail())
			error("Hiba történt! - Ez nem létező szám/számok");
		else
			;
}

//void Person::checkNev(string n)
void Person::checkNev(string vez, string ker)
{
	vector<string> ekezetek{ "á", "é" , "í", "ó", "ő", "ú", "ű"};
	vector<char> specialis{ '$', ';', '"', '\'', '[', ']', '#', '%', '^', '@', '!', '&', '<', '>'};
	for(auto s : specialis)
	{
		for(auto e : ekezetek)
		{
			if(vez.find(e) != string::npos || ker.find(e) != string::npos) ; //string::npos --> állandó érték, size_t utolsó eleme, jelzik, hogyha nincs egyezések
			else if(vez.find(s) != string::npos || ker.find(s) != string::npos)
				error( "Speciális karaktereket tartalmaz...");
			else ;
		}
	}

	return;
}

//Kiiratás ostream
ostream& operator<<(ostream& o, const Person& p)
{
	o << endl <<  p.vezeteknev_lekeres() << " " << p.keresztnev_lekeres() << " : " << p.korlekeres() << endl;
	return o;
}

//Beolvasás istream
istream& operator>>(istream& i, Person& p)
{
	//string n;
	string vez, ker;
	int k;
	//cout << "Neve:"; i> n;
	cout << endl <<"Vezetékneve: "; i>> vez;
	cout << "Keresztneve: "; i>> ker;
	cout << "Kor: "; i>> k; 
	
	p.init(vez, ker, k);
	
	
	return i;
}

int main()
try{
setlocale(LC_ALL, "");
/*Person szemely{"Goofy",63};
cout << szemely << endl;

Person szemely2;
cin >> szemely2;
cout << szemely2 << endl;*/

//8.as feladat

vector<Person> szemelyek;
Person ujszemely;
for(int i =0; i < 3; ++i)
{
	cin >> ujszemely;
	szemelyek.push_back(ujszemely);

}

for(auto& lista : szemelyek)
{
	cout << lista;
}

	
return 0;


}catch(exception& e)
{
	cerr << "Hiba - (1): " << e.what() << endl; 
	return 1;
}catch(...)
{
	cerr << "Hiba - (2)\n";
	return 2;
}
