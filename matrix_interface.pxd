cdef extern from "matrix.h":
    cdef cppclass Matrix:
        Matrix()
        Matrix(size_t rows, size_t cols)
        Matrix(const Matrix& other)
        Matrix(Matrix&& other) noexcept
        double get(size_t row, size_t col) const
        void set(size_t row, size_t col, double value)
        size_t rows() const
        size_t cols() const
        void fill(double value)
        Matrix operator*(const Matrix& other) const
        Matrix operator+(const Matrix& other) const
        Matrix operator-(const Matrix& other) const
        Matrix operator*(double scalar) const
        Matrix elementwise_multiplication(const Matrix& other) const
        Matrix transpose() const

    Matrix* Matrix_new(size_t rows, size_t cols)
    void Matrix_delete(Matrix* m)
    double Matrix_get(const Matrix* m, size_t row, size_t col)
    void Matrix_set(Matrix* m, size_t row, size_t col, double value)
    size_t Matrix_rows(const Matrix* m)
    size_t Matrix_cols(const Matrix* m)
    void Matrix_fill(Matrix* m, double value)
    Matrix* Matrix_multiply(const Matrix* a, const Matrix* b)
    Matrix* Matrix_transpose(const Matrix* m)
