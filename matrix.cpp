#include "matrix.h"
#include <algorithm>
#include <stdexcept>
#include <thread>
#include <vector>

Matrix::Matrix() : rows_(0), cols_(0), data_() {}

Matrix::Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols), data_(rows * cols, 0) {}

Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {}

Matrix::Matrix(Matrix&& other) noexcept : rows_(other.rows_), cols_(other.cols_), data_(std::move(other.data_)) {
    other.rows_ = 0;
    other.cols_ = 0;
}

Matrix::~Matrix() {}

double Matrix::get(size_t row, size_t col) const {
    return data_[row * cols_ + col];
}

void Matrix::set(size_t row, size_t col, double value) {
    data_[row * cols_ + col] = value;
}

size_t Matrix::rows() const {
    return rows_;
}

size_t Matrix::cols() const {
    return cols_;
}

void Matrix::fill(double value) {
    std::fill(data_.begin(), data_.end(), value);
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    }
    Matrix result(rows_, other.cols_);
    std::vector<std::thread> threads;

    auto worker = [&](size_t start, size_t end) {
        for (size_t i = start; i < end; ++i) {
            for (size_t j = 0; j < other.cols_; ++j) {
                for (size_t k = 0; k < cols_; ++k) {
                    result.set(i, j, result.get(i, j) + get(i, k) * other.get(k, j));
                }
            }
        }
    };

    size_t num_threads = std::thread::hardware_concurrency();
    size_t chunk_size = (rows_ + num_threads - 1) / num_threads;

    for (size_t t = 0; t < num_threads; ++t) {
        size_t start = t * chunk_size;
        size_t end = std::min(start + chunk_size, rows_);
        threads.emplace_back(worker, start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(cols_, rows_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            result.set(j, i, get(i, j));
        }
    }
    return result;
}

extern "C" {
    Matrix* Matrix_new(size_t rows, size_t cols) {
        return new Matrix(rows, cols);
    }

    void Matrix_delete(Matrix* m) {
        delete m;
    }

    double Matrix_get(const Matrix* m, size_t row, size_t col) {
        return m->get(row, col);
    }

    void Matrix_set(Matrix* m, size_t row, size_t col, double value) {
        m->set(row, col, value);
    }

    size_t Matrix_rows(const Matrix* m) {
        return m->rows();
    }

    size_t Matrix_cols(const Matrix* m) {
        return m->cols();
    }

    void Matrix_fill(Matrix* m, double value) {
        m->fill(value);
    }

    Matrix* Matrix_multiply(const Matrix* a, const Matrix* b) {
        return new Matrix(*a * *b);
    }

    Matrix* Matrix_transpose(const Matrix* m) {
        return new Matrix(m->transpose());
    }
}
