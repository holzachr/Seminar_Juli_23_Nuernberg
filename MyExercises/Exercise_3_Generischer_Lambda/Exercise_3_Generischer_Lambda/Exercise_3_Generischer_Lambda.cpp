// Exercise_3_Generischer_Lambda.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <vector>
#include <string>


class Person
{
private:
    std::string m_name;
    size_t m_age;

public:
    Person(std::string name, int age) : m_name(name), m_age(age) {};    

    size_t getAge()
    {
        return m_age;
    }
};


int main()
{
    std::vector<Person> personValues{
        Person{ "Hans", 40 },
        Person{ "Sepp", 60 }
    };

    auto isGreaterThanFifty = [](const Person& n) { return n.getAge() > 50; };

    // use generic lambda with a vector of Persons
    auto pos = std::find_if(
        std::begin(personValues),
        std::end(personValues),
        isGreaterThanFifty
    );
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
