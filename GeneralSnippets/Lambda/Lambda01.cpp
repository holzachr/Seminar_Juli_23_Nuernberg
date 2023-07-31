// =====================================================================================
// Lambda01.cpp // Lambda Methods
// =====================================================================================

module modern_cpp:lambda;

namespace Lambdas {

    //long belegeVor()
    //{
    //    static int i = 0;

    //    i++;

    //    // 2 * i + 1
    //    return 2 * i + 1;
    //}

    //// Besser: Template-Funktion, da typunabhängig
    //template <typename T>
    //auto belegeVor()
    //{
    //    static int i = 0;

    //    i++;

    //    // 2 * i + 1
    //    return 2 * i + 1;
    //}

    //// Statt Template, historisch, Variante 1: "Der Funktor" = aufrufbares Objekt
    //// = Objekt, das den ()-Aufrufoperator bereitstellt
    //class Vorbeleger
    //{
    //private:
    //    int m_factor;
    //    int m_i;

    //public:
    //    Vorbeleger(int factor) : m_factor(factor), m_i(0) {}

    //    // Statt int belegeVor() {}: Aufrufoperator!
    //    auto operator () ()
    //    {
    //        m_i++;
    //        return m_factor * m_i + 1;
    //    }
    //};

    //// Funktor-Verwendung:
    //void wasIstEinFunktor()
    //{
    //    Vorbeleger beleger(3);  // Funktor-Konstruktor

    //    beleger();              // Funktor-Aufruf
    //}



    //void wiederholung()
    //{
    //    // using = typedef
    //    typedef std::vector<long> MyContainer;      // <--- Zentrale Definition
    //    using MyContainer = std::vector<long>;      // Geht auch

    //    // STL-Container
    //    MyContainer numbers(10);

    //    // Iterator-Objekt = Position
    //    // STL-Iteratoren
    //    auto start = numbers.begin();
    //    std::vector<long>::iterator start2 = numbers.begin();   // Eigentlich von diesem Typ
    //    MyContainer::iterator start3 = numbers.begin();         // Mit using

    //    auto end = numbers.end();

    //    // STL-Algorithmus
    //    // => verwendet automatisch std::memset, ohne notwendige manuelle Berechnung des Bytecount, void*-Adresse etc.
    //    std::fill(
    //        start,
    //        end,
    //        123);

    //    // Geht auch, aber schlechte Performance wegen Einzelzugriffen
    //    for (int i = 0; i < numbers.size(); i++)
    //    {
    //        numbers[i] = 123;
    //    }

    //    // Für den Problemfall numbers[i] = 2 * i + 1:
    //    // Historische Lösung, STL aber nicht mehr zeitgemäß
    //    std::generate(
    //        start,
    //        end,
    //        belegeVor // 2 * i + 1
    //    );

    //    std::generate(
    //        start,
    //        end,
    //        belegeVor<long> // 2 * i + 1
    //    );

    //    Vorbeleger beleger(2);
    //    std::generate(
    //        start,
    //        end,
    //        // 2 * i + 1
    //        &beleger
    //    )
    //}

    bool compare (int n1, int n2) {
        return n1 < n2;
    }

    // Funktor = aufrufbares Objekt
    class Comparer
    {
    private:
        bool m_flag;

    public:
        Comparer() : m_flag{ true } {}
        Comparer(bool flag) : m_flag{ flag } {}

        bool operator() (int n1, int n2) const {
            return (m_flag) ? n1 < n2 : n1 > n2;
        }
    };

    void test_00()
    {
        Comparer obj{ false };
        bool result = obj(1, 2);
        std::cout << std::boolalpha << result << std::endl;
    }

    void test_01()
    {
        // Ein Lambda ist eine lokale Klasse mit einem Aufrufoperator!
        // local class within function possible
        class LocalComparer
        {
        private:
            bool m_flag;

        public:
            LocalComparer() : m_flag{ true } {}
            LocalComparer(bool flag) : m_flag{ flag } {}

            bool operator() (int n1, int n2) const {
                return (m_flag) ? n1 < n2 : n1 > n2;
            }
        };

        std::vector<int> vec { 5, 9, 1, 3, 7, 8 };

        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        std::sort(std::begin(vec), std::end(vec), compare);
        // or
        std::sort(std::begin(vec), std::end(vec), Comparer());
        // or
        std::sort(std::begin(vec), std::end(vec), Comparer{false});
        // or
        std::sort(std::begin(vec), std::end(vec), LocalComparer{});
        // or
        std::sort(
            std::begin(vec),
            std::end(vec),
            [] (int n1, int n2) {             // <--- LAMBDA-Funktion
                std::cout << "Lambda mit " << n1 << " und " << n2 << std::endl;
                return n1 < n2;
            }
        );

        // or
        std::sort(
            std::begin(vec), 
            std::end(vec), 
            [flag = true] (int n1, int n2) {             // <--- LAMBDA-Funktion mit Eingangsparametern
                std::cout << "Lambda mit " << n1 << " und " << n2 << std::endl;
                return (flag) ? n1 < n2 : n1 > n2;       // Mit ternärem Operator für Modi
           }
        );

        // Ein LAMBDA ist ein OBJEKT, keine Funktion!

        for (int n : vec) {
            std::cout << n << ' ';
        }
    }

