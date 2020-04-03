#include "../FastRational/Rational.h"
#include "../Finite/Finite.h"
#include <vector>

#ifndef MATRIX_MATRIXBASE_H
#define MATRIX_MATRIXBASE_H

template<unsigned int N, unsigned int M>
struct equal{
    static const bool is_equal = 1 / static_cast<int>(!static_cast<bool>(M - N)); // M != N
};

template<typename Field>
std::vector<Field>& operator+=(std::vector<Field>& left, const std::vector<Field>& right) {
    size_t sz = std::min(left.size(), right.size());
    for (size_t i = 0; i < sz; ++i){
        left[i] += right[i];
    }
    return left;
}
template<typename Field>
std::vector<Field> operator*(std::vector<Field> left, const Field& f){
    std::vector<Field> Result;

    for (size_t i = 0; i < left.size(); ++i){
        Result.push_back(left[i] * f);
    }

    return Result;
}
template<typename Field>
std::vector<Field>& operator*=(std::vector<Field>& left, const Field& f){
    for (size_t i = 0; i < left.size(); ++i){
        left[i] *= f;
    }

    return left;
}
template<typename Field>
std::vector<Field>& AddAndMult(std::vector<Field>& left, std::vector<Field>& right, const Field& f){
    for (size_t i = 0; i < left.size(); ++i){
        left[i] += right[i] * f;
    }

    return left;
}

template <unsigned int N, unsigned int M, typename Field = Rational>
class Matrix{
protected:
    Field** matrix_;

    template <unsigned int P, unsigned int Q>
    void resize_(const Matrix<P, Q, Field>& matrix, unsigned int up_min, unsigned int left_min);
    template<unsigned int P, unsigned int Q>
    void insert_(const Matrix<P, Q, Field>& matrix, unsigned int up, unsigned int left);
    std::pair<unsigned int, Field> rank_and_det() const;
public:
    template <unsigned int, unsigned int, typename>
    friend class Matrix;
    template <unsigned int, unsigned int, typename>
    friend class Matrix;
    template <unsigned int, typename>
    friend class SquareMatrix;

    Matrix();
    template<typename Init>
    Matrix(const std::initializer_list<std::initializer_list<Init>>& in_list);
    Matrix(const Matrix<N, M, Field>& matrix);

    virtual Matrix<N, M, Field>& operator=(const Matrix<N, M, Field>& matrix);

    ~Matrix ();

    Matrix<N, M, Field>& operator+=(const Matrix<N, M, Field>& add);
    Matrix<N, M, Field>& operator-=(const Matrix<N, M, Field>& add);
    Matrix<N, M, Field>  operator+(const Matrix<N, M, Field>& add) const;
    Matrix<N, M, Field>  operator-(const Matrix<N, M, Field>& add) const;
    Matrix<N, M, Field>  operator-() const;

    bool operator==(const Matrix<N, M, Field>& other) const;
    bool operator!=(const Matrix<N, M, Field>& other) const;

    Matrix<N, M, Field>& operator*=(const Field& k);
    Matrix<N, M, Field>  operator*(const Field& k) const;

    template <unsigned int K>
    Matrix<N, K, Field> operator*(const Matrix<M, K, Field>& matrix) const;
    template <unsigned int K>
    Matrix<N, K, Field> SmartMultiple(const Matrix<M, K, Field>& matrix) const;
    template <unsigned int K>
    Matrix<N, K, Field> SmallMultiple(const Matrix<M, K, Field>& matrix) const;
    Matrix<N, 1, Field> operator*(const Matrix<M, 1, Field>& matrix) const;
    template <unsigned int K>
    Matrix<N, K, Field>& operator*=(const Matrix<M, K, Field>& matrix);

    Matrix<M, N, Field> transposed() const;

    Field* operator[](unsigned int n);
    const Field* operator[](unsigned int n) const;
    unsigned int rank() const;

    std::vector<Field> getRow(unsigned int n) const;
    std::vector<Field> getColumn(unsigned int m) const;

    void print() const;
    Field det() const;
    Field trace() const;

    Matrix inverted() const;
    void invert();
};

