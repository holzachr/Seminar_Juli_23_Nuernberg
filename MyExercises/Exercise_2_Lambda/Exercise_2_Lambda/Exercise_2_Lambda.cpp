// Exercise_2_Lambda.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

//void even(int val) {
//    if ((val % 2) == 0) {
//        std::cout << " is even." << std::endl;
//    }
//}

class even
{
private:
    int m_Nenner;

public:
    even(int nenner) : m_Nenner(nenner) {}

    auto operator () (int n)
    {
        if ((n % m_Nenner) == 0) {
            std::cout << n << " is even." << std::endl;
        }       
    }
};

int main()
{
    std::vector<int> v {3, -4, 2, -8, 15, 267};

    auto lambda = [](int n)
    {
        if ((n % 2) == 0) {
            std::cout << n << " is even." << std::endl;
        }
    };

    std::for_each(v.cbegin(), v.cend(), lambda);

    std::cout << std::endl;

    std::for_each(v.cbegin(), v.cend(), even(2));
}
