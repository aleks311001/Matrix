#include <iostream>
#include <vector>
#include <string>

#ifndef FASTRATIONAL_BIGINTEGER_H
#define FASTRATIONAL_BIGINTEGER_H

class BigInteger{
public:
    BigInteger();
    BigInteger(int Int);
    BigInteger(const BigInteger& BInt);

    BigInteger& operator=(const BigInteger& BInt);
    BigInteger& operator=(const int& Int);

    std::string toString() const;
    void fromString(std::string str);

    friend std::ostream& operator<<(std::ostream &out, const BigInteger& BInt);
    friend std::istream& operator>>(std::istream &in, BigInteger& BInt);

    BigInteger operator-() const;

    BigInteger& operator+=(const BigInteger& BInt);
    BigInteger& operator-=(const BigInteger& BInt);
    BigInteger& operator*=(const BigInteger& BInt);
    BigInteger& operator/=(const BigInteger& BInt);
    BigInteger& operator%=(const BigInteger& BInt);

    BigInteger& operator++();
    BigInteger& operator--();
    BigInteger  operator++(int);
    BigInteger  operator--(int);

    BigInteger operator*(const BigInteger& BInt) const;
    BigInteger operator*(const int& Int) const;
    BigInteger operator/(const BigInteger& BInt) const;
    BigInteger operator/(const int& Int) const;
    BigInteger operator%(const BigInteger& BInt) const;
    BigInteger operator%(const int& Int) const;

    std::pair<BigInteger, BigInteger> Div(const BigInteger& BigInt) const;
    BigInteger& DivOn2();

    bool operator==(const BigInteger& BInt) const;
    bool operator!=(const BigInteger& BInt) const;
    bool operator>=(const BigInteger& BInt) const;
    bool operator<=(const BigInteger& BInt) const;
    bool operator> (const BigInteger& BInt) const;
    bool operator< (const BigInteger& BInt) const;

    operator bool() const;
    size_t size() const;
    bool sgn() const;
    BigInteger BinaryGCD(const BigInteger& BigInt) const;
private:

    std::vector<int> ArrBigInt_;
    bool sign_;
    static const int BASE = 10000;
    static const int DEG = 4;
    static int modBASE_(int a);
    void Del0_();
    void choiceSign_(const BigInteger& BInt , int& si1, int& si2, bool& signReal) const;
    BigInteger move_(const int& n) const;
};

BigInteger::BigInteger(): sign_ (true) {}
BigInteger::BigInteger(int Int) {
    if (Int >= 0) {
        sign_ = true;
    } else {
        sign_ = false;
        Int = -Int;
    }

    for (; Int > 0; Int /= BASE) {
        ArrBigInt_.push_back(Int % BASE);
    }
}
BigInteger::BigInteger(const BigInteger& BInt) {
    ArrBigInt_ = BInt.ArrBigInt_;
    sign_ = BInt.sign_;
}

BigInteger& BigInteger::operator=(const BigInteger& BInt) {
    if (this == &BInt) {
        return *this;
    }

    ArrBigInt_.clear();
    sign_ = BInt.sign_;

    int sz = BInt.ArrBigInt_.size();
    if (sz == 0) {
        return *this;
    }

    for (int i = 0; i < sz; ++i) {
        ArrBigInt_.push_back(BInt.ArrBigInt_[i]);
    }

    return *this;
}
BigInteger& BigInteger::operator=(const int& Int) {
    BigInteger BInt(Int);
    *this = BInt;
    return *this;
}

