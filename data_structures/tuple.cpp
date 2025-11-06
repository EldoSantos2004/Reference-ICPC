#include <tuple>
#include <iostream>
#include <string>

int main() {
    // ------------------------------
    // DECLARING A TUPLE
    // ------------------------------
    std::tuple<int, double, std::string> t1;

    // ------------------------------
    // INITIALIZING A TUPLE
    // ------------------------------
    std::tuple<int, double, std::string> t2(42, 3.14, "hello");

    // ------------------------------
    // USING std::make_tuple
    // (automatic type deduction)
    // ------------------------------
    auto t3 = std::make_tuple(7, 2.71, "world");

    // ------------------------------
    // ACCESSING ELEMENTS USING std::get
    // ------------------------------
    int a = std::get<0>(t2);        // a = 42
    double b = std::get<1>(t2);     // b = 3.14
    std::string c = std::get<2>(t2); // c = "hello"

    // ------------------------------
    // MODIFYING ELEMENTS
    // ------------------------------
    std::get<1>(t2) = 5.67; // change second element

    // ------------------------------
    // STRUCTURED BINDINGS (C++17)
    // Unpacks the tuple into variables
    // ------------------------------
    auto [x, y, z] = t3;  // x=7, y=2.71, z="world"

    // ------------------------------
    // tuple_size and tuple_element
    // (using decltype to reference the type)
    // ------------------------------
    std::size_t n = std::tuple_size<decltype(t3)>::value; // n = 3
    using FirstType = std::tuple_element<0, decltype(t3)>::type; 
    // FirstType is int

    // ------------------------------
    // SMALL EXAMPLE OF USE
    // ------------------------------
    auto person = std::make_tuple("Alice", 25, 1.70);

    // Access values
    std::cout << "Name: "  << std::get<0>(person) << "\n";
    std::cout << "Age: "   << std::get<1>(person) << "\n";
    std::cout << "Height: "<< std::get<2>(person) << "\n";

    // Modify a value
    std::get<1>(person) = 26;

    // Print updated value
    std::cout << "Updated age: " << std::get<1>(person) << "\n";

    return 0;
}
