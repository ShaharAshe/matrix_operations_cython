# Matrix Operations with Cython 📊

This project demonstrates how to perform matrix operations using Cython for improved performance.

![license](https://img.shields.io/github/license/ShaharAshe/Cryptography_modules)

## 🛠️ Setup

### Install dependencies

1. Update your package list and install essential build tools and Python development headers:

    ```sh
    sudo apt-get update
    sudo apt-get install -y build-essential python3-dev python3-pip
    ```

2. Install `Cython` and `notebook` via pip:

    ```sh
    pip3 install cython notebook
    ```

### Compile the shared library

#### For Linux

1. Compile the shared library from the C++ and header files:

    ```sh
    gcc -shared -o libmatrix.so -fPIC matrix.cpp
    ```

#### For Windows

1. Compile the shared library from the C++ and header files:

    ```sh
    g++ -shared -o matrix.dll -fPIC matrix.cpp
    ```

### Compile the Cython extension

1. Run the setup script to build the Cython extension:

    ```sh
    python3 setup.py build_ext --inplace
    ```

### Run Jupyter Notebook

1. Start Jupyter Notebook to run the example notebook:

    ```sh
    jupyter notebook matrix_operations.ipynb
    ```

## 📐 Matrix Operations

The following matrix operations are implemented:

- Matrix multiplication
- Matrix addition
- Matrix subtraction
- Scalar multiplication
- Element-wise multiplication
- Matrix transposition

## Usage

To see the matrix operations in action, you can use either the Jupyter Notebook for interactive exploration or the standalone application.

### Jupyter Notebook

The `matrix_operations.ipynb` notebook demonstrates how to create matrices and perform various operations interactively. It includes examples of:

- Creating large matrices for heavy tasking.
- Filling matrices with larger values.
- Performing matrix multiplication, addition, subtraction, scalar multiplication, element-wise multiplication, and transposition.
- Printing all matrices for verification.

To run the notebook:

```sh
jupyter notebook matrix_operations.ipynb
```

### Standalone Application

The standalone application provides a graphical interface for performing matrix operations. To run the application:

```sh
python3 main.py
```

The application allows you to:

- Create matrices with specified rows and columns.
- Fill matrices with specific values or random values.
- Perform operations such as multiplication, addition, subtraction, scalar multiplication, element-wise multiplication, and transposition.
- View and manage created matrices.

## 📁 Files

- `matrix_interface.pyx`: Contains the Cython code for matrix operations.
- `matrix_interface.pxd`: Contains the corresponding declarations for the functions.
- `setup.py`: The setup script to build the Cython extension.
- `matrix.cpp`: The C++ source file for matrix operations.
- `matrix.h`: The header file for matrix operations.
- `matrix_operations.ipynb`: Jupyter Notebook for interactive exploration of matrix operations.
- `main.py`: Entry point for the standalone application.
- `matrix_app.py`: Contains the `MatrixApp` class and the main application logic.
- `matrix_operations.py`: Contains the logic for performing matrix operations.

## 👥 Authors

- David Zaydenberg
  - Email: [Davidzay@edu.hac.ac.il](mailto:Davidzay@edu.hac.ac.il)
- Shahar Asher
  - Email: [Shaharas@edu.hac.ac.il](mailto:Shaharas@edu.hac.ac.il)

## 📜 License

This project is licensed under the MIT License - see the `LICENSE` file for details.

## 🐍 Python Version

This project is compatible with Python 3.11.9.
