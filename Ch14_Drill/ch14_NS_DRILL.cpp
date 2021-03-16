#include "std_lib_facilities.h"

/*class B1 //1.feladat
{
public:
	virtual void vf()
	{
		cout << "B1::vf" << endl;
	}
	void f()
	{
		cout << "B1::f" << endl;
	}
	//virtual void pvf() = 0;  //--> Hibát dob a fordító, ha nem törlünk B1 objektumot.
							   //--> Ha egy osztály bármely funkciója virtuálisak, akkor az osztály önmagában nem lesz objektum
}; */

//6.feladat
class B1
{
public:
	virtual void vf() 
	{ 
		cout << "B1::vf" << endl;
	}
	virtual void pvf() = 0;
}; 

//7.feladat
class B2
{
public:
	virtual void pvf() = 0;
};

//2.feladat
class D1 : public B1 
{
public:
	void vf() override
	{
		cout << "D1::vf (override)" << endl;
	}
	void pvf() override //6. feladat kiegészítés
	{
		cout << "D1:pvf (override)" << endl;
	}
	void f() //4.feladat kiegészítés
	{
		cout << "D1::f" << endl;
	}
};

//6.feladat
class D2 : public D1
{
public:
	void pvf() override
	{
		cout << "D2::pvf (override)" << endl;
	}
};

//7.feladat
class D21 : public B2
{
public:
	void pvf() override 
	{ 
		cout << "D21: " << szoveg << endl;
	}
	string szoveg;
};

class D22 : public B2
{
public:
	void pvf() override 
	{
		cout << "D22: " << ertek << endl;
	}
	int ertek;
};

void f(B2& b2ref)
	{
		b2ref.pvf();
	}

int main()
{
	//1.feladat
	/*B1 b1;
	b1.vf();
	b1.f();*/

	//2.feladat
	/*D1 d1;
	d1.vf(); 
	d1.pvf(); //6.feladat
	d1.f(); *///4.feladat kiegészítés

	//3.feladat
	/*B1& b1ref = d1;  //Mivel B1 típusra való hivatkozás
	b1ref.vf(); //Ha nem lenne virtual void, akkor B1.vf-t fogja hívni, ha virtual, akkor D1.vf-t használja
	b1ref.f(); //Ami B1.f()-et hívja, de semmit sem tud a D1 funkcióról*/

	//6.feladat
	D2 d2;
	d2.vf();
	d2.pvf();
	d2.f();

	//7.feladat
	D21 d21;
	d21.szoveg = "Ez olyan bonyolult.";

	D22 d22;
	d22.ertek = 99;

	f(d21);
	f(d22);


	return 0;
}
