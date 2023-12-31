// =====================================================================================
// Variant.cpp // std::variant: C++ 17
// 
//  Ist ein Objekt das Daten unterschiedlichen Typs enthalten kann.
//  Zu einem Zeitpunkt nur nur eine Variable.
// 
//  Beispiel Excel: Zelle: Number/String/Date/Double
//           Spiel: Board: Figure: Pro Boardslot eine andere Figur
// 
// =====================================================================================

// Untermodul (Partition) anziehen. Enth�lt u.A. "import std;".
module modern_cpp:variant;

namespace VariantDemo {

    void test_01() {

        // Festlegung zur �bersetzungszeit: Welche Datentypen m�ssen das sein k�nnen?
        // Ohne Festlegung: std::any!
        std::variant<int, float, std::string> var{ 10.5f };

        std::cout
            << var.index()
            << ", value "
            << std::get<float>(var)
            << std::endl;

        var = std::string{ "Hello" }; // we're now a string

        std::cout
            << var.index()
            << ", value "
            << std::get<std::string>(var)
            << std::endl;

        var = 10; // we're now an int

        std::cout
            << var.index()
            << ", value "
            << std::get<int>(var)
            << std::endl;

        var.emplace<2>("Hello again"); // we're now a string again

        std::cout
            << var.index()
            << ", value "
            << std::get<std::string>(var)
            << std::endl;

        // std::get returns a reference, so you can change the value:

        std::get<std::string>(var) += std::string{ " World" };

        std::cout
            << var.index()
            << ", value "
            << std::get<std::string>(var)
            << std::endl;

        var = 10.1f;
        if (auto pFloat = std::get_if<float>(&var); pFloat)
            *pFloat *= 2.0f;

        std::cout
            << var.index()
            << ", value "
            << std::get<float>(var)
            << std::endl;
    }

    // -------------------------------------------------------------------

    void test_02() {

        // accessing a variant

        std::variant<int, float, std::string> var{ std::string{ "Hello" } };

        std::cout
            << var.index()
            << ", value "
            << std::get<std::string>(var)
            << std::endl;

        try
        {
            auto f = std::get<float>(var);
            std::cout << "float! " << f << "\n";
        }
        catch (std::bad_variant_access&)
        {
            std::cout << "Variant doesn't hold float at this moment ..." << std::endl;
        }

        var = 123;

        std::cout
            << var.index()
            << ", value "
            << std::get<int>(var)
            << std::endl;

        if (auto intPtr = std::get_if<0>(&var))
            std::cout << "int! => " << *intPtr << std::endl;
    }

    // -------------------------------------------------------------------

// prim�res Template
template <class T>
struct my_remove_reference {
    using type = T;
};

// Template Spezialisierung
template <>
struct my_remove_reference<int> {
    using type = int;
};

// Template Spezialisierung
template <class T>
struct my_remove_reference<T&> {
    using type = T;
};



    void test_03() {

        std::variant<int, float, std::string> var{ 3.5f };

        // using a generic visitor (matching all types in the variant)
        // Ein Lambda!
    	auto visitor = [](const auto& elem) {

            using ElemType = decltype (elem);  // ElemType ==>  int

            using ElemTypeWithoutReference =
                my_remove_reference<ElemType>::type;

            using ElemTypeWithoutReferenceAndConst =
                std::remove_const<ElemTypeWithoutReference>::type;


            // ElemTypeWithoutReference dummy{};

            // typedef decltype (elem) ElemType2;

            int n = 123;

          //  if constexpr (n == 12345)

            if constexpr ( std::is_same<ElemTypeWithoutReferenceAndConst, int>::value == true )
            {
                std::cout << "bin ein int: " << elem << std::endl;
            }
            else if constexpr (std::is_same<ElemTypeWithoutReferenceAndConst, float>::value == true) {
                std::cout << "bin ein float: " << elem << std::endl;
            }
            else if constexpr (std::is_same<ElemTypeWithoutReferenceAndConst, std::string>::value == true) {
                std::cout << "bin ein std::string: " << elem << std::endl;
                std::cout << " und bin  " << elem.size() <<  " Zeichen lang" << std::endl;
            }
            else {
                std::cout << "unbekannt ..." << elem << std::endl;
            }
        };

        std::visit(visitor, var);

        var = 10;
        std::visit(visitor, var);

        var = std::string{ "Hello" };
        std::visit(visitor, var);
    }

