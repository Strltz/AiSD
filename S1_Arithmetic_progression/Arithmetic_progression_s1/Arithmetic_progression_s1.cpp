// gh: Strltz, tg: S dvumya V
// 
// Finding the excluded element of an arithmetic progression

#include <iostream>

int main()
{
	int sum;
	int n;
	std::cout << "Enter sum:" << std::endl;
	std::cin >> sum;
	std::cout << "Enter n:" << std::endl;
	std::cin >> n;
	int res = int((n * (n + 1) / 2)) - sum;
	std::cout << res;

	return res;
}