std::string BigInteger::toString() const {
    std::string BigStr;

    if (!sign_){
        BigStr.push_back('-');
    }

    if (ArrBigInt_.empty()) {
        BigStr = '0';
    } else {
        size_t sz = ArrBigInt_.size();
        std::string add;
        for (size_t i = 0; i < sz; ++i) {
            add = std::to_string(ArrBigInt_[sz - i - 1]);
            if (i > 0) {
                while (add.size() < DEG) {
                    add = '0' + add;
                }
            }
            BigStr.append(add);
        }
    }

    return BigStr;
}
void BigInteger::fromString(std::string str) {
    int sz = str.length();
    int szWithoutSign = sz;
    ArrBigInt_.clear();
    sign_ = true;

    int min = 0;
    if (str[0] == '-') {
        sign_ = false;
        --szWithoutSign;
        min = 1;
    }

    for (int i = 0; i < szWithoutSign; i += DEG) {
        ArrBigInt_.push_back(stoi(str.substr(std::max(sz - i - DEG, min), DEG)));
    }

    Del0_();
}

bool BigInteger::operator==(const BigInteger& BInt) const {
    int sz1 = ArrBigInt_.size();
    int sz2 = BInt.ArrBigInt_.size();

    if (sz1 != sz2 || sign_ != BInt.sign_) {
        return false;
    }

    for (int i = 0; i < sz1; ++i){
        if (ArrBigInt_[i] != BInt.ArrBigInt_[i]) {
            return false;
        }
    }

    return true;
}
bool BigInteger::operator!=(const BigInteger& BInt) const {
    return !(*this == BInt);
}
bool BigInteger::operator>=(const BigInteger& BInt) const {
    return !(BInt > *this);
}
bool BigInteger::operator<=(const BigInteger& BInt) const {
    return !(*this > BInt);
}
bool BigInteger::operator> (const BigInteger& BInt) const {
    if (sign_ != BInt.sign_) {
        return sign_;
    }

    int si = sign_ ? 1 : -1;

    int sz1 = ArrBigInt_.size();
    int sz2 = BInt.ArrBigInt_.size();

    if  (si * sz1 > si * sz2) {
        return true;
    }
    if  (si * sz1 < si * sz2) {
        return false;
    }

    for (int i = sz1 - 1; i >= 0; --i){
        if (ArrBigInt_[i] > BInt.ArrBigInt_[i]) {
            return true;
        }
        if (ArrBigInt_[i] < BInt.ArrBigInt_[i]) {
            return false;
        }
    }

    return false;
}
bool BigInteger::operator< (const BigInteger& BInt) const {
    return BInt > *this;
}

bool operator==(const int& Int1, const BigInteger& BInt2) {
    BigInteger BInt1(Int1);
    return BInt1 == BInt2;
}
bool operator!=(const int& Int1, const BigInteger& BInt2) {
    BigInteger BInt1(Int1);
    return BInt1 != BInt2;
}
bool operator>=(const int& Int1, const BigInteger& BInt2) {
    BigInteger BInt1(Int1);
    return BInt1 >= BInt2;
}
bool operator<=(const int& Int1, const BigInteger& BInt2) {
    BigInteger BInt1(Int1);
    return BInt1 <= BInt2;
}
bool operator> (const int& Int1, const BigInteger& BInt2) {
    BigInteger BInt1(Int1);
    return BInt1 > BInt2;
}
bool operator< (const int& Int1, const BigInteger& BInt2) {
    BigInteger BInt1(Int1);
    return BInt1 < BInt2;
}

bool operator==(const BigInteger& BInt1, const int& Int2) {
    BigInteger BInt2(Int2);
    return BInt1 == BInt2;
}
bool operator!=(const BigInteger& BInt1, const int& Int2) {
    BigInteger BInt2(Int2);
    return BInt1 != BInt2;
}
bool operator>=(const BigInteger& BInt1, const int& Int2) {
    BigInteger BInt2(Int2);
    return BInt1 >= BInt2;
}
bool operator<=(const BigInteger& BInt1, const int& Int2) {
    BigInteger BInt2(Int2);
    return BInt1 <= BInt2;
}
bool operator> (const BigInteger& BInt1, const int& Int2) {
    BigInteger BInt2(Int2);
    return BInt1 > BInt2;
}
bool operator< (const BigInteger& BInt1, const int& Int2) {
    BigInteger BInt2(Int2);
    return BInt1 < BInt2;
}

