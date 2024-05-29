import numpy as np
import sympy as sym
from newton import *
from laplace import *
import matplotlib.pyplot as plt

def main():
    # Task 1
    variables = ['x', 'y', 'z']
    functions = ['x**2 + y**2 + z**2 - 1', '2*x**2 + y**2 - 4*z', '3*x**2 - 4*y + z**2']
    func_matrix = sym.Matrix(functions)
    jacobian = func_matrix.jacobian(variables)
    func_matrix = sym.lambdify(sym.symbols(variables), func_matrix)
    jacobian = sym.lambdify(sym.symbols(variables), jacobian)

    approximation_01 = np.array([10.5, 10.5, 10.5])
    approximation_02 = np.array([-10.5, 10.5, 10.5])

    solution_01 = newton(jacobian, func_matrix, approximation_01, 1e-6)
    solution_02 = newton(jacobian, func_matrix, approximation_02, 1e-6)

    print("\tЗадание 1:")
    print("Решение 1: ", solution_01)
    print("Решение 2: ", solution_02)

    # Task 2
    print("\tЗадание 2")
    value = float(input("Значение функции: "))
    print("Аргумент функции: ", bisect(lambda x : laplace(x) - value, 0, 10))

    # Task 3
    print("\tЗадание 3")
    n = 100
    h = 1 / n
    variables_de = [f'y{i}' for i in range(n + 1)]
    x0, xn = 0, 1
    y0, yn = 1, 3
    x = np.linspace(x0, xn, n + 1, endpoint=True)
    functions_de = [f'y0 - {y0}'] + [f'y{i - 1} - 2 * y{i} + y{i + 1} - {h} ** 2 * ({x[i]} ** 2 + y{i} ** 3)' for i in range(1, n)] + [f'y{n} - {yn}']
    func_matrix_de = sym.Matrix(functions_de)
    jacobian_de = func_matrix_de.jacobian(variables_de)

    func_matrix_de = sym.lambdify(sym.symbols(variables_de), func_matrix_de)
    jacobian_de = sym.lambdify(sym.symbols(variables_de), jacobian_de)

    tangent = (yn - y0) / (xn - x0)
    approximation_de = [y0 + tangent * i * h for i in range(n + 1)]
    solution_de = newton(jacobian_de, func_matrix_de, approximation_de, 1e-6)
    # print("Значение проксимации: ", solution_de)

    # plt.plot(x, start_approx, label="Start approx")
    plt.plot(x, solution_de, label="Решение")
    plt.legend()
    plt.grid()
    plt.show()

if __name__ == "__main__":
    main()

# approximation_01 = np.array([0.5, 0.5, 0.5])
# approximation_02 = np.array([-0.5, 0.5, 0.5])