    // Betrachtung von Datentypen: Type Traits!
 /* void test_03b() {

        std::variant<int, float, std::string> var{ 3.5f };

        using ElemType = decltype(elem);  // z.B. int
        using ElemTypeWithoutReference = std::remove_reference<ElemType>::type;   // F�r auto&-Zugriff
        using ElemTypeWithoutRefAndConst = std::remove_const<ElemTypeWithoutReference>::type; // F�r const auto&-Zugriff

        // using a generic visitor (matching all types in the variant)
        // Ein Lambda!
        auto visitor = [](const auto& elem) {
            
            if constexpr (std::is_same<ElemTypeWithoutRefAndConst, int>::value == true) {
                std::cout << "Ich bin ein int " << elem << std::endl;
            }
            else if constexpr (std::is_same<ElemTypeWithoutRefAndConst, float>::value == true) {
                std::cout << "Ich bin ein float " << elem << std::endl;
            }
            // constexpr notwendig f�r den std::string, elem.size()-Fall, da sonst
            // f�r jeden Typ (int, float, string) jeweils eine Instanz des Lambda mit 
            // jeweils allen 3 Pfaden entstehen w�rden, wobei int und float kein size() 
            // beherrschen -> Compile-Error!
            // Mit constexpr wird zur COMPILEzeit ausgewertet, welche Pfade f�r welche
            // Instanz des jeweiligen Lambdas TATS�CHLICH notwendig sind!
            // Hiermit wird am Ende auch Maschinencode eingespart!
            //       \/
            else if constexpr (std::is_same<ElemTypeWithoutRefAndConst, std::string>::value == true) {
                std::cout << "Ich bin ein String " << elem << std::endl;
                std::cout << " und bin " << elem.size() << "Zeichen lang" << std::endl;
            }
            else
            {
                std::cout << "Unbekannt" << std::endl;
            }
        };

        std::visit(visitor, var);

        var = 10;
        std::visit(visitor, var);

        var = std::string{ "Hello" };
        std::visit(visitor, var);
    }
    */

    // -------------------------------------------------------------------

    template<typename T>
    void visitorFunction (const T& elem) {
        std::cout << elem << std::endl;
    }

    void test_04() {

        std::variant<int, float, std::string> var{ 3.5f };

        // Doesn't work:
        // std::visit requires an object,
        // and template functions aren't objects of functions:
        // std::visit(visitorFunction<float>, var);
    }

    // -------------------------------------------------------------------
    // Beste L�sung mit Fallunterscheidung: Ein Funktor!

    class Visitor
    {
    public:
        Visitor() = default;

        void operator() (int n) {
            std::cout << "int: " << n << std::endl;
        }

        void operator() (float f) {
            std::cout << "float: " << f << std::endl;
        }

        void operator() (std::string s) {
            std::cout << "std::string: " << s << std::endl;
        }
    };

    void test_05() {

        std::variant<int, float, std::string> var{ 3.5f };

        Visitor visitor{};

        std::visit(visitor, var);
        
        var = 10;
        std::visit(visitor, var);
    }

    // -------------------------------------------------------------------

    void test_06() {

        std::vector<std::variant<int, long, long long, float, double>>
            vec = { 100, 200l, 300ll, 400.5f, 500.5 };

        // display each value
        std::cout << "Values:      ";
        for (const auto& var : vec) {
            std::visit([](const auto& n) { std::cout << n << " "; }, var);
        }
        std::cout << std::endl;

        // display each type
        // C++ modules & typeid don't work
        //std::cout << "Types:       ";
        //for (const auto& var : vec) {
        //    std::visit([](const auto& arg) { std::cout << typeid(arg).name() << " "; }, var);
        //}
        //std::cout << std::endl;

        // get the sum
        // C++ modules & typeid don't work
        std::common_type<int, long, long long, float, double>::type res{};
        //std::cout << "Type of Sum: " << typeid(res).name() << std::endl;

        for (const auto& var : vec) {
            std::visit([&res](const auto& arg) { res += arg; }, var);
        }
        std::cout << "Sum:         " << res << std::endl;

        // double each value of the vector
        std::cout << "Values:      ";
        for (auto& var : vec) {
            std::visit([](auto& arg) { arg *= 2; }, var);
            std::visit([](const auto& arg) { std::cout << arg << " "; }, var);
        }
        std::cout << std::endl;
    }

    // -------------------------------------------------------------------

    template<class... Ts>
    struct Overload : Ts... { using Ts::operator()...; };
    
    template<class... Ts> Overload(Ts...) -> Overload<Ts...>;

    void test_07() {

        std::variant<int, float, std::string> intFloatString{ "Hello" };

        std::visit(Overload{
            [](const int& i) { std::cout << "int: " << i << std::endl; },
            [](const float& f) { std::cout << "float: " << f << std::endl; },
            [](const std::string& s) { std::cout << "string: " << s << std::endl; }
            },
            intFloatString
        );

        intFloatString = 123;

        std::visit(Overload{
            [](const int& i) { std::cout << "int: " << i << std::endl; },
            [](const float& f) { std::cout << "float: " << f << std::endl; },
            [](const std::string& s) { std::cout << "string: " << s << std::endl; }
            },
            intFloatString
        );
    }

    // -------------------------------------------------------------------

    void test_08() {

        std::variant<int, float, std::string> intFloatString{ "Hello" };

        Overload overloadSet {
            [](const int& i) { std::cout << "int: " << i << std::endl; },
            [](const float& f) { std::cout << "float: " << f << std::endl; },
            [](const std::string& s) { std::cout << "string: " << s << std::endl; }
        };

        std::visit(overloadSet, intFloatString);

        intFloatString = 123;

        std::visit(overloadSet, intFloatString);
    }
}

// C++-Module: K�nnte hier auch direkt mit export exportiert werden.
// Wird jedoch erst in Module_Variant.ixx exportiert, um die Entscheidung auszulagern.
void main_variant()         
{
    using namespace VariantDemo;
    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
    test_06();
    test_07();
    test_08();
}

// =====================================================================================
// End-of-File
// =====================================================================================