    void test_02() {

        std::vector<int> vec{ 50, 90, 10, 30, 70, 80 };

        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        std::sort(
            std::begin(vec),
            std::end(vec),
            [] (int n1, int n2) { return n1 < n2; }
        );

        for (int n : vec) {
            std::cout << n << ' ';
        }
    }

    void test_03() {

        // shortest lambda on earth: no parameters, capturing and doing nothing
        auto nothing = [] {};
        nothing();

        // c'tor notation
        auto itsOne ([] { return 1; });
        auto itsTwo ([] { return 2; });
        std::cout << itsOne() << ", " << itsTwo() << std::endl;

        // "copy-c'tor" notation
        auto itsFour = [] { return 4; };
        auto itsFive = [] { return 5; };
        std::cout << itsFour() << ", " << itsFive() << std::endl;
    }

    void test_04() {

        // defining a lambda without 'auto'
        // --> Ein Lambda ist eigentlich vom Typ std::function, ähnlich einem Funktionspointer!
        std::function<int(int, int, int)> threeArgs([](int x, int y, int z) -> int {
            return x + y + z; 
            }
        );

        std::cout << threeArgs (5, 6, 7) << std::endl;
    }

    void test_05() {

        // defining new variables in the lambda capture:
        // we can declare a new variable that is only visible
        // in the scope of the lambda: We do so by defining a variable
        // in the lambda-capture without specifying its type:

        // lambda with variable definition
        auto lambda = [variable = 10] () { return variable; };      // Einer Lambda-Funktion einen Namen zu geben ist nicht der Regelfall!
        std::cout << lambda() << std::endl;                         // Aufruf der Lambda-Funktion mit Namen

        // lambda with member / instance variable definition
        auto lambda2 = [variable = 10]() mutable {                  // <-- mutable!
            variable++;
            return variable; 
        };     
        std::cout << "test05 " << lambda2() << std::endl;                        // Aufruf der Lambda-Funktion mit Namen

        // Captures default to 'const value':
        // The mutable keyword removes the 'const' qualification from all captured variables
        auto counter = [count = 50] () mutable { 
            ++count; 
            return count;
        };

        for (size_t i{}; i < 5; ++i) {
            std::cout << counter() << " ";
        }
        std::cout << std::endl;
    }

    void test_06() {

        int n = 1;
        int m = 2;

        // Zugriff auf lokale Variablen:
            
        // Alle als Kopie [=] = 1, 2
        auto l1 = [=] {                                                 
            std::cout << "Copy:      " << n << " " << m << std::endl;
        };

        // Alle als Referenz [&] = 3, 4
        auto l2 = [&] {
            std::cout << "Reference: " << n << " " << m << std::endl;
        };

        // n als Referenz, m als Kopie = 3, 2
        auto l3 = [&, m] {
            std::cout << "Both:      " << n << " " << m << std::endl;
        };

        // n als Kopie, m als Referenz = 1, 4
        auto l4 = [=, &m] {
            std::cout << "More both: " << n << " " << m << std::endl;
        };

        n = 3;
        m = 4;

        l1();
        l2();
        l3();
        l4();
    }

    auto test_07_helper_a() {

        int n = 1;
        int m = 2;

        auto lambda = [=] {
            std::cout << "Copy:      " << n << " " << m << std::endl;
        };

        return lambda;
    }

    auto test_07_helper_b() {

        int n = 1;
        int m = 2;

        auto lambda = [&] {
            std::cout << "Reference: " << n << " " << m << std::endl;
        };

        return lambda;  // I would't do this never ever :-)
    }

    void test_07() {

        auto outerLambda1 = test_07_helper_a();
        auto outerLambda2 = test_07_helper_b();
        outerLambda1();
        outerLambda2();     // Gibt ungültige Ausgabe, weil n und m als Referenzen mit Auslaufen der Funktion test_07_helper_b() nicht mehr in Scope sind!
    }

    void test_08() {

        // demonstrating 'noexcept'
        auto itsOne([] () noexcept { return 1; });
        auto itsTwo = [] () noexcept { return 2; };
        std::cout << itsOne() << ", " << itsTwo() << std::endl;
    }

    void test_09() {
        // IIFE -Immediately Invoked Functional Expression:
        // Inline-definition and direct invocation of lambda funtion:
        
        std::cout << [](int l, int r) { return l + r; } (11, 12) << std::endl;

        // Use case for IIFE:
        // This kind of expression might be useful when you have
        // a complex initialization of a const  object:

        auto constexpr ConstValue = [] () {
            /* several lines of code ... - "very complex" computation */
            return 123;
        }();

        std::cout << "Const Value: " << ConstValue << std::endl;
    }
}

void main_lambdas()
{
    using namespace Lambdas;
    //test_00();
    //test_01();
    //test_02();
    ////test_03();
    //test_04();
    test_05();
    //test_06();
    //test_07();
    //test_08();
    //test_09();
}

// =====================================================================================
// End-of-File
// =====================================================================================
