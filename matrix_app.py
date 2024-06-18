import tkinter as tk
from tkinter import ttk, simpledialog
from matrix_operations import create_matrix, fill_matrix, fill_matrix_random, perform_operation, print_matrix, delete_matrix

class MatrixApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Matrix Operations")
        self.matrices = {}
        self.create_widgets()

    def create_widgets(self):
        self.size_label = ttk.Label(self.root, text="Matrix Rows:")
        self.size_label.grid(column=0, row=0, padx=5, pady=10)

        self.rows_var = tk.IntVar(value=2)
        self.rows_entry = ttk.Entry(self.root, textvariable=self.rows_var)
        self.rows_entry.grid(column=1, row=0, padx=5, pady=10)

        self.cols_label = ttk.Label(self.root, text="Matrix Columns:")
        self.cols_label.grid(column=2, row=0, padx=5, pady=10)

        self.cols_var = tk.IntVar(value=2)
        self.cols_entry = ttk.Entry(self.root, textvariable=self.cols_var)
        self.cols_entry.grid(column=3, row=0, padx=5, pady=10)

        self.matrix_name_label = ttk.Label(self.root, text="Matrix Name:")
        self.matrix_name_label.grid(column=4, row=0, padx=5, pady=10)

        self.matrix_name_var = tk.StringVar(value="A")
        self.matrix_name_entry = ttk.Entry(self.root, textvariable=self.matrix_name_var)
        self.matrix_name_entry.grid(column=5, row=0, padx=5, pady=10)

        self.create_button = ttk.Button(self.root, text="Create Matrix", command=self.create_matrix)
        self.create_button.grid(column=6, row=0, padx=5, pady=10)

        self.fill_label = ttk.Label(self.root, text="Fill Value:")
        self.fill_label.grid(column=0, row=1, padx=5, pady=10)

        self.fill_var = tk.DoubleVar(value=0.0)
        self.fill_entry = ttk.Entry(self.root, textvariable=self.fill_var)
        self.fill_entry.grid(column=1, row=1, padx=5, pady=10)

        self.fill_button = ttk.Button(self.root, text="Fill Matrix", command=self.fill_matrix)
        self.fill_button.grid(column=2, row=1, padx=5, pady=10)

        self.random_fill_button = ttk.Button(self.root, text="Fill with Random", command=self.fill_matrix_random)
        self.random_fill_button.grid(column=3, row=1, padx=5, pady=10)

        self.operation_label = ttk.Label(self.root, text="Operations:")
        self.operation_label.grid(column=0, row=2, padx=5, pady=10)

        self.operation_var = tk.StringVar()
        self.operation_menu = ttk.Combobox(self.root, textvariable=self.operation_var)
        self.operation_menu['values'] = ("Multiply", "Add", "Subtract", "Scalar Multiply", "Element-wise Multiply", "Transpose")
        self.operation_menu.grid(column=1, row=2, padx=5, pady=10, columnspan=2)

        self.scalar_label = ttk.Label(self.root, text="Scalar Value:")
        self.scalar_label.grid(column=3, row=2, padx=5, pady=10)
        self.scalar_var = tk.DoubleVar(value=2.0)
        self.scalar_entry = ttk.Entry(self.root, textvariable=self.scalar_var)
        self.scalar_entry.grid(column=4, row=2, padx=5, pady=10)

        self.execute_button = ttk.Button(self.root, text="Execute", command=self.execute_operation)
        self.execute_button.grid(column=0, row=3, padx=5, pady=10, columnspan=2)

        self.clear_button = ttk.Button(self.root, text="Clear Output", command=self.clear_output)
        self.clear_button.grid(column=2, row=3, padx=5, pady=10, columnspan=2)

        self.feedback_label = ttk.Label(self.root, text="", foreground="blue")
        self.feedback_label.grid(column=0, row=5, padx=5, pady=10, columnspan=7)

        self.result_text = tk.Text(self.root, width=80, height=20)
        self.result_text.grid(column=0, row=6, padx=10, pady=10, columnspan=7)

        self.matrix_listbox_label = ttk.Label(self.root, text="Created Matrices:")
        self.matrix_listbox_label.grid(column=0, row=7, padx=10, pady=10, columnspan=7)

        self.matrix_listbox = tk.Listbox(self.root, selectmode=tk.SINGLE)
        self.matrix_listbox.grid(column=0, row=8, padx=10, pady=10, columnspan=7)

        self.show_button = ttk.Button(self.root, text="Show Selected Matrix", command=self.show_selected_matrix)
        self.show_button.grid(column=0, row=9, padx=10, pady=10, columnspan=7)

        self.delete_button = ttk.Button(self.root, text="Delete Matrix", command=self.delete_matrix)
        self.delete_button.grid(column=0, row=10, padx=5, pady=10, columnspan=7)

    def create_matrix(self):
        rows = self.rows_var.get()
        cols = self.cols_var.get()
        name = self.matrix_name_var.get().strip()
        if not name:
            self.feedback_label.config(text="Matrix name cannot be empty")
            return
        if name in self.matrices:
            self.feedback_label.config(text=f"Matrix {name} already exists")
        else:
            self.matrices[name] = create_matrix(rows, cols)
            self.matrix_listbox.insert(tk.END, name)
            self.feedback_label.config(text=f"Matrix {name} created successfully")

    def fill_matrix(self):
        name = self.matrix_name_var.get().strip()
        if not name:
            self.feedback_label.config(text="Matrix name cannot be empty")
            return
        fill_value = self.fill_var.get()
        if name not in self.matrices:
            self.feedback_label.config(text=f"Matrix {name} does not exist")
            return
        fill_matrix(self.matrices[name], fill_value)
        print_matrix(self.result_text, self.matrices[name], f"Matrix {name}")
        self.feedback_label.config(text=f"Matrix {name} filled with value {fill_value}")

    def fill_matrix_random(self):
        name = self.matrix_name_var.get().strip()
        if not name:
            self.feedback_label.config(text="Matrix name cannot be empty")
            return
        if name not in self.matrices:
            self.feedback_label.config(text=f"Matrix {name} does not exist")
            return
        fill_matrix_random(self.matrices[name])
        print_matrix(self.result_text, self.matrices[name], f"Matrix {name} (Filled with Random Values)")
        self.feedback_label.config(text=f"Matrix {name} filled with random values")

    def clear_output(self):
        self.result_text.delete(1.0, tk.END)

    def show_selected_matrix(self):
        selected = self.matrix_listbox.curselection()
        if not selected:
            self.feedback_label.config(text="No matrix selected")
            return
        name = self.matrix_listbox.get(selected[0])
        print_matrix(self.result_text, self.matrices[name], f"Matrix {name}")
        self.feedback_label.config(text=f"Displayed Matrix {name}")

    def delete_matrix(self):
        selected = self.matrix_listbox.curselection()
        if not selected:
            self.feedback_label.config(text="No matrix selected")
            return
        name = self.matrix_listbox.get(selected[0])
        delete_matrix(self.matrices, name)
        self.matrix_listbox.delete(selected)
        self.feedback_label.config(text=f"Deleted Matrix {name}")
        self.clear_output()

    def execute_operation(self):
        operation = self.operation_var.get()
        if not self.matrices:
            self.feedback_label.config(text="No matrices available. Create matrices first.")
            return

        try:
            if operation in ["Multiply", "Add", "Subtract", "Element-wise Multiply"]:
                self.choose_and_execute_binary_operation(operation)
            elif operation == "Scalar Multiply":
                self.choose_and_execute_scalar_multiply()
            elif operation == "Transpose":
                self.choose_and_execute_transpose()
        except Exception as e:
            self.feedback_label.config(text=f"Error: {str(e)}")

    def choose_and_execute_binary_operation(self, operation):
        if len(self.matrices) < 2:
            self.feedback_label.config(text="At least two matrices are needed for this operation.")
            return

        selected_1 = self.select_matrix("Select the first matrix")
        if not selected_1:
            self.feedback_label.config(text="First matrix not selected.")
            return
        selected_2 = self.select_matrix("Select the second matrix")
        if not selected_2:
            self.feedback_label.config(text="Second matrix not selected.")
            return

        matrix_1 = self.matrices[selected_1]
        matrix_2 = self.matrices[selected_2]
        result = perform_operation(operation, matrix_1, matrix_2)
        print_matrix(self.result_text, result, f"Result of {selected_1} {operation} {selected_2}")

    def choose_and_execute_scalar_multiply(self):
        selected = self.select_matrix("Select the matrix for scalar multiplication")
        if not selected:
            self.feedback_label.config(text="Matrix not selected.")
            return

        matrix = self.matrices[selected]
        scalar = self.scalar_var.get()
        result = matrix.scalar_multiply(scalar)
        print_matrix(self.result_text, result, f"Result of {selected} * {scalar}")

    def choose_and_execute_transpose(self):
        selected = self.select_matrix("Select the matrix to transpose")
        if not selected:
            self.feedback_label.config(text="Matrix not selected.")
            return

        matrix = self.matrices[selected]
        result = matrix.transpose()
        print_matrix(self.result_text, result, f"Result of Transpose({selected})")

    def select_matrix(self, prompt):
        matrix_names = list(self.matrices.keys())
        selected_matrix = simpledialog.askstring("Input", f"{prompt}\nAvailable matrices: {', '.join(matrix_names)}")
        if selected_matrix not in self.matrices:
            return None
        return selected_matrix