template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field>::Matrix() {
    Field(1) / Field(1);

    matrix_ = new Field*[N];
    for (size_t i = 0; i < N; ++i){
        matrix_[i] = new Field[M];
    }

    if (N == M){
        for (size_t i = 0; i < N; ++i) {
            matrix_[i][i] = Field(1);
        }
    }
}
template<unsigned int N, unsigned int M, typename Field>
template<typename Init>
Matrix<N, M, Field>::Matrix(const std::initializer_list<std::initializer_list<Init>>& in_list) {
    Field(1) / Field(1);

    matrix_ = new Field*[N];
    auto it1 = in_list.begin();
    for (size_t i = 0; i < N; ++i, ++it1) {
        auto it2 = (*it1).begin();
        matrix_[i] = new Field[M];
        for (size_t j = 0; j < M; ++j, ++it2) {
            matrix_[i][j] = *it2;
        }
    }
}
template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field>::Matrix(const Matrix<N, M, Field>& matrix) {
    Field(1) / Field(1);

    matrix_ = new Field*[N];
    for (size_t i = 0; i < N; ++i) {
        matrix_[i] = new Field[M];
    }

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            matrix_[i][j] = matrix.matrix_[i][j];
        }
    }
}
template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field>& Matrix<N, M, Field>::operator=(const Matrix<N, M, Field>& matrix) {
    for (size_t i = 0; i < N; ++i){
        for (size_t j = 0; j < M; ++j){
            matrix_[i][j] = matrix.matrix_[i][j];
        }
    }

    return *this;
}
template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field>::~Matrix() {
    for (size_t i = 0; i < N; ++i){
        delete[] matrix_[i];
    }
    delete[] matrix_;
}

template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field>& Matrix<N, M, Field>::operator+=(const Matrix<N, M, Field>& add) {
    for (size_t i = 0; i < N; ++i){
        for (size_t j = 0; j < M; ++j){
            matrix_[i][j] += add.matrix_[i][j];
        }
    }

    return *this;
}
template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field>& Matrix<N, M, Field>::operator-=(const Matrix<N, M, Field>& add) {
    *this += -add;

    return *this;
}
template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field> Matrix<N, M, Field>::operator+ (const Matrix<N, M, Field>& add) const {
    Matrix<N, M, Field> Result;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            Result.matrix_[i][j] = matrix_[i][j] + add.matrix_[i][j];
        }
    }

    return Result;
}
template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field> Matrix<N, M, Field>::operator-(const Matrix<N, M, Field>& add) const {
    Matrix<N, M, Field> Result;
    Result = *this + (-add);

    return Result;
}
template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field> Matrix<N, M, Field>::operator-() const {
    Matrix<N, M, Field> Result;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            Result.matrix_[i][j] = -matrix_[i][j];
        }
    }

    return Result;
}

template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field>& Matrix<N, M, Field>::operator*=(const Field& k) {
    for (size_t i = 0; i < N; ++i){
        for (size_t j = 0; j < M; ++j){
            matrix_[i][j] *= k;
        }
    }

    return *this;
}
template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field> Matrix<N, M, Field>::operator*(const Field& k) const {
    Matrix<N, M, Field> Result;
    for (size_t i = 0; i < N; ++i){
        for (size_t j = 0; j < M; ++j){
            Result.matrix_[i][j] = matrix_[i][j] * k;
        }
    }

    return Result;
}
template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field> operator*(const Field& k, const Matrix<N, M, Field>& other) {
    return other * k;
}

template<unsigned int N, unsigned int M, typename Field>
template<unsigned int K>
Matrix<N, K, Field> Matrix<N, M, Field>::operator*(const Matrix<M, K, Field>& matrix) const {
    if (N < 10 && M < 10 && K < 10) {
        return SmallMultiple(matrix);
    } else {
        return SmartMultiple(matrix);
    }
}

