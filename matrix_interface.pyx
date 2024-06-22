from libc.stdlib cimport malloc, free
cimport cython
from matrix_interface cimport Matrix, Matrix_new, Matrix_delete, Matrix_get, Matrix_set, Matrix_rows, Matrix_cols, Matrix_fill, Matrix_multiply, Matrix_transpose

cdef class PyMatrix:
    cdef Matrix* c_matrix

    def __cinit__(self, size_t rows=0, size_t cols=0):
        if rows > 0 and cols > 0:
            self.c_matrix = Matrix_new(rows, cols)
        else:
            self.c_matrix = NULL

    def __dealloc__(self):
        if self.c_matrix:
            Matrix_delete(self.c_matrix)

    cpdef double get(self, size_t row, size_t col):
        return Matrix_get(self.c_matrix, row, col)

    cpdef void set(self, size_t row, size_t col, double value):
        Matrix_set(self.c_matrix, row, col, value)

    cpdef size_t get_rows(self):
        return Matrix_rows(self.c_matrix)

    cpdef size_t get_cols(self):
        return Matrix_cols(self.c_matrix)

    cpdef void fill(self, double value):
        Matrix_fill(self.c_matrix, value)

    @staticmethod
    cdef PyMatrix _create_from_matrix(Matrix* c_matrix):
        cdef PyMatrix result = PyMatrix.__new__(PyMatrix)
        result.c_matrix = c_matrix
        return result

    cpdef PyMatrix multiply(self, PyMatrix other):
        cdef Matrix* result_matrix = Matrix_multiply(self.c_matrix, other.c_matrix)
        return PyMatrix._create_from_matrix(result_matrix)

    cpdef PyMatrix add(self, PyMatrix other):
        if self.get_rows() != other.get_rows() or self.get_cols() != other.get_cols():
            raise ValueError("Matrix dimensions do not match for addition")
        cdef Matrix* result_matrix = Matrix_new(self.get_rows(), self.get_cols())
        cdef PyMatrix result = PyMatrix._create_from_matrix(result_matrix)
        cdef size_t i, j
        for i in range(self.get_rows()):
            for j in range(self.get_cols()):
                result.set(i, j, self.get(i, j) + other.get(i, j))
        return result

    cpdef PyMatrix subtract(self, PyMatrix other):
        if self.get_rows() != other.get_rows() or self.get_cols() != other.get_cols():
            raise ValueError("Matrix dimensions do not match for subtraction")
        cdef Matrix* result_matrix = Matrix_new(self.get_rows(), self.get_cols())
        cdef PyMatrix result = PyMatrix._create_from_matrix(result_matrix)
        cdef size_t i, j
        for i in range(self.get_rows()):
            for j in range(self.get_cols()):
                result.set(i, j, self.get(i, j) - other.get(i, j))
        return result

    cpdef PyMatrix scalar_multiply(self, double scalar):
        cdef Matrix* result_matrix = Matrix_new(self.get_rows(), self.get_cols())
        cdef PyMatrix result = PyMatrix._create_from_matrix(result_matrix)
        cdef size_t i, j
        for i in range(self.get_rows()):
            for j in range(self.get_cols()):
                result.set(i, j, self.get(i, j) * scalar)
        return result

    cpdef PyMatrix elementwise_multiply(self, PyMatrix other):
        if self.get_rows() != other.get_rows() or self.get_cols() != other.get_cols():
            raise ValueError("Matrix dimensions do not match for elementwise multiplication")
        cdef Matrix* result_matrix = Matrix_new(self.get_rows(), self.get_cols())
        cdef PyMatrix result = PyMatrix._create_from_matrix(result_matrix)
        cdef size_t i, j
        for i in range(self.get_rows()):
            for j in range(self.get_cols()):
                result.set(i, j, self.get(i, j) * other.get(i, j))
        return result

    cpdef PyMatrix transpose(self):
        cdef Matrix* result_matrix = Matrix_transpose(self.c_matrix)
        return PyMatrix._create_from_matrix(result_matrix)
