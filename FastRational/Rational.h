//
// Created by aleks311001 on 20.03.2020.
//
#include "BigInteger.h"

#ifndef FASTRATIONAL_RATIONAL_H
#define FASTRATIONAL_RATIONAL_H

class Rational{
public:
    Rational();
    Rational(int Int);
    Rational(const BigInteger& BInt);

    Rational(const Rational& Rat);

    Rational& operator=(const Rational& Rat);
    Rational& operator=(const BigInteger& BInt);
    Rational& operator=(const int& Int);

    Rational operator-() const;

    Rational& operator+=(const Rational& Rat);
    Rational& operator-=(const Rational& Rat);
    Rational& operator*=(const Rational& Rat);
    Rational& operator/=(const Rational& Rat);

    Rational& operator+=(const BigInteger& BInt);
    Rational& operator-=(const BigInteger& BInt);
    Rational& operator*=(const BigInteger& BInt);
    Rational& operator/=(const BigInteger& BInt);

    Rational& operator+=(const int& Int);
    Rational& operator-=(const int& Int);
    Rational& operator*=(const int& Int);
    Rational& operator/=(const int& Int);

    Rational operator+(const Rational& Rat) const;
    Rational operator-(const Rational& Rat) const;
    Rational operator*(const Rational& Rat) const;
    Rational operator/(const Rational& Rat) const;

    Rational operator+(const BigInteger& BInt) const;
    Rational operator-(const BigInteger& BInt) const;
    Rational operator*(const BigInteger& BInt) const;
    Rational operator/(const BigInteger& BInt) const;

    Rational operator+(const int& Int) const;
    Rational operator-(const int& Int) const;
    Rational operator*(const int& Int) const;
    Rational operator/(const int& Int) const;

    bool operator==(const Rational& Rat) const;
    bool operator!=(const Rational& Rat) const;
    bool operator>=(const Rational& Rat) const;
    bool operator<=(const Rational& Rat) const;
    bool operator>(const Rational& Rat) const;
    bool operator<(const Rational& Rat) const;

    bool operator==(const BigInteger& BInt) const;
    bool operator!=(const BigInteger& BInt) const;
    bool operator>=(const BigInteger& BInt) const;
    bool operator<=(const BigInteger& BInt) const;
    bool operator>(const BigInteger& BInt) const;
    bool operator<(const BigInteger& BInt) const;

    bool operator==(const int& Int) const;
    bool operator!=(const int& Int) const;
    bool operator>=(const int& Int) const;
    bool operator<=(const int& Int) const;
    bool operator>(const int& Int) const;
    bool operator<(const int& Int) const;

    std::string toString() const;
    std::string asDecimal(size_t precision = 0) const;
    void fromString(const std::string& str);

    operator double() const;
    friend std::ostream& operator<<(std::ostream &out, const Rational& Rat);
    friend std::istream& operator>>(std::istream &in, Rational& Rat);
private:
    BigInteger numerator_;
    BigInteger denominator_;
    void VzPrime();
};

Rational::Rational(): numerator_(0), denominator_(1) {}
Rational::Rational(int Int): numerator_(Int), denominator_(1) {
    if (Int == 0) {
        denominator_ = 1;
    }
}
Rational::Rational(const BigInteger& BInt): numerator_(BInt), denominator_(1) {
    if (BInt == 0) {
        denominator_ = 1;
    }
}

Rational::Rational(const Rational& Rat) {
    numerator_ = Rat.numerator_;
    denominator_ = Rat.denominator_;
}

Rational& Rational::operator=(const Rational& Rat) {
    numerator_ = Rat.numerator_;
    denominator_ = Rat.denominator_;
    return *this;
}
Rational& Rational::operator=(const BigInteger& BInt) {
    numerator_ = BInt;
    denominator_ = 1;
    return *this;
}
Rational& Rational::operator=(const int& Int) {
    numerator_ = Int;
    denominator_ = 1;
    return *this;
}

void Rational::VzPrime() {
    BigInteger GCD = numerator_.BinaryGCD(denominator_);
    numerator_ /= GCD;
    denominator_ /= GCD;
}

Rational Rational::operator-() const {
    Rational Result;
    Result.numerator_ = -numerator_;
    Result.denominator_ = denominator_;
    return Result;
}

Rational& Rational::operator+=(const Rational& Rat) {
    numerator_ = numerator_ * Rat.denominator_ + Rat.numerator_ * denominator_;
    denominator_ *= Rat.denominator_;

    VzPrime();
    return *this;
}
Rational& Rational::operator-=(const Rational& Rat) {
    *this += -Rat;
    return *this;
}
Rational& Rational::operator*=(const Rational& Rat) {
    numerator_ *= Rat.numerator_;
    denominator_ *= Rat.denominator_;

    VzPrime();
    return *this;
}
Rational& Rational::operator/=(const Rational& Rat) {
    numerator_ *= Rat.denominator_;
    denominator_ *= Rat.numerator_;
    if (denominator_ < 0) {
        denominator_ = -denominator_;
        numerator_ = -numerator_;
    }

    VzPrime();
    return *this;
}

