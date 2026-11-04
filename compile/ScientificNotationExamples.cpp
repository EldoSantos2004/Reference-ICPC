// C++17. Scientific notation is coefficient * 10^exponent.
#include <bits/stdc++.h>
using namespace std;

int main() {
    double a = 1e3;       // 1 * 10^3 = 1000; type is double.
    double b = 2.5e-3;    // 2.5 * 10^-3 = 0.0025.
    double c = -4.2E+2;   // -4.2 * 10^2 = -420; E also works.
    long double eps = 1e-9L; // L selects long double; f selects float.
    cout << "literals: " << a << ' ' << b << ' ' << c << '\n';
    // 1000 0.0025 -420
    cout << "long double literal: " << scientific << setprecision(2);
    cout << eps << '\n'; // 1.00e-09
    cout << defaultfloat << setprecision(6);

    // Exact integer constants should use integer literals.
    const long long LIMIT = 1000000000LL;
    const long long LARGE = 1000000000000000001LL;
    cout << "integer constants: " << LIMIT << ' ' << LARGE << '\n';
    // 1000000000 1000000000000000001
    // 1e9 is a double even without a decimal point.
    // Large floating-point values can lose integer precision.
    // 10 ^ 3 is bitwise XOR in C++, not exponentiation; 1e3 means 1000.

    // Streams and stod/stold understand exponents when reading floats.
    istringstream input("1e3 2.5e-3 -4.2E+2");
    double x, y, z;
    input >> x >> y >> z;
    cout << "parsed input: " << x << ' ' << y << ' ' << z << '\n';
    // 1000 0.0025 -420
    cout << "stod: " << stod("2.5e3") << '\n'; // 2500
    // Integer parsers do not read the exponent: check the consumed length.
    size_t used = 0;
    long long prefix = stoll("1e3", &used);
    cout << "stoll prefix: " << prefix << " consumed " << used << '\n';
    // 1 consumed 1; this is NOT a way to parse the integer 1000.

    double value = 12345.6789;
    auto old_flags = cout.flags();
    auto old_precision = cout.precision();
    cout << "scientific p3: " << scientific << setprecision(3);
    cout << value << '\n'; // 1.235e+04 (3 fractional digits)
    cout << "uppercase p2: " << uppercase << setprecision(2);
    cout << value << '\n'; // 1.23E+04
    cout << "fixed p2: " << nouppercase << fixed << setprecision(2);
    cout << value << '\n'; // 12345.68 (2 fractional digits)
    cout << "defaultfloat p6: " << defaultfloat << setprecision(6);
    cout << value << '\n'; // 12345.7 (6 significant digits)
    // Formatting changes only the printed representation, not value.
    // Flags and precision persist; restore both when needed.
    cout.flags(old_flags);
    cout.precision(old_precision);
    cout << "restored: " << value << '\n'; // 12345.7

    // printf: %e/%E take double; %Le/%LE take long double.
    // Do not use %e for long double (or %Le for double).
    printf("printf p3: %.3e\n", value); // 1.235e+04
    printf("printf upper p2: %.2E\n", value); // 1.23E+04
    long double large_value = 12345.6789L;
    printf("printf long double p2: %.2Le\n", large_value); // 1.23e+04
    // This program keeps the default iostream/stdio synchronization.
}
