#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <list>

//1.feladat
struct Item
{
	std::string name;
	int iid;
	double value;

	Item() : name(), iid(0), value(0) {}
	Item(std::string n, int i, double v) : name(n), iid(i), value(v) {}
};

struct sort_name
{
	bool operator()(const Item& a, const Item& b) const
	{
		return a.name < b.name;
	}
};

struct sort_iid
{
	bool operator()(const Item& a, const Item& b) const
	{
		return a.iid < b.iid;
	}
};

struct sort_value
{
	bool operator()(const Item& a, const Item& b) const
	{
		return a.value > b.value;
	}
};

//6.feladat
class Find_by_name
{

	std::string name;

public: 

	Find_by_name(const std::string& s) : name(s) { }
	bool operator()(const Item& item) const 
	{
		return item.name == name;
	}
};

//7.feladat
class Find_by_iid
{

	int iid;

public: 

	Find_by_iid(int i) : iid(i) { }
	bool operator()(const Item& item) const 
	{
		return item.iid == iid;
	}
};

//Reading file
std::istream& operator>>(std::istream& is, Item& item)
{
	std::string name;
	int iid;
	double value;

	is >> name >> iid >> value;
		if(!is) return is; 

	item = Item(name, iid, value);

	return is;
}

std::ostream& operator<<(std::ostream& os, const Item& item)
{
	return os << item.name << " - " << item.iid << " - " << item.value;
}

int main()
{
	std::list<Item> li;
	const std::string file = "ch21.txt";

	std::cout << "List - fill with ten items from file\n";
	{

		std::ifstream ifs(file.c_str());
		if (!ifs) std::cout << ("Can't open", file);

		Item i;
		while (ifs>>i) li.insert(li.end(),i);
	}

	for(const auto& e : li) std::cout << e << " " << std::endl;
	std::cout << std::endl;
	
	//Sort by name - 2 feladat
	std::cout << "Sort by name" << std::endl;
	//li.sort(sort_name());
	li.sort([] (Item const& a, Item const& b) { return a.name < b.name;});

	for(const auto& e : li) std::cout << e.name << " " << std::endl;
	std::cout << std::endl;

	//Sort by iid - 3 feladat
	std::cout << "Sort by iid" << std::endl;
	//li.sort(sort_iid());
	li.sort([] (const Item& a, const Item& b) { return a.iid < b.iid;});

	for(const auto& e : li) std::cout << e.iid << " " << std::endl;
	std::cout << std::endl;

	//Sort by value - 4 feladat (csökkenő)
	std::cout << "Sort by value - descreasing" << std::endl;
	//li.sort(sort_value());
	li.sort([] (const Item& a, const Item& b) { return a.value > b.value;});

	for(const auto& e : li) std::cout << e.value << " " << std::endl;
	std::cout << std::endl;

	//Insert values - 5 feladat
	std::cout << "Insert values ..." << std::endl;
	li.insert(li.end(),Item("Horsesh",99,12.34));
	li.insert(li.end(),Item("C S400",9988, 499.95));
	li.sort(sort_name());

	for(const auto& e : li) std::cout << e.name << " " << std::endl;
	std::cout << std::endl;

	//Two values erase...
	std::cout << "Erase values with name" << std::endl;

	std::list<Item>::iterator li_it = find_if(li.begin(),li.end(), Find_by_name("Teszt18"));
	li.erase(li_it);
	li_it = find_if(li.begin(),li.end(), Find_by_name("Teszt20"));
	li.erase(li_it);
 
	li.sort(sort_name());

	for(const auto& e : li) std::cout << e.name << " " << std::endl;
	std::cout << std::endl;

	//Two iid erase
	std::cout << "Erase values with iid" << std::endl;

	li_it = find_if(li.begin(),li.end(), Find_by_iid(151235));
	li.erase(li_it);
	li_it = find_if(li.begin(),li.end(), Find_by_iid(151236));
	li.erase(li_it);

	li.sort(sort_name());
	
	for(const auto& e : li) std::cout << e.iid << " " << std::endl;
	std::cout << std::endl;


	return 0;
}
