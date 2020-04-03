#include<cmath>

#ifndef MATRIX_FINITE_H
#define MATRIX_FINITE_H

template <unsigned int P, unsigned int n>
struct primeCheckNumbersLessN {
    static const bool is_prime = static_cast<bool>(1 / (P % n) + 1) && primeCheckNumbersLessN<P, n - 2>::is_prime;
};
template <unsigned int P>
struct primeCheckNumbersLessN<P, 3> {
    static const bool is_prime = static_cast<bool>(1 / (P % 3) + 1) && static_cast<bool>(1 / (P % 2) + 1);
};
template <unsigned int P>
struct primeCheckNumbersLessN<P, 0> {
    static const bool is_prime = true;
};

template <unsigned int P>
struct prime {
    static const bool is_prime = primeCheckNumbersLessN<P, static_cast<unsigned int>(sqrt(P))>::is_prime;
};

template <unsigned int N>
class Finite {
private:
    long long k_;

public:
    Finite();
    Finite(int k);
    Finite(size_t k);
    Finite(long long k);
    Finite(const Finite<N>& fin);
    Finite<N>& operator=(const Finite<N>& fin);
    Finite<N>& operator=(int fin);

    Finite<N> operator-() const;

    Finite<N>& operator++();
    Finite<N>& operator--();
    Finite<N>  operator++(int);
    Finite<N>  operator--(int);

    Finite<N>& operator+=(const Finite<N>& fin);
    Finite<N>& operator-=(const Finite<N>& fin);
    Finite<N>& operator*=(const Finite<N>& fin);
    Finite<N>& operator/=(const Finite<N>& fin);

    Finite<N> operator+(const Finite<N>& fin) const;
    Finite<N> operator-(const Finite<N>& fin) const;
    Finite<N> operator*(const Finite<N>& fin) const;
    Finite<N> operator/(const Finite<N>& fin) const;

    bool operator==(const Finite<N>& fin) const;
    bool operator!=(const Finite<N>& fin) const;

    Finite<N> pow(int deg) const;

    Finite<N> inverse() const;

    template <unsigned int M>
    friend std::ostream& operator<<(std::ostream &out, const Finite<M>& fin);
    template <unsigned int M>
    friend std::istream& operator>>(std::istream &in, Finite<M>& fin);

    void print() const;
};

template<unsigned int N>
Finite<N>::Finite(): k_(0) {}
template<unsigned int N>
Finite<N>::Finite(int k) {
    k_ = k % static_cast<int>(N);
    if (k_ < 0) k_ = k_ + N;
}

template<unsigned int N>
Finite<N>::Finite(size_t k): k_(k) {
    k_ = k % static_cast<size_t>(N);
}
template<unsigned int N>
Finite<N>::Finite(long long k) {
    k_ = k % static_cast<long long>(N);
    if (k_ < 0) {
        k_ = k_ + N;
    }
}
template<unsigned int N>
Finite<N>::Finite(const Finite<N>& fin): k_(fin.k_) {}

template<unsigned int N>
Finite<N>& Finite<N>::operator=(const Finite<N>& fin) {
    k_ = fin.k_;
    return *this;
}
template<unsigned int N>
Finite<N>& Finite<N>::operator=(int fin) {
    Finite<N> Fin(fin);
    *this = Fin;
    return *this;
}

template<unsigned int N>
std::ostream& operator<<(std::ostream &out, const Finite<N>& fin) {
    out << fin.k_;
    return out;
}
template<unsigned int N>
std::istream& operator>>(std::istream &in, Finite<N>& fin) {
    int inp;
    in >> inp;
    fin(inp);

    return in;
}

template<unsigned int N>
Finite<N> Finite<N>::operator-() const {
    return Finite<N>(-k_);
}

template<unsigned int N>
Finite<N>& Finite<N>::operator++() {
    return *this += 1;
}
template<unsigned int N>
Finite<N>& Finite<N>::operator--() {
    return *this -= 1;
}
template<unsigned int N>
Finite<N> Finite<N>::operator++(int) {
    Finite<N> Copy = *this;
    Copy += 1;
    return Copy;
}
template<unsigned int N>
Finite<N> Finite<N>::operator--(int) {
    Finite<N> Copy = *this;
    Copy -= 1;
    return Copy;
}

template<unsigned int N>
Finite<N>& Finite<N>::operator+=(const Finite<N>& fin) {
    k_ += fin.k_;
    if (k_ >= static_cast<int>(N)) {
        k_ -= N;
    }

    return *this;
}
template<unsigned int N>
Finite<N>& Finite<N>::operator-=(const Finite<N>& fin) {
    std::cout << fin.k_ << k_;
    return *this += -fin;
}
template<unsigned int N>
Finite<N>& Finite<N>::operator*=(const Finite<N>& fin) {
    k_ *= fin.k_;
    k_ %= N;

    return *this;
}
template<unsigned int N>
Finite<N>& Finite<N>::operator/=(const Finite<N>& fin) {
    *this *= fin.inverse();

    return *this;
}

template<unsigned int N>
bool Finite<N>::operator==(const Finite<N>& fin) const {
    return (k_ == fin.k_);
}
template<unsigned int N>
bool Finite<N>::operator!=(const Finite<N>& fin) const {
    return (k_ != fin.k_);
}

template<unsigned int N>
Finite<N> Finite<N>::operator+(const Finite<N>& fin) const {
    Finite<N> Result = *this;
    Result += fin;
    return Result;
}
template<unsigned int N>
Finite<N> Finite<N>::operator-(const Finite<N>& fin) const {
    Finite<N> Result = *this;
    Result -= fin;
    return Result;
}
template<unsigned int N>
Finite<N> Finite<N>::operator*(const Finite<N>& fin) const {
    Finite<N> Result = *this;
    Result *= fin;
    return Result;
}

template<unsigned int N>
Finite<N> Finite<N>::operator/(const Finite<N>& fin) const {
    Finite<N> Result = *this;
    Result /= fin;
    return Result;
}

template<unsigned int N>
Finite<N> Finite<N>::pow(int deg) const {
    Finite<N> Result (1);
    Finite<N> t = *this;

    for (; deg > 0; deg /= 2) {
        if (deg%2 == 1) {
            Result *= t;
        }
        t *= t;
    }

    return Result;
}

template<unsigned int N>
Finite<N> Finite<N>::inverse() const {
    Finite<N> Result = *this;
    if (prime<N>::is_prime) {
        Result = Result.pow(N - 2);
    }

    return Result;
}

template<unsigned int N>
void Finite<N>::print() const{
    printf("%lld", k_);
}

#endif //MATRIX_FINITE_H