Rational& Rational::operator+=(const BigInteger& BInt) {
    Rational Rat(BInt);
    return *this += Rat;
}
Rational& Rational::operator-=(const BigInteger& BInt) {
    Rational Rat(BInt);
    return *this -= Rat;
}
Rational& Rational::operator*=(const BigInteger& BInt) {
    Rational Rat(BInt);
    return *this *= Rat;
}
Rational& Rational::operator/=(const BigInteger& BInt) {
    Rational Rat(BInt);
    return *this /= Rat;
}

Rational& Rational::operator+=(const int& Int) {
    Rational Rat(Int);
    return *this += Rat;
}
Rational& Rational::operator-=(const int& Int) {
    Rational Rat(Int);
    return *this -= Rat;
}
Rational& Rational::operator*=(const int& Int) {
    Rational Rat(Int);
    return *this *= Rat;
}
Rational& Rational::operator/=(const int& Int) {
    Rational Rat(Int);
    return *this /= Rat;
}

Rational Rational::operator+(const Rational& Rat) const {
    Rational Result = *this;
    Result += Rat;
    return Result;
}
Rational Rational::operator-(const Rational& Rat) const {
    Rational Result = *this;
    Result -= Rat;
    return Result;
}
Rational Rational::operator*(const Rational& Rat) const {
    Rational Result = *this;
    Result *= Rat;
    return Result;
}
Rational Rational::operator/(const Rational& Rat) const {
    Rational Result = *this;
    Result /= Rat;
    return Result;
}

Rational Rational::operator+(const BigInteger& BInt) const {
    Rational Rat(BInt);
    return *this + Rat;
}
Rational Rational::operator-(const BigInteger& BInt) const {
    Rational Rat(BInt);
    return *this - Rat;
}
Rational Rational::operator*(const BigInteger& BInt) const {
    Rational Rat(BInt);
    return *this * Rat;
}
Rational Rational::operator/(const BigInteger& BInt) const {
    Rational Rat(BInt);
    return *this / Rat;
}

Rational Rational::operator+(const int& Int) const {
    Rational Rat(Int);
    return *this + Rat;
}
Rational Rational::operator-(const int& Int) const {
    Rational Rat(Int);
    return *this - Rat;
}
Rational Rational::operator*(const int& Int) const {
    Rational Rat(Int);
    return *this * Rat;
}
Rational Rational::operator/(const int& Int) const {
    Rational Rat(Int);
    return *this / Rat;
}

Rational operator+(const BigInteger& BInt, const Rational& Rat2) {
    Rational Rat(BInt);
    return Rat + Rat2;
}
Rational operator-(const BigInteger& BInt, const Rational& Rat2) {
    Rational Rat(BInt);
    return Rat - Rat2;
}
Rational operator*(const BigInteger& BInt, const Rational& Rat2) {
    Rational Rat(BInt);
    return Rat * Rat2;
}
Rational operator/(const BigInteger& BInt, const Rational& Rat2) {
    Rational Rat(BInt);
    return Rat / Rat2;
}

Rational operator+(const int& Int, const Rational& Rat2) {
    Rational Rat(Int);
    return Rat + Rat2;
}
Rational operator-(const int& Int, const Rational& Rat2) {
    Rational Rat(Int);
    return Rat - Rat2;
}
Rational operator*(const int& Int, const Rational& Rat2) {
    Rational Rat(Int);
    return Rat * Rat2;
}
Rational operator/(const int& Int, const Rational& Rat2) {
    Rational Rat(Int);
    return Rat / Rat2;
}

bool Rational::operator==(const Rational& Rat) const {
    return (numerator_ == Rat.numerator_ && denominator_ == Rat.denominator_);
}
bool Rational::operator!=(const Rational& Rat) const {
    return !(*this == Rat);
}
bool Rational::operator>=(const Rational& Rat) const {
    return !(*this < Rat);
}
bool Rational::operator<=(const Rational& Rat) const {
    return !(*this > Rat);
}
bool Rational::operator>(const Rational& Rat) const {
    return (numerator_ * Rat.denominator_ > Rat.numerator_ * denominator_);
}
bool Rational::operator<(const Rational& Rat) const {
    return (Rat > *this);
}

bool Rational::operator==(const BigInteger& BInt) const {
    Rational Rat(BInt);
    return (*this == Rat);
}
bool Rational::operator!=(const BigInteger& BInt) const {
    Rational Rat(BInt);
    return (*this != Rat);
}
bool Rational::operator>=(const BigInteger& BInt) const {
    Rational Rat(BInt);
    return (*this >= Rat);
}
bool Rational::operator<=(const BigInteger& BInt) const {
    Rational Rat(BInt);
    return (*this <= Rat);
}
bool Rational::operator>(const BigInteger& BInt) const {
    Rational Rat(BInt);
    return (*this > Rat);
}
bool Rational::operator<(const BigInteger& BInt) const {
    Rational Rat(BInt);
    return (*this < Rat);
}