template<unsigned int N, unsigned int M, typename Field>
template<unsigned int K>
Matrix<N, K, Field> Matrix<N, M, Field>::SmartMultiple(const Matrix<M, K, Field>& matrix) const {
    const unsigned int SmallN = (N + 1) / 2;
    const unsigned int SmallK = (K + 1) / 2;
    const unsigned int SmallM = (M + 1) / 2;

    Matrix<SmallN, SmallM, Field> Left00;
    Matrix<SmallN, SmallM, Field> Left01;
    Matrix<SmallN, SmallM, Field> Left10;
    Matrix<SmallN, SmallM, Field> Left11;
    Left00.resize_(*this, 0,      0);
    Left01.resize_(*this, 0,      SmallM);
    Left10.resize_(*this, SmallN, 0);
    Left11.resize_(*this, SmallN, SmallM);

    Matrix<SmallM, SmallK, Field> Right00;
    Matrix<SmallM, SmallK, Field> Right01;
    Matrix<SmallM, SmallK, Field> Right10;
    Matrix<SmallM, SmallK, Field> Right11;
    Right00.resize_(matrix, 0,      0);
    Right01.resize_(matrix, 0,      SmallK);
    Right10.resize_(matrix, SmallM, 0);
    Right11.resize_(matrix, SmallM, SmallK);

    Matrix<SmallN, SmallK, Field> P0 = (Left00 + Left11) * (Right00 + Right11);
    Matrix<SmallN, SmallK, Field> P1 = (Left10 + Left11) * (Right00);
    Matrix<SmallN, SmallK, Field> P2 = (Left00         ) * (Right01 - Right11);
    Matrix<SmallN, SmallK, Field> P3 = (Left11         ) * (Right10 - Right00);
    Matrix<SmallN, SmallK, Field> P4 = (Left00 + Left01) * (Right11);
    Matrix<SmallN, SmallK, Field> P5 = (Left10 - Left00) * (Right00 + Right01);
    Matrix<SmallN, SmallK, Field> P6 = (Left01 - Left11) * (Right10 + Right11);

    Matrix<N, K, Field> Result;

    Result.insert_(P0 + P3 - P4 + P6, 0,      0);
    Result.insert_(P1 + P3,           SmallN, 0);
    Result.insert_(P2 + P4,           0,      SmallK);
    Result.insert_(P0 - P1 + P2 + P5, SmallN, SmallK);

    return Result;
}
template<unsigned int N, unsigned int M, typename Field>
template<unsigned int K>
Matrix<N, K, Field> Matrix<N, M, Field>::SmallMultiple(const Matrix<M, K, Field>& matrix) const {
    Matrix<N, K, Field> Result;
    Field null = Field(0);

    for (size_t n = 0; n < N; ++n) {
        for (size_t k = 0; k < K; ++k) {
            Result.matrix_[n][k] = null;
            for (size_t m = 0; m < M; ++m) {
                Result.matrix_[n][k] += matrix_[n][m] * matrix.matrix_[m][k];
            }
        }
    }

    return Result;
}
template<unsigned int N, unsigned int M, typename Field>
Matrix<N, 1, Field> Matrix<N, M, Field>::operator*(const Matrix<M, 1, Field>& matrix) const {
    Matrix<N, 1, Field> Result;

    for (size_t i = 0; i < N; ++i){
        Result.matrix_[i][0] = 0;
        for (size_t j = 0; j < M; ++j){
            Result.matrix_[i][0] += this->matrix_[i][j] * matrix.matrix_[j][0];
        }
    }


    return Result;
}
template<unsigned int N, unsigned int M, typename Field>
template<unsigned int K>
Matrix<N, K, Field>& Matrix<N, M, Field>::operator*=(const Matrix<M, K, Field>& matrix) {
    *this = *this * matrix;
    return *this;
}

template<unsigned int N, unsigned int M, typename Field>
template<unsigned int P, unsigned int Q>
void Matrix<N, M, Field>::resize_(const Matrix<P, Q, Field>& matrix, unsigned int up_min, unsigned int left_min) {
    unsigned int minX = std::min(Q - left_min, M);
    unsigned int minY = std::min(P - up_min, N);
    for (unsigned int i = 0; i < minY; ++i) {
        for (unsigned int j = 0; j < minX; ++j) {
            matrix_[i][j] = matrix.matrix_[i + up_min][j + left_min];
        }
        for (unsigned int j = minX; j < M; ++j) {
            matrix_[i][j] = 0;
        }
    }
    for (unsigned int i = minY; i < N; ++i) {
        for (unsigned int j = 0; j < M; ++j) {
            matrix_[i][j] = 0;
        }
    }
}
template<unsigned int N, unsigned int M, typename Field>
template<unsigned int P, unsigned int Q>
void Matrix<N, M, Field>::insert_(const Matrix<P, Q, Field>& matrix, unsigned int up, unsigned int left) {
    for (unsigned int i = up; i < N && i < P + up; ++i) {
        for (unsigned int j = left; j < M && j < Q + left; ++j) {
            matrix_[i][j] = matrix.matrix_[i - up][j - left];
        }
    }
}

template<unsigned int N, unsigned int M, typename Field>
Matrix<M, N, Field> Matrix<N, M, Field>::transposed() const {
    Matrix<M, N, Field> Result;

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            Result.matrix_[j][i] = matrix_[i][j];
        }
    }

    return Result;
}

