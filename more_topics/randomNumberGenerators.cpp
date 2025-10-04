//to avoid hacks
mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
//you can also just write seed_value if hacks are not an issue

// rng() for generating random numbers between 0 and 2<<31-1

// for generating numbers with uniform probability in range
uniform_int_distribution<int> rng(0, numeric_limits<int>::max());

// then for generating random values just do 
int random_value = rng(mt);

// if you do not want to create variable
uniform_int_distribution<int>(0, n)(mt)

// other distributions
// Normal distribution: mean = 0.0, stddev = 1.0
normal_distribution<double> normal_dist(0.0, 1.0);

// Exponential distribution: lambda = 1.5
exponential_distribution<double> exp_dist(1.5);

// for shuffling array
shuffle(permutation.begin(), permutation.end(), rng);
