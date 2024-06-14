#include "vector_multithread.h"

// Constructor to initialize matrix with given rows and columns
Matrix::Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols), data_(rows * cols, 0) {}

// Get the value at the specified row and column
double Matrix::get(size_t row, size_t col) const {
    return data_[row * cols_ + col];
}

// Set the value at the specified row and column
void Matrix::set(size_t row, size_t col, double value) {
    data_[row * cols_ + col] = value;
}

// Get the number of rows in the matrix
size_t Matrix::rows() const {
    return rows_;
}

// Get the number of columns in the matrix
size_t Matrix::cols() const {
    return cols_;
}

// Fill the matrix with a specified value
void Matrix::fill(double value) {
    std::fill(data_.begin(), data_.end(), value);
}

// Matrix multiplication
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
    size_t chunk_size = rows_ / num_threads;

    for (size_t t = 0; t < num_threads; ++t) {
        size_t start = t * chunk_size;
        size_t end = (t == num_threads - 1) ? rows_ : start + chunk_size;
        threads.emplace_back(worker, start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return result;
}

// Matrix addition
Matrix Matrix::operator+(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrix dimensions do not match for addition");
    }
    Matrix result(rows_, cols_);
    std::vector<std::thread> threads;

    auto worker = [&](size_t start, size_t end) {
        for (size_t i = start; i < end; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                result.set(i, j, get(i, j) + other.get(i, j));
            }
        }
    };

    size_t num_threads = std::thread::hardware_concurrency();
    size_t chunk_size = rows_ / num_threads;

    for (size_t t = 0; t < num_threads; ++t) {
        size_t start = t * chunk_size;
        size_t end = (t == num_threads - 1) ? rows_ : start + chunk_size;
        threads.emplace_back(worker, start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return result;
}

// Matrix subtraction
Matrix Matrix::operator-(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrix dimensions do not match for subtraction");
    }
    Matrix result(rows_, cols_);
    std::vector<std::thread> threads;

    auto worker = [&](size_t start, size_t end) {
        for (size_t i = start; i < end; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                result.set(i, j, get(i, j) - other.get(i, j));
            }
        }
    };

    size_t num_threads = std::thread::hardware_concurrency();
    size_t chunk_size = rows_ / num_threads;

    for (size_t t = 0; t < num_threads; ++t) {
        size_t start = t * chunk_size;
        size_t end = (t == num_threads - 1) ? rows_ : start + chunk_size;
        threads.emplace_back(worker, start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return result;
}

// Scalar multiplication
Matrix Matrix::operator*(double scalar) const {
    Matrix result(rows_, cols_);
    std::vector<std::thread> threads;

    auto worker = [&](size_t start, size_t end) {
        for (size_t i = start; i < end; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                result.set(i, j, get(i, j) * scalar);
            }
        }
    };

    size_t num_threads = std::thread::hardware_concurrency();
    size_t chunk_size = rows_ / num_threads;

    for (size_t t = 0; t < num_threads; ++t) {
        size_t start = t * chunk_size;
        size_t end = (t == num_threads - 1) ? rows_ : start + chunk_size;
        threads.emplace_back(worker, start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return result;
}

// Element-wise multiplication
Matrix Matrix::elementwise_multiplication(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrix dimensions do not match for element-wise multiplication");
    }
    Matrix result(rows_, cols_);
    std::vector<std::thread> threads;

    auto worker = [&](size_t start, size_t end) {
        for (size_t i = start; i < end; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                result.set(i, j, get(i, j) * other.get(i, j));
            }
        }
    };

    size_t num_threads = std::thread::hardware_concurrency();
    size_t chunk_size = rows_ / num_threads;

    for (size_t t = 0; t < num_threads; ++t) {
        size_t start = t * chunk_size;
        size_t end = (t == num_threads - 1) ? rows_ : start + chunk_size;
        threads.emplace_back(worker, start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return result;
}

// Matrix transposition
Matrix Matrix::transpose() const {
    Matrix result(cols_, rows_);
    std::vector<std::thread> threads;

    auto worker = [&](size_t start, size_t end) {
        for (size_t i = start; i < end; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                result.set(j, i, get(i, j));
            }
        }
    };

    size_t num_threads = std::thread::hardware_concurrency();
    size_t chunk_size = rows_ / num_threads;

    for (size_t t = 0; t < num_threads; ++t) {
        size_t start = t * chunk_size;
        size_t end = (t == num_threads - 1) ? rows_ : start + chunk_size;
        threads.emplace_back(worker, start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return result;
}
