//to avoid hacks
mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
//you can also just write seed_value if hacks are not an issue

// rng() for generating random numbers between 0 and 2<<31-1

// for generating numbers with uniform probability in range
uniform_int_distribution<int> rng(0, numeric_limits<int>::max());

// then for generating random values just do 
int random_value = rng(mt);


std::normal_distribution<> normal_dist(mean, 2)
exponential_distribution

// for shuffling array
shuffle(permutation.begin(), permutation.end(), rng);
