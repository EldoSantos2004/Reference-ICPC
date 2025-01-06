// count the number of set bits in an integer
#pragma GCC target("popcnt")
(int) __builtin_popcount(x);
(int) __builtin_popcountll(x);
__builtin_clz(x); // count leading zeros

// declare bitset 
bitset<64> b;

// count set bits in bitser
b.count();