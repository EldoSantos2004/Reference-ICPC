bitset<3001> b[3001];

//set() Set the bit value at the given index to 1.
//count() Count the number of set bits.
//any() Checks if any bit is set
//all() Check if all bit is set.
// count the number of set bits in an integer

#pragma GCC target("popcnt")
(int) __builtin_popcount(x);
(int) __builtin_popcountll(x);
__builtin_clz(x); // count leading zeros

// declare bitset 
bitset<64> b;

// count set bits in bitser
b.count();