bool operator==(const BigInteger& BInt, const Rational& Rat2) {
    Rational Rat(BInt);
    return Rat == Rat2;
}
bool operator!=(const BigInteger& BInt, const Rational& Rat2) {
    Rational Rat(BInt);
    return Rat != Rat2;
}
bool operator>=(const BigInteger& BInt, const Rational& Rat2) {
    Rational Rat(BInt);
    return Rat >= Rat2;
}
bool operator<=(const BigInteger& BInt, const Rational& Rat2) {
    Rational Rat(BInt);
    return Rat <= Rat2;
}
bool operator>(const BigInteger& BInt, const Rational& Rat2) {
    Rational Rat(BInt);
    return Rat > Rat2;
}
bool operator<(const BigInteger& BInt, const Rational& Rat2) {
    Rational Rat(BInt);
    return Rat < Rat2;
}

bool Rational::operator==(const int& Int) const {
    Rational Rat(Int);
    return (*this == Rat);
}
bool Rational::operator!=(const int& Int) const {
    Rational Rat(Int);
    return (*this != Rat);
}
bool Rational::operator>=(const int& Int) const {
    Rational Rat(Int);
    return (*this >= Rat);
}
bool Rational::operator<=(const int& Int) const {
    Rational Rat(Int);
    return (*this <= Rat);
}
bool Rational::operator>(const int& Int) const {
    Rational Rat(Int);
    return (*this > Rat);
}
bool Rational::operator<(const int& Int) const {
    Rational Rat(Int);
    return (*this < Rat);
}

bool operator==(const int& Int, const Rational& Rat2) {
    Rational Rat(Int);
    return Rat == Rat2;
}
bool operator!=(const int& Int, const Rational& Rat2) {
    Rational Rat(Int);
    return Rat != Rat2;
}
bool operator>=(const int& Int, const Rational& Rat2) {
    Rational Rat(Int);
    return Rat >= Rat2;
}
bool operator<=(const int& Int, const Rational& Rat2) {
    Rational Rat(Int);
    return Rat <= Rat2;
}
bool operator>(const int& Int, const Rational& Rat2) {
    Rational Rat(Int);
    return Rat > Rat2;
}
bool operator<(const int& Int, const Rational& Rat2) {
    Rational Rat(Int);
    return Rat < Rat2;
}

std::ostream& operator<<(std::ostream &out, const Rational& Rat) {
    out << Rat.asDecimal(8);
    return out;
}
std::istream& operator>>(std::istream &in, Rational& Rat) {
    std::string str;
    in >> str;
    Rat.fromString(str);

    return in;
}

void Rational::fromString(const std::string& str) {
    size_t dot = 0;
    size_t e = 0;
    size_t num_of_nulls_after_dot = 0;
    for (; dot < str.size(); ++dot) {
        if (str[dot] == '.' || str[dot] == ','){
            break;
        }
    }
    bool was_only_null = true;
    for (e = dot + 1; e < str.size(); ++e) {
        if (str[e] == 'e' || str[e] == 'E') {
            break;
        }
        if (str[e] == '0') {
            if (was_only_null) {
                ++num_of_nulls_after_dot;
            }
        } else {
            was_only_null = false;
        }
    }

    int degreeTen = 0;
    numerator_.fromString(str.substr(0, dot));
    BigInteger afterDot = 0;
    if (dot + 1 < str.size()) {
        afterDot.fromString(str.substr(dot + 1, e - dot - 1));
    }
    if (e + 1 < str.size()) {
        degreeTen = stoi(str.substr(e + 1));
    }

    denominator_.fromString('1' + std::string(afterDot.size() + num_of_nulls_after_dot, '0'));
    numerator_ *= denominator_;
    numerator_ += afterDot;

    BigInteger TEN;
    if (degreeTen < 0) {
        TEN.fromString('1' + std::string(-degreeTen, '0'));
        denominator_ *= TEN;
    } else {
        TEN.fromString('1' + std::string(degreeTen, '0'));
        numerator_ *= TEN;
    }

    VzPrime();
}

std::string Rational::toString() const {
    std::string strRat;

    strRat += numerator_.toString();
    if (denominator_ > 1) {
        strRat += '/';
        strRat += denominator_.toString();
    }

    return strRat;
}
std::string Rational::asDecimal(size_t precision) const {
    std::string strRat;
    BigInteger TEN = 1;
    for (size_t i = 0; i < precision + 1; ++i){
        TEN *= 10;
    }

    BigInteger Int = numerator_ / denominator_;
    if (numerator_ < 0 && Int == 0) {
        strRat += '-';
    }
    strRat += Int.toString();

    if (numerator_ < 0) TEN = -TEN;
    if (precision > 0) {
        BigInteger Float = (numerator_ * TEN) / denominator_;
        Float -= Int * TEN;

        if (Float % 10 >= 5) Float += 10;
        Float /= 10;

        strRat.push_back('.');
        for (size_t i = 0; i < precision - Float.size(); ++i) {
            strRat.push_back('0');
        }
        strRat += Float.toString();
    }

    return strRat;
}

Rational::operator double() const {
    std::string strRat = asDecimal(309);

    return stod(strRat);
}

#endif //FASTRATIONAL_RATIONAL_H