std::ostream& operator<<(std::ostream &out, const BigInteger& BInt) {
    out << BInt.toString();
    return out;
}
std::istream& operator>>(std::istream &in, BigInteger& BInt) {
    std::string str;
    in >> str;
    BInt.fromString(str);

    return in;
}

BigInteger BigInteger::operator-() const {
    BigInteger BResult(*this);
    if (BResult != 0) {
        BResult.sign_ = !BResult.sign_;
    }
    return BResult;
};

BigInteger operator+(BigInteger BInt1, const BigInteger& BInt2) {
    return BInt1 += BInt2;
}
BigInteger operator+(const int& Int1, const BigInteger& BInt2) {
    BigInteger BInt1(Int1);
    return BInt1 += BInt2;
}
BigInteger operator+(const BigInteger& BInt1, const int& Int2) {
    BigInteger BInt2(Int2);
    return BInt2 += BInt1;
}

BigInteger operator-(BigInteger BInt1, const BigInteger& BInt2) {
    return BInt1 += -BInt2;;
}
BigInteger operator-(const int& Int1, const BigInteger& BInt2) {
    BigInteger BInt1(Int1);
    return BInt1 += -BInt2;
}
BigInteger operator-(BigInteger BInt1, const int& Int2) {
    BigInteger BInt2(Int2);
    return BInt1 += -BInt2;;
}

BigInteger& BigInteger::operator++() {
    return *this += 1;
}
BigInteger& BigInteger::operator--() {
    return *this += -1;
}
BigInteger  BigInteger::operator++(int) {
    BigInteger BCopy = *this;
    *this += 1;
    return BCopy;
}
BigInteger  BigInteger::operator--(int) {
    BigInteger BCopy = *this;
    *this += -1;
    return BCopy;
}

BigInteger BigInteger::operator*(const BigInteger& BInt) const {
    BigInteger BResult;
    int sz1 = ArrBigInt_.size();
    int sz2 = BInt.ArrBigInt_.size();
    int sumDigits = 0;
    int transferDigit = 0;

    for (int i = 0; i < sz1 + sz2 - 1; ++i){
        sumDigits = transferDigit;
        for (int j = std::max(0, i - sz2 + 1); j <= i && j < sz1; ++j){
            sumDigits += ArrBigInt_[j] * BInt.ArrBigInt_[i - j];
        }
        BResult.ArrBigInt_.push_back(sumDigits % BASE);
        transferDigit = sumDigits / BASE;
    }
    BResult.ArrBigInt_.push_back(transferDigit);

    BResult.sign_ = (sign_ == BInt.sign_);
    BResult.Del0_();
    return BResult;
}
BigInteger BigInteger::operator*(const int& Int) const {
    BigInteger BInt(Int);
    return *this * BInt;
}
BigInteger operator*(const int& Int1, const BigInteger& BInt2) {
    BigInteger BInt1(Int1);
    return BInt2 * BInt1;
}

BigInteger BigInteger::operator/(const BigInteger& BInt) const {
    return Div(BInt).first;
}
BigInteger BigInteger::operator/(const int& Int) const {
    BigInteger BInt(Int);
    return *this / BInt;
}
BigInteger operator/(const int& Int1, const BigInteger& BInt2) {
    BigInteger BInt1(Int1);
    return BInt1 / BInt2;
}

BigInteger BigInteger::operator%(const BigInteger& BInt) const {
    return Div(BInt).second;
}
BigInteger BigInteger::operator%(const int& Int) const {
    BigInteger BInt(Int);
    return *this % BInt;
}
BigInteger operator%(const int& Int1, const BigInteger& BInt2) {
    BigInteger BInt1(Int1);
    return BInt1 % BInt2;
}

