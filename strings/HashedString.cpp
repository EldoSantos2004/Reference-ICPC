
/*
                                        Hashed string
  ----------------------------------------------------------------
  Class for hashing string. Allows retrieval of hashes of any substring in the string.

	Double hash or use big mod values to avoid problems with collisions

	Time Complexity(Construction): O(n)
  Space Complexity: O(n)
*/

const ll MOD = 212345678987654321LL;
const ll base = 33;

class HashedString {
  private:
	// change M and B if you want
	static const long long M = 1e9 + 9;
	static const long long B = 9973;

	// pow[i] contains B^i % M
	static vector<long long> pow;

	// p_hash[i] is the hash of the first i characters of the given string
	vector<long long> p_hash;

  public:
	HashedString(const string &s) : p_hash(s.size() + 1) {
		while (pow.size() < s.size()) { pow.push_back((pow.back() * B) % M); }

		p_hash[0] = 0;
		for (int i = 0; i < s.size(); i++) {
			p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
		}
	}

	// Returns hash of substring [start, end]
	long long get_hash(int start, int end) {
		long long raw_val =
		    (p_hash[end + 1] - (p_hash[start] * pow[end - start + 1]));
		return (raw_val % M + M) % M;
	}
};
// you cant skip this
vector<long long> HashedString::pow = {1};
