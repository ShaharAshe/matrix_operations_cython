#include <pybind11/pybind11.h>
#include "vector_multithread.h"

namespace py = pybind11;

PYBIND11_MODULE(vector_multithread, m) {
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())  // Constructor
        .def("get", &Matrix::get)  // Get value at position (row, col)
        .def("set", &Matrix::set)  // Set value at position (row, col)
        .def("rows", &Matrix::rows)  // Get number of rows
        .def("cols", &Matrix::cols)  // Get number of columns
        .def("fill", &Matrix::fill)  // Fill matrix with a value
        .def("__mul__", static_cast<Matrix (Matrix::*)(const Matrix&) const>(&Matrix::operator*), py::is_operator())  // Matrix multiplication
        .def("__mul__", static_cast<Matrix (Matrix::*)(double) const>(&Matrix::operator*), py::is_operator())  // Scalar multiplication
        .def("__add__", &Matrix::operator+, py::is_operator())  // Matrix addition
        .def("__sub__", &Matrix::operator-, py::is_operator())  // Matrix subtraction
        .def("transpose", &Matrix::transpose)  // Matrix transposition
        .def("elementwise_multiplication", &Matrix::elementwise_multiplication);  // Element-wise multiplication
}
