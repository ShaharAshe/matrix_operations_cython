from libc.stdlib cimport malloc, free
cimport cython

cdef class Matrix:
    """
    A class that represents a matrix with basic operations such as addition, subtraction,
    multiplication, scalar multiplication, element-wise multiplication, and transposition.
    """
    
    cdef:
        double* data  # Pointer to the matrix data stored in a contiguous block of memory
        size_t rows, cols  # Number of rows and columns in the matrix

    def __cinit__(self, size_t rows, size_t cols):
        """
        Initialize the matrix with the given number of rows and columns.
        Allocate memory for the matrix data.

        :param rows: Number of rows in the matrix
        :param cols: Number of columns in the matrix
        """
        self.rows = rows
        self.cols = cols
        self.data = <double*> malloc(self.rows * self.cols * sizeof(double))
        if self.data == NULL:
            raise MemoryError("Failed to allocate memory for matrix data")

    def __dealloc__(self):
        """
        Deallocate the memory used for the matrix data.
        """
        if self.data is not NULL:
            free(self.data)

    cpdef double get(self, size_t row, size_t col):
        """
        Get the value at the specified row and column in the matrix.

        :param row: Row index
        :param col: Column index
        :return: Value at the specified position
        """
        if row >= self.rows or col >= self.cols:
            raise IndexError("Matrix index out of range")
        return self.data[row * self.cols + col]

    cpdef void set(self, size_t row, size_t col, double value):
        """
        Set the value at the specified row and column in the matrix.

        :param row: Row index
        :param col: Column index
        :param value: Value to set at the specified position
        """
        if row >= self.rows or col >= self.cols:
            raise IndexError("Matrix index out of range")
        self.data[row * self.cols + col] = value

    cpdef size_t get_rows(self):
        """
        Get the number of rows in the matrix.

        :return: Number of rows
        """
        return self.rows

    cpdef size_t get_cols(self):
        """
        Get the number of columns in the matrix.

        :return: Number of columns
        """
        return self.cols

    cpdef void fill(self, double value):
        """
        Fill the entire matrix with the specified value.

        :param value: Value to fill the matrix with
        """
        cdef size_t i
        for i in range(self.rows * self.cols):
            self.data[i] = value

    cpdef Matrix multiply(self, Matrix other):
        """
        Perform matrix multiplication with another matrix.

        :param other: The matrix to multiply with
        :return: Resulting matrix after multiplication
        :raises ValueError: If the dimensions of the matrices do not match for multiplication
        """
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
        """
        Perform matrix addition with another matrix.

        :param other: The matrix to add
        :return: Resulting matrix after addition
        :raises ValueError: If the dimensions of the matrices do not match for addition
        """
        if self.rows != other.get_rows() or self.cols != other.get_cols():
            raise ValueError("Matrix dimensions do not match for addition")
        cdef Matrix result = Matrix(self.rows, self.cols)
        cdef size_t i, j
        for i in range(self.rows):
            for j in range(self.cols):
                result.set(i, j, self.get(i, j) + other.get(i, j))
        return result

    cpdef Matrix subtract(self, Matrix other):
        """
        Perform matrix subtraction with another matrix.

        :param other: The matrix to subtract
        :return: Resulting matrix after subtraction
        :raises ValueError: If the dimensions of the matrices do not match for subtraction
        """
        if self.rows != other.get_rows() or self.cols != other.get_cols():
            raise ValueError("Matrix dimensions do not match for subtraction")
        cdef Matrix result = Matrix(self.rows, self.cols)
        cdef size_t i, j
        for i in range(self.rows):
            for j in range(self.cols):
                result.set(i, j, self.get(i, j) - other.get(i, j))
        return result

    cpdef Matrix scalar_multiply(self, double scalar):
        """
        Perform scalar multiplication on the matrix.

        :param scalar: The scalar value to multiply each element by
        :return: Resulting matrix after scalar multiplication
        """
        cdef Matrix result = Matrix(self.rows, self.cols)
        cdef size_t i, j
        for i in range(self.rows):
            for j in range(self.cols):
                result.set(i, j, self.get(i, j) * scalar)
        return result

    cpdef Matrix elementwise_multiply(self, Matrix other):
        """
        Perform element-wise multiplication with another matrix.

        :param other: The matrix to element-wise multiply with
        :return: Resulting matrix after element-wise multiplication
        :raises ValueError: If the dimensions of the matrices do not match for element-wise multiplication
        """
        if self.rows != other.get_rows() or self.cols != other.get_cols():
            raise ValueError("Matrix dimensions do not match for elementwise multiplication")
        cdef Matrix result = Matrix(self.rows, self.cols)
        cdef size_t i, j
        for i in range(self.rows):
            for j in range(self.cols):
                result.set(i, j, self.get(i, j) * other.get(i, j))
        return result

    cpdef Matrix transpose(self):
        """
        Transpose the matrix.

        :return: Transposed matrix
        """
        cdef Matrix result = Matrix(self.cols, self.rows)
        cdef size_t i, j
        for i in range(self.rows):
            for j in range(self.cols):
                result.set(j, i, self.get(i, j))
        return result
