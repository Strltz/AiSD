// gh: Strltz, tg: S dvumya V
// 
// The problem of exponentiation

#include <iostream>
#include <cmath>
#include <bitset>

double this_pow(double a, int n) {
    double res = 1;
    for (size_t i = 0; i < n; ++i) {
        res *= a;
    }
    return res; // time O(1); memory O(n)
}

double pow_optimal(double a, int n) {
    std::bitset<32> bitset = n; 
    // let's take the previous operation as O(1)
    double res = 1;
    for (size_t i = 0; i <= log2(n); ++i) {
        if (bitset[i] == 1) {
            res *= pow(a, pow(2, i));
            // let's take the previous operation as O(1)
        }
    }
    return res; // time O(log2(n)); memory O(1)
}

int main()
{
    double a;
    int n;
    std::cout << "a^n" << std::endl;
    std::cout << "Enter a real number (a):" << std::endl;
    std::cin >> a;
    std::cout << "Enter a natural (n):" << std::endl;
    std::cin >> n;
    std::cout << pow_optimal(a, n);
}

