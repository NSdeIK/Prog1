#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

//6.feladat
template<typename Iterator, typename Out>
Out my_copy(Iterator first, Iterator last, Out res)
{
	while(first != last)
	{
		*res = *first;
		res++;
		first++;
	}
	return res;
}


int main()
{
	//int array
	int intTomb[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	
	//vector<int>
	std::vector <int> intVector { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	
	//list 
	std::list<int> intList { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; 
	
	//copy - default
	int intTomb2[10];
	std::copy(std::begin(intTomb), std::end(intTomb), std::begin(intTomb2));
	
	std::vector<int> intVector2 = intVector;
	
	std::list<int> intList2 = intList;
	
	//increase value
	
	for(auto& e : intTomb) e += 2;
	
	for(auto& e : intVector) e += 3;
	
	for(auto& e : intList) e += 5;
	
	//7.feladat - copy
	my_copy(std::begin(intTomb), std::end(intTomb), intVector2.begin());
	my_copy(intList.begin(), intList.end(), std::begin(intTomb2));
	
	//8.feladat - find - 3 value in vector
	int three = 3;
		auto value3 = std::find(begin(intVector),end(intVector), three );
			if(value3 != end(intVector))
				std::cout << "IntVector contains '3' value\n" << "Position: " << std::distance(intVector.begin(), value3) << std::endl << std::endl;
			else
				std::cout << "IntVector does not contain '3' value\n" << std::endl;
	
	//find - 27 value in list
	int value = 27;
		auto value27 = std::find(begin(intList),end(intList), value );
		if(value27 != end(intList))
			std::cout << "IntVector contains '27' value\n" << "Position: " << std::distance(intList.begin(), value27) <<  std::endl;
		else
			std::cout << "IntVector does not contain '27' value\n" << std::endl;
			
	intList.push_back(27);
		value27 = std::find(begin(intList),end(intList), value );
			if(value27 != end(intList))
				std::cout << "IntVector contains '27' value\n" << "Position: " << std::distance(intList.begin(), value27) << std::endl << std::endl;
			else
				std::cout << "IntVector does not contain '27' value\n" << std::endl;
	
	
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
