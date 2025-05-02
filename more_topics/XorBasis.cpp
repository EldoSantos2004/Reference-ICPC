/*
  XOR Basis (Linear Basis over GF(2))
  ------------------------------------
  Supports insertion of numbers into a basis and querying the maximum
  XOR of any subset with a given value.

  Bit Width: up to D bits (here D = 60 for 64-bit integers)
  Indexing: basis[0] is for bit 0 (least significant), basis[D-1] for bit D-1
  Bounds:
    - Values x inserted must satisfy 0 <= x < 2^D
  Time Complexity:
    - insert(x):   O(D)
    - getMax(x):   O(D)
  Space Complexity: O(D)

  Notes:
    - We maintain one basis vector per bit position.
    - On insert, we reduce x by existing basis vectors, then store it
      in the highest bit it still has.
    - To query max XOR, we greedily try to xor with basis vectors
      from highest bit down.
*/
const int D = 31; // Maximum number of bits in the numbers
int basis[D]; // basis[i] keeps the mask of the vector whose f value is i
int sz; // Current size of the basis

void insertVector(int mask) {
  //turn for around if you want max xor
	for (int i = 0; i < D; i++) {
		if ((mask & 1 << i) == 0) continue; // continue if i != f(mask)
		if (!basis[i]) { // If there is no basis vector with the ith bit set, then insert this vector into the basis
			basis[i] = mask;
			++sz;
			return;
		}
		mask ^= basis[i]; // Otherwise subtract the basis vector from this vector
	}
}

// V2: If you dont need the basis sorted.
vector<ll> basis;
void add(ll x)
{
  for (int i = 0; i < basis.size(); i++)
  {
    x = min(x, x ^ basis[i]);
  }
  if (x != 0)
  {
    basis.pb(x);
  }
}
