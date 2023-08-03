// Exercises_12_PerfectForwarding_2.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <chrono>



class ExecutionTimer {

public:

    template<typename F, typename ... Args>
    static std::chrono::milliseconds duration(F&& f, Args&& ... args) {

        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

        // Ausführen
        std::invoke(std::forward<F>(f), std::forward<Args>(args) ...);

        std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
        auto tpStart = std::chrono::time_point_cast<std::chrono::milliseconds>(start);
        auto tpEnd = std::chrono::time_point_cast<std::chrono::milliseconds>(end);
        return tpEnd - tpStart;
    }


private:

};





void g(int a, double b)
{
    // simulate some work (function with parameters)
    std::cout << "calling g with parameters " << a << " and " << b << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void h(int a, double b, std::string c)
{
    // simulate some work (function with parameters)
    std::cout << "calling h with parameters " << a << " and " << b << " and " << c << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void main()
{
    std::chrono::milliseconds time = ExecutionTimer::duration(g, 10, 20.0);
    std::cout << time.count() << " msecs." << std::endl;

    time = ExecutionTimer::duration(h, 10, 20.0, "test123");
    std::cout << time.count() << " msecs." << std::endl;
}