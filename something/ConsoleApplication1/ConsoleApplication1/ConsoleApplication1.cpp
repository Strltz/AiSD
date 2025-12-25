#include <iostream>

class TheClass {
public:

    TheClass(int b) {
        a = b;
    }

    int a;
    TheClass* ukaz = nullptr;

};

int main()
{

    TheClass frst(5);
    TheClass scnd(5);
    scnd.ukaz = &frst;

    TheClass* pred = &scnd;

    for (size_t i = 0; i < 4; ++i) {
        TheClass* thrd = new TheClass(i);
        (*thrd).ukaz = pred;
        pred = thrd;
    }

    std::cout << scnd.a << std::endl; // 5
    std::cout << (*pred).a << std::endl; // 3
    pred = (*pred).ukaz;
    std::cout << (*pred).a << std::endl; // 2
    pred = (*pred).ukaz;
    std::cout << (*pred).a << std::endl; // 1
    pred = (*pred).ukaz;
    std::cout << (*pred).a << std::endl; // 0
   

}

