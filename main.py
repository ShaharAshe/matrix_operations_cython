from matrix_interface import Matrix

def print_matrix(matrix, name):
    print(f"{name}:")
    for i in range(matrix.get_rows()):
        for j in range(matrix.get_cols()):
            print(matrix.get(i, j), end=' ')
        print()
    print()

# Create large matrices for heavy tasking
size = 2  # Adjust the size for more complexity
matrix_a = Matrix(size, size)
matrix_b = Matrix(size, size)

# Fill matrices with larger values
matrix_a.fill(5.0)
matrix_b.fill(10.0)

# Perform matrix multiplication
matrix_c = matrix_a.multiply(matrix_b)

# Perform matrix addition
matrix_d = matrix_a.add(matrix_b)

# Perform matrix subtraction
matrix_g = matrix_a.subtract(matrix_b)

# Perform scalar multiplication
matrix_e = matrix_a.scalar_multiply(2.0)

# Perform element-wise multiplication
matrix_f = matrix_a.elementwise_multiply(matrix_b)

# Perform matrix transposition
matrix_h = matrix_a.transpose()

# Print all matrices for verification
print_matrix(matrix_a, "Matrix A")
print_matrix(matrix_b, "Matrix B")
print_matrix(matrix_c, "Matrix C (A * B)")
print_matrix(matrix_d, "Matrix D (A + B)")
print_matrix(matrix_g, "Matrix G (A - B)")
print_matrix(matrix_e, "Matrix E (A * 2.0)")
print_matrix(matrix_f, "Matrix F (A elementwise B)")
print_matrix(matrix_h, "Matrix H (A Transposed)")
