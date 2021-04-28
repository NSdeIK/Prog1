#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>

//1.feladat
struct Item
{
	std::string name;
	int iid;
	double value;

	Item() : name(), iid(0), value(0) {}
	Item(std::string n, int i, double v) : name(n), iid(i), value(v) {}
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
	std::vector<Item> vi;
	const std::string file = "ch21.txt";

	std::cout << "Vector - fill with ten items from file\n";
	{

		std::ifstream ifs(file.c_str());
		if (!ifs) std::cout << ("Can't open", file);

		Item i;
		while (ifs>>i) vi.insert(vi.end(),i);
	}

	for(const auto& e : vi) std::cout << e << " " << std::endl;
	std::cout << std::endl;
	
	//Sort by name - 2 feladat
	std::cout << "Sort by name" << std::endl;
	std::sort(vi.begin(), vi.end(), [] (const Item& a, const Item& b) { return a.name < b.name;});

	for(const auto& e : vi) std::cout << e.name << " " << std::endl;
	std::cout << std::endl;

	//Sort by iid - 3 feladat
	std::cout << "Sort by iid" << std::endl;
	std::sort(vi.begin(), vi.end(), [] (const Item& a, const Item& b) { return a.iid < b.iid;});

	for(const auto& e : vi) std::cout << e.iid << " " << std::endl;
	std::cout << std::endl;

	//Sort by value - 4 feladat (csökkenő)
	std::cout << "Sort by value - descreasing" << std::endl;
	std::sort(vi.begin(), vi.end(), [] (const Item& a, const Item& b) { return a.value > b.value;});

	for(const auto& e : vi) std::cout << e.value << " " << std::endl;
	std::cout << std::endl;

	//Insert values - 5 feladat
	std::cout << "Insert values ..." << std::endl;
	vi.insert(vi.end(),Item("Horsesh",99,12.34));
	vi.insert(vi.end(),Item("C S400",9988, 499.95));
	std::sort(vi.begin(), vi.end(), [] (const Item& a, const Item& b) { return a.name < b.name;});

	for(const auto& e : vi) std::cout << e.name << " " << std::endl;
	std::cout << std::endl;

	//Two values erase...
	std::cout << "Erase values with name" << std::endl;

	std::vector<Item>::iterator vi_it = find_if(vi.begin(),vi.end(), Find_by_name("Teszt18"));
	vi.erase(vi_it);
	vi_it = find_if(vi.begin(),vi.end(), Find_by_name("Teszt20"));
	vi.erase(vi_it);
 
	std::sort(vi.begin(), vi.end(), [] (const Item& a, const Item& b) { return a.name < b.name;});

	for(const auto& e : vi) std::cout << e.name << " " << std::endl;
	std::cout << std::endl;

	//Two iid erase
	std::cout << "Erase values with iid" << std::endl;

	vi_it = find_if(vi.begin(),vi.end(), Find_by_iid(151235));
	vi.erase(vi_it);
	vi_it = find_if(vi.begin(),vi.end(), Find_by_iid(151236));
	vi.erase(vi_it);

	std::sort(vi.begin(), vi.end(), [] (const Item& a, const Item& b) { return a.iid < b.iid;});
	
	for(const auto& e : vi) std::cout << e.iid << " " << std::endl;
	std::cout << std::endl;


	/*for(const auto& e : vi) std::cout << e << " " << std::endl;
	std::cout << std::endl;*/

	return 0;
}