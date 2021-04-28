#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>


int main()
{
	//3.1 feladat
	const std::string filename = "ch21_v.txt";
	std::ifstream ifs(filename.c_str());
	if(!ifs) std::cout << "I can't open this file: " << filename << std::endl;

	std::vector<double> vd;
	double v;

	while(ifs>>v) vd.push_back(v);

	//3.2 feladat
	std::cout << "vd: \n";
	for(const auto& e: vd)
		std::cout << e << "\n";

	//3.3 feladat
	std::vector<int> vi(vd.size());
	copy(vd.begin(),vd.end(),vi.begin());

	//3.4 feladat
	std::cout << "\nPairs [ vd - vi ]\n";

	for(int i = 0; i < vd.size(); ++i)
		std::cout << "[ " << vd[i] << " - " << vi[i] << " ]\n";

	//3.5 feladat
	double sum_vd = 0;
	sum_vd = accumulate(vd.begin(),vd.end(),sum_vd);
	std::cout << "\nSum values from [vd] - SUM: [ "<< sum_vd << " ] \n"; 
	
	//3.6 feladat
	int sum_vi = 0;
	sum_vi = accumulate(vi.begin(),vi.end(),sum_vi);
	std::cout << "\nSum values from [vi] - SUM: [ "<< sum_vi << " ] \n"; 

	std::cout << "\nDifference of [sum_vd, sum_vi]: " << sum_vd - sum_vi << "\n";

	//3.7 feladat
	std::cout << "\nReserved vd: \n";
	reverse(vd.begin(),vd.end());
	for(const auto& e : vd)
		std::cout << e << "\n"; 	

	//3.8 feladat
	double vd_mean = sum_vd/vd.size();
	std::cout << "\nMean [vd]: " << vd_mean << "\n";


	//3.9 feladat
	std::cout << "\nMean > value\n";
	std::vector<double> vd2(count_if(vd.begin(),vd.end(), [&](double v) -> bool { return v < vd_mean; }));
	copy_if(vd.begin(),vd.end(),vd2.begin(), [&](double v) -> bool { return v < vd_mean; });
	for(const auto&e : vd2)
		std::cout << e << "\n";

	//3.10 feladat
	std::cout << "\nSort vd\n";
	sort(vd.begin(),vd.end());
	for(const auto&e : vd)
		std::cout << e << "\n";

	return 0;
}