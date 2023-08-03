// Exercises_03_Algorithms_2.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>


int main()
{
    std::vector<int> vec(20);

    std::generate(
        std::begin(vec),
        std::end(vec),
        [p = std::pair{ 0, 1 }]() mutable {
            std::cout << p.first << " ";
            int temp = p.first;
            p.first = p.second;
            p.second = temp + p.second;
            return temp;
        }
    );
}
