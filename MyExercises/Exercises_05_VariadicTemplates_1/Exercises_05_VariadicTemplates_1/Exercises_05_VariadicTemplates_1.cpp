// Exercises_05_VariadicTemplates_1.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>



template<typename T>
bool andAll(T n)
{
    return n;
}

template<typename T, typename ... TRest>
bool andAll(T n, TRest ... m)
{   
    return n && andAll<TRest ...>(m ...);
}


template<typename T>
bool orAll(T n)
{
    return n;
}

template<typename T, typename ... TRest>
bool orAll(T n, TRest ... m)
{
    bool result = (std::is_same<decltype(n), bool>::value);
    return n || orAll<TRest ...>(m ...);
}


int main()
{
    bool result = andAll(true, false, true);
    std::cout << std::boolalpha << result << std::endl;

    result = andAll(true, true, true, true, true, true, true, true, true, true);
    std::cout << std::boolalpha << result << std::endl;

    result = andAll(true, true, true, true, true, 3, true, true, true, true);
    std::cout << std::boolalpha << result << std::endl;

    result = orAll(1, 2, 3);
    std::cout << std::boolalpha << result << std::endl;

    result = orAll(false, 2, false);
    std::cout << std::boolalpha << result << std::endl;
}

