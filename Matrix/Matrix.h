#include "MatrixBase.h"

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

template <unsigned int N, typename Field=Rational>
class SquareMatrix: public Matrix<N, N, Field>{
public:
    SquareMatrix();
    explicit SquareMatrix(const Matrix<N, N, Field>& other);
    SquareMatrix(const std::initializer_list<std::initializer_list<Field>>& in_list);
    ~SquareMatrix() = default;
    SquareMatrix<N, Field>& operator=(const Matrix<N, N, Field>& matrix) override;
};

template<unsigned int N, typename Field>
SquareMatrix<N, Field>::SquareMatrix(): Matrix<N, N, Field>() {}

template<unsigned int N, typename Field>
SquareMatrix<N, Field>::SquareMatrix(const Matrix<N, N, Field>& other):
        Matrix<N, N, Field>(other) {}

template<unsigned int N, typename Field>
SquareMatrix<N, Field>::SquareMatrix(const std::initializer_list<std::initializer_list<Field>>& in_list):
        Matrix<N, N, Field>(in_list) {}

template<unsigned int N, typename Field>
SquareMatrix<N, Field>& SquareMatrix<N, Field>::operator= (const Matrix<N, N, Field>& matrix) {
    for (size_t i = 0; i < N; ++i){
        for (size_t j = 0; j < N; ++j){
            this->matrix_[i][j] = matrix.matrix_[i][j];
        }
    }

    return *this;
}

#endif //MATRIX_MATRIX_H
