// Exercises_04_UtilityClasses_2.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <variant>
#include <vector>


class Book
{
public:
    Book(std::string title, std::string author, double price, int inventory) :
        m_Title(title),
        m_Author(author),
        m_Price(price),
        m_Inventory(inventory)
    {
    }

    std::string m_Title;
    std::string m_Author;
    double m_Price;
    int m_Inventory;
};

class Movie
{
public:
    Movie(std::string title, std::string author, double price, int inventory) :
        m_Title(title),
        m_Author(author),
        m_Price(price),
        m_Inventory(inventory)
    {
    }

    std::string m_Title;
    std::string m_Author;
    double m_Price;
    int m_Inventory;
};

// Template-Klasse, übernimmt bei Objekterstellung automatisch Typen von Medien
template <typename ... TMedia>
class Bookstore
{
private:
    // Falls nicht Template-Klasse: using SimpleItems = std::vector<std::variant<Book, Movie>>;
    // using = wie Define, zur Kurzschreibung im Folgenden.
    using Items = std::vector<std::variant<TMedia ...>>;

    // Initializer-List-Konzept soll Init-Werte über den Stack statt über den Heap transportieren
    using ItemsList = std::initializer_list<std::variant<TMedia ...>>;  
    Items m_Items;

public:
    Bookstore(ItemsList items) : m_Items{ items } {}


    double totalBalance()
    {
        double balance = 0;
        for (const auto& n : m_Items)
        {
            double price{};
            int number{};

            // "Duck Typing": Passende elem werden aufgrund ihrer hier geforderten Methoden automatisch erkannt.
            // Würde man totalBalance() / den visitor an einem Objekt ohne m_Price, m_Inventory 
            // aufrufen, wäre der Code nicht übersetzungsfähig!
            //              / &: Umgebungsvariablen price und number verwenden dürfen
            auto visitor = [&](auto const& elem) {
                price = elem.m_Price;
                number = elem.m_Inventory;
            };

            std::visit(visitor, n);

            balance += price * number;            
        }
        return balance;
    }

    // Alternativer Ansatz: balance = std::visit(), Visitor/Lambda returned zusammengezählten Wert.

    // Template-Member-Methode
    // Nicht-variadisch, nur 1 Typ T, anstelle ...TMedia.
    // MUSS aber ein Element von ...TMedia der Template-Klasse sein!
    template <typename T>
    void addMedia(const T& media)
    {
        m_Items.push_back(media);
    }
};


int main()
{
    Book cBook{ "C", "Dennis Ritchie", 11.99, 12 };
    Book javaBook{ "Java", "James Gosling", 17.99, 21 };
    Book cppBook{ "C++", "Bjarne Stroustrup", 16.99, 4 };
    Book csharpBook{ "C#", "Anders Hejlsberg", 21.99, 8 };

    Movie movieTarantino{ "Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3 };
    Movie movieBond{ "Spectre", "Sam Mendes", 8.99, 6 };

    using MyBookstore = Bookstore<Book, Movie>;

    MyBookstore bookstore = MyBookstore{
        cBook, movieBond, javaBook, cppBook, csharpBook, movieTarantino
    };

    std::cout << "Balance: " << bookstore.totalBalance() << std::endl;
}

