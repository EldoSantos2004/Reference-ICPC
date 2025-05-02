bitset<3001> b[3001];

//set() Set the bit value at the given index to 1.
//reset() Set the bit value at the given index to 0.
//flip() Toggle the bit value at the given index.
//test() Check if the bit value at the given index is 1 or 0.
//count() Count the number of set bits.
//any() Checks if any bit is set
//all() Check if all bit is set.
//none() Check if no bit is set.
//to_string() Convert the bitset to a string representation.

#pragma GCC target("popcnt")
(int) __builtin_popcount(x);
(int) __builtin_popcountll(x);
__builtin_clz(x); // count leading zeros

// declare bitset 
bitset<64> b;