template<unsigned int N, unsigned int M, typename Field>
std::pair<unsigned int, Field> Matrix<N, M, Field>::rank_and_det() const {
    unsigned int rk = 0;
    Field det = Field(1);
    std::vector<Field> Raws [N];

    for (size_t i = 0; i < N; ++i) {
        Raws[i] = getRow(i);
    }

    Field null = Field(0);

    for (size_t m = 0; m < M; ++m) {
        bool was_not_null = false;
        for (unsigned int n = rk; n < N; ++n) {
            if (!was_not_null) {
                if (Raws[n][m] != null) {
                    std::swap(Raws[rk], Raws[n]);
                    if (rk != n) {
                        det = -det;
                    }
                    ++rk;
                    was_not_null = true;
                }
            } else {
                Raws[n] += Raws[rk - 1] * (-(Raws[n][m] / Raws[rk - 1][m]));
            }
        }
        if (m < N) {
            det *= Raws[m][m];
        }
    }

    return std::pair<unsigned int, Field>(rk, det);
}

template<unsigned int N, unsigned int M, typename Field>
unsigned int Matrix<N, M, Field>::rank() const {
    return rank_and_det().first;
}

template<unsigned int N, unsigned int M, typename Field>
void Matrix<N, M, Field>::print() const {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            std::cout << matrix_[i][j] << "  ";
        }
        std::cout << "\n";
    }
}

template<unsigned int N, unsigned int M, typename Field>
Field* Matrix<N, M, Field>::operator[](unsigned int n) {
    return matrix_[n];
}
template<unsigned int N, unsigned int M, typename Field>
const Field* Matrix<N, M, Field>::operator[](unsigned int n) const {
    return matrix_[n];
}

template<unsigned int N, unsigned int M, typename Field>
std::vector<Field> Matrix<N, M, Field>::getRow(unsigned int n) const {
    std::vector<Field> Result;

    for (size_t i = 0; i < M; ++i) {
        Result.emplace_back(matrix_[n][i]);
    }

    return Result;
}
template<unsigned int N, unsigned int M, typename Field>
std::vector<Field> Matrix<N, M, Field>::getColumn(unsigned int m) const {
    std::vector<Field> Result;

    for (size_t i = 0; i < N; ++i) {
        Result.emplace_back(matrix_[i][m]);
    }

    return Result;
}

template<unsigned int N, unsigned int M, typename Field>
bool Matrix<N, M, Field>::operator==(const Matrix<N, M, Field>& other) const {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            if (matrix_[i][j] != other.matrix_[i][j]) {
                return false;
            }
        }
    }

    return true;
}

template<unsigned int N, unsigned int M, typename Field>
bool Matrix<N, M, Field>::operator!=(const Matrix<N, M, Field>& other) const {
    return !(*this == other);
}

template<unsigned int N, unsigned int M, typename Field>
Field Matrix<N, M, Field>::trace() const {
    if (!equal<N, M>::is_equal) {
        return 0;
    }
    Field Result = 0;
    for (unsigned int i = 0; i < N; ++i) {
            Result += this->matrix_[i][i];
        }
    return Result;

}
template<unsigned int N, unsigned int M, typename Field>
Field Matrix<N, M, Field>::det() const {
    if (!equal<N, M>::is_equal) {
        return 0;
    }
    return this->rank_and_det().second;
}

template<unsigned int N, unsigned int M, typename Field>
Matrix<N, M, Field> Matrix<N, M, Field>::inverted() const {
    if (!equal<N, M>::is_equal) {
        return *this;
    }

    std::vector<Field> Raws [N];
    Field null = Field(0);
    Field e = Field(1);

    for (size_t i = 0; i < N; ++i) {
        Raws[i] = this->getRow(i);
        for (size_t j = 0; j < N; ++j) {
            if (i == j) {
                Raws[i].push_back(e);
            } else {
                Raws[i].push_back(null);
            }
        }
    }

    int start = 0;
    bool was;
    for (size_t j = 0; j < N; ++j) {
        was = false;
        for (size_t i = start; i < N; ++i) {
            if (was) {
                AddAndMult(Raws[i], Raws[start - 1], -Raws[i][j]);
            } else if (Raws[i][j] != null) {
                std::swap(Raws[i], Raws[start]);
                Raws[start] *= (e / Raws[start][j]);
                was = true;
                ++start;
            }
        }
    }

    for (int j = N - 1; j >= 0; --j) {
        for (int i = j - 1; i >= 0; --i) {
            AddAndMult(Raws[i], Raws[j], -Raws[i][j]);
        }
    }

    Matrix<N, M, Field> Result;

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            Result.matrix_[i][j] = Raws[i][j + N];
        }
    }

    return Result;
}
template<unsigned int N, unsigned int M, typename Field>
void Matrix<N, M, Field>::invert() {
    if (!equal<N, M>::is_equal) {
        return;
    }

    *this = inverted();
}

#endif //MATRIX_MATRIXBASE_H
