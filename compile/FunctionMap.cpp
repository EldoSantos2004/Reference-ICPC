#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    map<char, function<ll(ll, ll)>> operation{
        {'+', [](ll a, ll b) { return a + b; }},
        {'*', [](ll a, ll b) { return a * b; }}
    };

    cout << operation.at('+')(3, 4) << '\n'; // 7
    cout << operation.at('*')(3, 4) << '\n'; // 12
}
