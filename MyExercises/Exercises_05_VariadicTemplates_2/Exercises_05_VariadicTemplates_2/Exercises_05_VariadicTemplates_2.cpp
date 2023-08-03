// Exercises_05_VariadicTemplates_2.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>



template<typename T1, typename T2>
bool sameType(T1 arg1, T2 arg2)
{
    return std::is_same<decltype(arg1), decltype(arg2)>::value;
}

template<typename T1, typename T2, typename ... TRest>
bool sameType(T1 arg1, T2 arg2, TRest ... m)
{    
    return sameType(arg1, arg2) && sameType(arg2, m ...);
}




int main() {
    bool result;
    result = sameType(1, 2, 3, 4, 5, 6, 7, 8, 9);
    std::cout << std::boolalpha << result << std::endl;

    result = sameType(1, 2, 3, 4, '?', 5, 6, 7, 8, 9);
    std::cout << std::boolalpha << result << std::endl;
    return 1;
}
