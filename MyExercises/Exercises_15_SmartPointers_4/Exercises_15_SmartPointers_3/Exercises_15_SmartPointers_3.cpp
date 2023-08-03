// Exercises_15_SmartPointers_3.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>


class LightAndSafeWatcher {
private:
    std::weak_ptr<int> m_ptr;

public:
    LightAndSafeWatcher() {}

    void watch(const std::shared_ptr<int>& sp)
    {
        m_ptr = sp;
    }

    int currentValue() const
    {
        std::shared_ptr<int> sp{ m_ptr.lock() };
        if (sp != nullptr)
        {
            return *sp;
        }
        else
        {
            throw std::exception{ "No value available!" };
        }        
    }
};

int main()
{
    LightAndSafeWatcher watcher;

    {
        std::shared_ptr<int> sp = std::make_shared<int>(123);
        watcher.watch(sp);
        std::cout << "Value: " << watcher.currentValue() << std::endl;
    }

    std::cout << "Value: " << watcher.currentValue() << std::endl;
}




