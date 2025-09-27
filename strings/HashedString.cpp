
/*
                                        Hashed string
  ----------------------------------------------------------------
  Class for hashing string. Allows retrieval of hashes of any substring in the string.

	Double hash or use big mod values to avoid problems with collisions

	Important to take into account that the values used for the letters are not 0 to 26. it is ascii characters.

	Time Complexity(Construction): O(n)
  Space Complexity: O(n)
*/

const ll MOD = 212345678987654321LL;
const ll base = 33;

class HashedString {
  private:
	static const long long M = 1e9 + 9;
	static const long long B = 9973;

	static vector<long long> pow;

	vector<long long> p_hash;

  public:
	HashedString(const string &s) : p_hash(s.size() + 1) {
		while (pow.size() <= s.size()) { pow.push_back((pow.back() * B) % M); }

		p_hash[0] = 0;
		for (int i = 0; i < (int)s.size(); i++) {
			p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
		}
	}
	// substring [start, end]
	long long get_hash(int start, int end) {
		long long raw_val =
		    (p_hash[end + 1] - (p_hash[start] * pow[end - start + 1]));
		return (raw_val % M + M) % M;
	}
  	// substring [start, end] with l added at the end. Remember it is ascii characters, not the number from 1 to 26 for the hash.
    long long get_hash(int start, int end, int l){
      if(start > end) return l;
      long long val = (p_hash[end + 1] - (p_hash[start] * pow[end - start + 1]));
     val = (val % M + M) % M;
      val = (val + l) % mod;
      return val;
    }
};
// you cant skip this
vector<long long> HashedString::pow = {1};


