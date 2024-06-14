# matrix_interface.pyx
from libc.stdlib cimport malloc, free
cimport cython

cdef class Matrix:
    cdef:
        double* data
        size_t rows, cols

    def __cinit__(self, size_t rows, size_t cols):
        self.rows = rows
        self.cols = cols
        self.data = <double*> malloc(self.rows * self.cols * sizeof(double))

    def __dealloc__(self):
        free(self.data)

    cpdef double get(self, size_t row, size_t col):
        return self.data[row * self.cols + col]

    cpdef void set(self, size_t row, size_t col, double value):
        self.data[row * self.cols + col] = value

    cpdef size_t get_rows(self):
        return self.rows

    cpdef size_t get_cols(self):
        return self.cols

    cpdef void fill(self, double value):
        cdef size_t i
        for i in range(self.rows * self.cols):
            self.data[i] = value

    cpdef Matrix multiply(self, Matrix other):
        if self.cols != other.get_rows():
            raise ValueError("Matrix dimensions do not match for multiplication")
        cdef Matrix result = Matrix(self.rows, other.get_cols())
        cdef size_t i, j, k
        cdef double sum
        for i in range(self.rows):
            for j in range(other.get_cols()):
                sum = 0.0
                for k in range(self.cols):
                    sum += self.get(i, k) * other.get(k, j)
                result.set(i, j, sum)
        return result

    cpdef Matrix add(self, Matrix other):
        if self.rows != other.get_rows() or self.cols != other.get_cols():
            raise ValueError("Matrix dimensions do not match for addition")
        cdef Matrix result = Matrix(self.rows, self.cols)
        cdef size_t i, j
        for i in range(self.rows):
            for j in range(self.cols):
                result.set(i, j, self.get(i, j) + other.get(i, j))
        return result

    cpdef Matrix subtract(self, Matrix other):
        if self.rows != other.get_rows() or self.cols != other.get_cols():
            raise ValueError("Matrix dimensions do not match for subtraction")
        cdef Matrix result = Matrix(self.rows, self.cols)
        cdef size_t i, j
        for i in range(self.rows):
            for j in range(self.cols):
                result.set(i, j, self.get(i, j) - other.get(i, j))
        return result

    cpdef Matrix scalar_multiply(self, double scalar):
        cdef Matrix result = Matrix(self.rows, self.cols)
        cdef size_t i, j
        for i in range(self.rows):
            for j in range(self.cols):
                result.set(i, j, self.get(i, j) * scalar)
        return result

    cpdef Matrix elementwise_multiply(self, Matrix other):
        if self.rows != other.get_rows() or self.cols != other.get_cols():
            raise ValueError("Matrix dimensions do not match for elementwise multiplication")
        cdef Matrix result = Matrix(self.rows, self.cols)
        cdef size_t i, j
        for i in range(self.rows):
            for j in range(self.cols):
                result.set(i, j, self.get(i, j) * other.get(i, j))
        return result

    cpdef Matrix transpose(self):
        cdef Matrix result = Matrix(self.cols, self.rows)
        cdef size_t i, j
        for i in range(self.rows):
            for j in range(self.cols):
                result.set(j, i, self.get(i, j))
        return result
