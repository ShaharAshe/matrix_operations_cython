import random
from matrix_interface import PyMatrix as Matrix

def create_matrix(rows, cols):
    return Matrix(rows, cols)

def fill_matrix(matrix, value):
    matrix.fill(value)

def fill_matrix_random(matrix):
    for i in range(matrix.get_rows()):
        for j in range(matrix.get_cols()):
            matrix.set(i, j, random.uniform(0, 100))

def perform_operation(operation, matrix_1, matrix_2):
    if operation == "Multiply":
        return matrix_1.multiply(matrix_2)
    elif operation == "Add":
        return matrix_1.add(matrix_2)
    elif operation == "Subtract":
        return matrix_1.subtract(matrix_2)
    elif operation == "Element-wise Multiply":
        return matrix_1.elementwise_multiply(matrix_2)

def delete_matrix(matrices, name):
    del matrices[name]

def print_matrix(result_text, matrix, name):
    result_text.insert("end", f"{name}:\n")
    for i in range(matrix.get_rows()):
        for j in range(matrix.get_cols()):
            result_text.insert("end", f"{matrix.get(i, j):.2f} ")
        result_text.insert("end", "\n")
    result_text.insert("end", "\n")
