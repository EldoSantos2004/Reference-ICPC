// C++17. Replace each istringstream with cin for keyboard/judge input.
#include <bits/stdc++.h>
using namespace std;

int main() {
    // >> reads one token and skips leading whitespace.
    istringstream words("  red blue\n");
    string first, second;
    words >> first >> second;
    cout << "tokens: " << quoted(first) << ' '
         << quoted(second) << '\n';
    // tokens: "red" "blue"

    // getline removes '\n', preserves spaces, and accepts empty lines.
    // The last line below has no final newline; it is still read.
    istringstream lines("  Alice Smith  \n\nBob Jones");
    string line;
    int row = 0;
    while (getline(lines, line)) {
        cout << "line " << ++row << ": " << quoted(line) << '\n';
    }
    // line 1: "  Alice Smith  "
    // line 2: ""
    // line 3: "Bob Jones"
    // Use while (getline(...)), not while (!stream.eof()).

    // Mixing >> and getline: discard the REST of the count's line.
    istringstream names("2   \nAda Lovelace\nAlan Turing\n");
    int n;
    names >> n;
    names.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < n && getline(names, line); ++i) {
        cout << "name: " << quoted(line) << '\n';
    }
    // name: "Ada Lovelace"
    // name: "Alan Turing"
    // Without ignore, the first getline would read "   ".
    // ignore() alone discards just ONE character, not the whole line.

    // ws skips ALL leading whitespace, including blank lines.
    istringstream padded("\n   \n  Grace Hopper  \n");
    getline(padded >> ws, line);
    cout << "with ws: " << quoted(line) << '\n';
    // with ws: "Grace Hopper  " (trailing spaces remain).
    // Do not use ws when leading spaces or empty lines matter.

    // Parse a whole line separately with istringstream.
    istringstream data("10 20 30\n7 8\n");
    while (getline(data, line)) {
        istringstream fields(line);
        int x, sum = 0;
        while (fields >> x) sum += x;
        cout << "sum: " << sum << '\n';
    }
    // sum: 60
    // sum: 15

    // A custom delimiter also works. This is not a quoted-CSV parser.
    istringstream separated("red,,blue");
    string field;
    while (getline(separated, field, ',')) {
        cout << "field: " << quoted(field) << '\n';
    }
    // field: "red"
    // field: ""
    // field: "blue"
    // No extra field is read after a trailing delimiter.

    // >> char skips whitespace; get(char&) reads even spaces/newlines.
    istringstream chars(" A");
    char ch;
    chars.get(ch);
    cout << "get: " << quoted(string(1, ch)) << '\n'; // get: " "
    chars >> ch;
    cout << ">> char: " << quoted(string(1, ch)) << '\n'; // "A"
}
