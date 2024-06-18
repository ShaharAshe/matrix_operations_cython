from setuptools import setup, Extension
from Cython.Build import cythonize

extensions = [
    Extension(
        "matrix_interface",
        sources=["matrix_interface.pyx", "matrix.cpp"],
        language="c++",
    )
]

setup(
    name="matrix_interface",
    ext_modules=cythonize(extensions),
)
