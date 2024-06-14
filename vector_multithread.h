#ifndef VECTOR_MULTITHREAD_H
#define VECTOR_MULTITHREAD_H

#include <vector>
#include <thread>
#include <stdexcept>

class Matrix {
public:
    // Constructor to initialize matrix with given rows and columns
    Matrix(size_t rows, size_t cols);

    // Get the value at the specified row and column
    double get(size_t row, size_t col) const;

    // Set the value at the specified row and column
    void set(size_t row, size_t col, double value);

    // Get the number of rows in the matrix
    size_t rows() const;

    // Get the number of columns in the matrix
    size_t cols() const;

    // Fill the matrix with a specified value
    void fill(double value);

    // Matrix multiplication
    Matrix operator*(const Matrix& other) const;

    // Matrix addition
    Matrix operator+(const Matrix& other) const;

    // Matrix subtraction
    Matrix operator-(const Matrix& other) const;

    // Scalar multiplication
    Matrix operator*(double scalar) const;

    // Element-wise multiplication
    Matrix elementwise_multiplication(const Matrix& other) const;

    // Matrix transposition
    Matrix transpose() const;

private:
    size_t rows_, cols_;
    std::vector<double> data_;
};

#endif // VECTOR_MULTITHREAD_H
