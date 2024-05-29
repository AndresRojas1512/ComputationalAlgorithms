import numpy as np
import sympy as ssym

def newton(jacobian, func_matrix, start_approximation, epsilon):
    vars_n = len(start_approximation)
    coefficients = jacobian(*start_approximation)
    func_values = -func_matrix(*start_approximation)
    deltas = np.linalg.solve(coefficients, func_values).reshape((vars_n,))
    approximation = start_approximation + deltas
    while any(map(lambda x : abs(x) >= epsilon, deltas / approximation)):
        coefficients = jacobian(*approximation)
        func_values = -func_matrix(*approximation)
        deltas = np.linalg.solve(coefficients, func_values).reshape((vars_n,))
        approximation += deltas
    return approximation