std::pair<BigInteger, BigInteger> BigInteger::Div(const BigInteger& BigInt) const {
    BigInteger BResult;
    BigInteger BInt = BigInt;
    BigInteger BCopyLeft(*this);

    if (*this == 0 || BInt == 0) {
        return std::pair<BigInteger, BigInteger>(BResult, BResult);
    }

    bool realSize = !(sign_ xor BInt.sign_);
    BCopyLeft.sign_ = true;
    BInt.sign_ = true;

    int sz1 = ArrBigInt_.size();
    int sz2 = BInt.ArrBigInt_.size();

    int szResult = sz1 - sz2;
    if (BCopyLeft.move_(szResult) < BInt) {
        --szResult;
    }
    if (szResult < 0) {
        return std::pair<BigInteger, BigInteger>(BResult, *this);
    }

    BigInteger TEN;
    for (int n = 0; n < szResult; ++n){
        TEN.ArrBigInt_.push_back(0);
    }
    TEN.ArrBigInt_.push_back(1);

    for (int j = 0; j < szResult + 1; ++j){
        BResult.ArrBigInt_.push_back(0);
    }

    int digitResult = 0;
    BigInteger BLeftMove;

    for (int i = szResult; i >= 0; --i){
        digitResult = BASE / 2;
        BLeftMove = BCopyLeft.move_(i) - digitResult * BInt;

        for (int j = (BASE + 3) / 4; j > 0; j = j > 1 ? (j + 1) / 2 : 0) {
            if (BLeftMove >= 0) {
                digitResult += j;
                BLeftMove -= j * BInt;
            } else {
                digitResult -= j;
                BLeftMove += j * BInt;
            }
        }

        if (BLeftMove >= 0) {
            ++digitResult;
            BLeftMove -= BInt;
            if (BLeftMove < 0) {
                --digitResult;
                BLeftMove += BInt;
            }
        } else {
            --digitResult;
            BLeftMove += BInt;
        }


        BResult.ArrBigInt_[i] = digitResult;
        BCopyLeft -= BInt * TEN * digitResult;
        TEN = TEN.move_(1);
    }

    BResult.sign_ = realSize;
    BResult.Del0_();
    return std::pair<BigInteger, BigInteger>(BResult, BLeftMove);
}

BigInteger& BigInteger::operator+=(const BigInteger& BInt) {
    int sz1 = ArrBigInt_.size();
    int sz2 = BInt.ArrBigInt_.size();

    int sign1 = 1;
    int sign2 = 1;
    choiceSign_(BInt, sign1, sign2, sign_);

    int sumDigits = 0;
    int transferDigit = 0;
    for (int i = 0; i < sz1 && i < sz2; ++i) {
        sumDigits = sign1 * ArrBigInt_[i] + sign2 * BInt.ArrBigInt_[i] + transferDigit;
        ArrBigInt_[i] = modBASE_(sumDigits);
        transferDigit = (sumDigits >= 0) ? sumDigits / BASE : -1;
    }

    for (int i = sz2; i < sz1; ++i) {
        sumDigits = sign1 * ArrBigInt_[i] + transferDigit;
        ArrBigInt_[i] = modBASE_(sumDigits);
        transferDigit = (sumDigits >= 0) ? sumDigits / BASE : -1;
    }

    for (int i = sz1; i < sz2; ++i) {
        sumDigits = sign2 * BInt.ArrBigInt_[i] + transferDigit;
        ArrBigInt_.push_back(modBASE_(sumDigits));
        transferDigit = (sumDigits >= 0) ? sumDigits / BASE : -1;
    }

    ArrBigInt_.push_back(abs(transferDigit));

    Del0_();
    return *this;
}
BigInteger& BigInteger::operator-=(const BigInteger& BInt) {
    *this += -BInt;
    return *this;
}
BigInteger& BigInteger::operator*=(const BigInteger& BInt) {
    *this = *this * BInt;
    return *this;
}
BigInteger& BigInteger::operator/=(const BigInteger& BInt) {
    *this = *this / BInt;
    return *this;
}
BigInteger& BigInteger::operator%=(const BigInteger& BInt) {
    *this = *this % BInt;
    return *this;
}

