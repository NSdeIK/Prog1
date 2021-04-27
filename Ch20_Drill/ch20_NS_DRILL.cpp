#include <iostream>
#include <list>
#include <vector>

int main()
{
	//1.feladat - int array
	int intTomb[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	
	//2.feladat - vector<int>
	std::vector <int> intVector { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	
	//3.feladat - list 
	std::list<int> intList { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; 
	
	//4.feladat - copy 
	int intTomb2[10];
	std::copy(std::begin(intTomb), std::end(intTomb), std::begin(intTomb2));
	
	std::vector<int> intVector2 = intVector;
	
	std::list<int> intList2 = intList;
	
	//5.feldat - increase value
	
	for(auto& e : intTomb) e += 2;
	
	for(auto& e : intVector) e += 3;
	
	for(auto& e : intList) e += 5;
	
	
	
	//Check 
	std::cout << "Int tömb1: " << std::endl;
	for(const auto& e : intTomb)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	
	std::cout << "Int tömb2: " << std::endl;
	for(const auto& e : intTomb2)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	
	std::cout << "Vector Int 1: " << std::endl;
	for(const auto& e : intVector)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	
	std::cout << "Vector Int 2: " << std::endl;
	for(const auto& e : intVector2)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	
	std::cout << "List 1: " << std::endl;
	for(const auto& e : intList)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	
	std::cout << "List 2: " << std::endl;
	for(const auto& e : intList2)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	
	return 0;
}
