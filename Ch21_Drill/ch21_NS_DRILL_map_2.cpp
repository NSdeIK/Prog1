#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>

struct sum_values
	{
		int operator()(int i, const std::pair<std::string, int>& it)
		{
			return i + it.second;
		}
	};

//2.5 feladat
void map_read_values(std::map<std::string,int>& msi)
{
	std::string s;
	int i;

	std::cin >> s >> i;
	if(!std::cin) std::cout << "Failed..." << std::endl;
	msi[s] = i;
}

int main()
{
	//2.1 feladat
	std::map<std::string,int> msi;

	//2.2 feladat
	msi["lecture"] = 21;
	msi["lecture5"] = 57;
	msi["lecture6"] = 30;
	msi["lecture3"] = 80;
	msi["lecture2"] = 65;
	msi["lecture4"] = 42;
	msi["lecture1"] = 48;
	msi["lecture7"] = 15;
	msi["lecture8"] = 89;
	msi["lecture9"] = 74;

	//2.3 feladat
	std::cout << "-----Default pairs from map-----" << std::endl;
	
	for(const auto& e : msi)
	{
		std::cout << e.first << " - " << e.second << std::endl;
	}
	
	//2.4 feladat
	auto p = std::find(msi.begin(),msi.end(),*msi.begin());

	std::cout << "----- Erase before - Size: " << msi.size() << " -----" << std::endl;

	while(p!=msi.end()) p = msi.erase(p);

	std::cout << "----- Erase after - Size: " << msi.size() << " -----" << std::endl;
	
	//2.6 feladat
	std::cout << "----- Cin ten pairs... -----\nFormatum: \n\tlecture 21\n\ttest 25\nWrite:\n  " << std::endl; 
	for(int i = 0; i<10; ++i)
		map_read_values(msi);

	//2.7 feladat
	std::cout << "\nChecking...\n\n";
	for(const auto& e : msi)
	{
		std::cout << e.first << " - " << e.second << std::endl;
	}
	
	//2.8 feladat
	int sum_val = 0;
	int sum = std::accumulate(msi.begin(), msi.end(), sum_val, sum_values());
	
	std::cout << "\nSum values: " << sum << std::endl;
	
	//2.9 feladat
	std::map<int, std::string> mis;
	
	//2.10 feladat
	for (auto m : msi)
	{
		mis[m.second] = m.first;
	}
	
	//2.11 feladat
	std::cout << "\nswap values...\n";
	for(const auto& e : mis)
	{
		std::cout << e.first << " - " << e.second << std::endl;
	}
	std::cout << std::endl;
	
	

	return 0;
}
