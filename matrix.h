#ifndef MATRIX_H
#define MATRIX_H

#ifdef _WIN32
  #define MATRIX_API __declspec(dllexport)
#else
  #define MATRIX_API
#endif

#include <vector>
#include <cstddef>

class MATRIX_API Matrix {
public:
    Matrix();
    Matrix(size_t rows, size_t cols);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    ~Matrix();

    double get(size_t row, size_t col) const;
    void set(size_t row, size_t col, double value);

    size_t rows() const;
    size_t cols() const;
    void fill(double value);

    Matrix operator*(const Matrix& other) const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    Matrix elementwise_multiplication(const Matrix& other) const;
    Matrix transpose() const;

private:
    size_t rows_, cols_;
    std::vector<double> data_;
};

extern "C" {
    MATRIX_API Matrix* Matrix_new(size_t rows, size_t cols);
    MATRIX_API void Matrix_delete(Matrix* m);
    MATRIX_API double Matrix_get(const Matrix* m, size_t row, size_t col);
    MATRIX_API void Matrix_set(Matrix* m, size_t row, size_t col, double value);
    MATRIX_API size_t Matrix_rows(const Matrix* m);
    MATRIX_API size_t Matrix_cols(const Matrix* m);
    MATRIX_API void Matrix_fill(Matrix* m, double value);
    MATRIX_API Matrix* Matrix_multiply(const Matrix* a, const Matrix* b);
    MATRIX_API Matrix* Matrix_transpose(const Matrix* m);
}

#endif // MATRIX_H