BigInteger::operator bool() const {
    return !ArrBigInt_.empty();
}

void BigInteger::Del0_() {
    if (!ArrBigInt_.empty()) {
        for (size_t i = ArrBigInt_.size(); i >= 1 && ArrBigInt_[i - 1] == 0; --i) {
            ArrBigInt_.pop_back();
        }
    }

    if (ArrBigInt_.empty()) {
        sign_ = true;
    }
}
int BigInteger::modBASE_(int a) {
    if (a >= BASE) {
        return a - BASE;
    } else {
        if (a < 0) {
            return a + BASE;
        } else {
            return a;
        }
    }
}
void BigInteger::choiceSign_(const BigInteger& BInt , int& si1, int& si2, bool& signReal) const {
    if (sign_ == BInt.sign_) {
        si1 = 1;
        si2 = 1;
        signReal = sign_;
    } else {
        if (sign_) {
            si1 = (*this <= -BInt) ? -1 : 1;
        } else {
            si1 = (-*this >= BInt) ? 1 : -1;
        }
        si2 = -si1;
        signReal = (si1 == 1) ? sign_ : !sign_;
    }
}

BigInteger BigInteger::move_(const int& n) const {
    BigInteger BResult;
    int sz = ArrBigInt_.size();

    if (n >= sz) {
        return BResult;
    }
    if (n == 0) {
        return *this;
    }

    for (int i = 0; i < sz - n; ++i) {
        BResult.ArrBigInt_.push_back(ArrBigInt_[n + i]);
    }

    BResult.sign_ = this->sign_;
    BResult.Del0_();
    return BResult;
}

size_t BigInteger::size() const {
    if (*this == 0) {
        return 0;
    }
    return ArrBigInt_.size() * 4 - static_cast<size_t>(ArrBigInt_.back() < 1000) -
                                   static_cast<size_t>(ArrBigInt_.back() < 100) -
                                   static_cast<size_t>(ArrBigInt_.back() < 10);
}
bool BigInteger::sgn() const {
    return sign_;
}

BigInteger BigInteger::BinaryGCD(const BigInteger& BigInt) const {
    BigInteger BInt = BigInt;

    if (*this == 0) {
        return BInt;
    }
    if (BInt == 0) {
        return *this;
    }

    BigInteger Result = 1;
    BigInteger copy = *this;
    copy.sign_ = true;
    BInt.sign_ = true;
    while (copy != BInt) {
        if (copy.ArrBigInt_[0] & 1) {
            if (BInt.ArrBigInt_[0] & 1) {
                BInt > copy ? BInt -= copy : copy -= BInt;
            } else {
                BInt.DivOn2();
            }
        } else {
            if (BInt.ArrBigInt_[0] & 1) {
                copy.DivOn2();
            } else {
                Result *= 2;
                copy.DivOn2();
                BInt.DivOn2();
            }
        }
    }
    Result *= BInt;
    Result.sign_ = true;

    return Result;
}

BigInteger& BigInteger::DivOn2() {
    size_t sz = ArrBigInt_.size();

    int transfer = 0;
    for (size_t i = 0; i < sz; ++i) {
        ArrBigInt_[sz - i - 1] += transfer * BASE;
        transfer = ArrBigInt_[sz - i - 1] & 1;
        ArrBigInt_[sz - i - 1] >>= 1;
    }

    Del0_();
    return *this;
}

BigInteger abs(const BigInteger& BInt) {
    if (BInt >= 0) return BInt;
    return -BInt;
} 

#endif //FASTRATIONAL_BIGINTEGER_H
