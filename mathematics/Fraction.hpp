#pragma once
#include <bits/stdc++.h>

class Fraction {
    using ll = long long;
    using i128 = __int128_t;
    ll n_, d_;

    void set(i128 n, i128 d) {
        if (d == 0) throw std::invalid_argument("zero denominator");
        if (d < 0) { n = -n; d = -d; }
        i128 a = n < 0 ? -n : n, b = d;
        while (b) { i128 r = a % b; a = b; b = r; }
        n /= a;
        d /= a;
        if (n < std::numeric_limits<ll>::min() ||
            n > std::numeric_limits<ll>::max() ||
            d > std::numeric_limits<ll>::max())
            throw std::overflow_error("fraction overflow");
        n_ = (ll)n;
        d_ = (ll)d;
    }
    static Fraction make(i128 n, i128 d) {
        Fraction f;
        f.set(n, d);
        return f;
    }

public:
    // Always reduced, positive denominator; zero is 0/1.
    Fraction(ll n = 0, ll d = 1) { set(n, d); }
    ll num() const { return n_; }
    ll den() const { return d_; }

    friend Fraction operator+(const Fraction& a, const Fraction& b) {
        return make((i128)a.n_ * b.d_ + (i128)b.n_ * a.d_,
                    (i128)a.d_ * b.d_);
    }
    friend Fraction operator-(const Fraction& a, const Fraction& b) {
        return make((i128)a.n_ * b.d_ - (i128)b.n_ * a.d_,
                    (i128)a.d_ * b.d_);
    }
    friend Fraction operator*(const Fraction& a, const Fraction& b) {
        return make((i128)a.n_ * b.n_, (i128)a.d_ * b.d_);
    }
    friend Fraction operator/(const Fraction& a, const Fraction& b) {
        if (b.n_ == 0) throw std::domain_error("divide by zero");
        return make((i128)a.n_ * b.d_, (i128)a.d_ * b.n_);
    }
    Fraction operator-() const { return make(-(i128)n_, d_); }
    Fraction& operator+=(const Fraction& b) { return *this = *this + b; }
    Fraction& operator-=(const Fraction& b) { return *this = *this - b; }
    Fraction& operator*=(const Fraction& b) { return *this = *this * b; }
    Fraction& operator/=(const Fraction& b) { return *this = *this / b; }

    friend bool operator==(const Fraction& a, const Fraction& b) {
        return a.n_ == b.n_ && a.d_ == b.d_;
    }
    friend bool operator<(const Fraction& a, const Fraction& b) {
        return (i128)a.n_ * b.d_ < (i128)b.n_ * a.d_;
    }
    friend bool operator!=(const Fraction& a, const Fraction& b) {
        return !(a == b);
    }
    friend bool operator>(const Fraction& a, const Fraction& b) {
        return b < a;
    }
    friend bool operator<=(const Fraction& a, const Fraction& b) {
        return !(b < a);
    }
    friend bool operator>=(const Fraction& a, const Fraction& b) {
        return !(a < b);
    }
    explicit operator long double() const {
        return (long double)n_ / d_;
    }
    friend std::ostream& operator<<(std::ostream& out,
                                    const Fraction& f) {
        return out << f.n_ << '/' << f.d_;
    }
};
