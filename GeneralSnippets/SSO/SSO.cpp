// =====================================================================================
// SSO.cpp // SSO (Small String Optimization)
// =====================================================================================

module modern_cpp:sso;

void main_sso()
{
    auto size = sizeof(std::string);            // 40
    auto capacity = std::string{}.capacity();   // 15       // Interner Puffer von 15
    auto small = std::string(capacity, '*');    // 15       // Interner Puffer 100 % voll -> weiterhin im Puffer!
    auto big = std::string(capacity + 1, '#');  // 31       // Interner Puffer + 1        -> Ab jetzt auf dem HEAP

    std::cout << "sizeof  : " << size << std::endl;
    std::cout << "Capacity: " << capacity << std::endl;
    std::cout << "Small   : " << small.capacity() << ": " << small << std::endl;
    std::cout << "Big     : " << big.capacity() << ": " << big << std::endl;
}

// =====================================================================================
// End-of-File
// =====================================================================================
