import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import math
from scipy.special import erfi
import plotly.express as px
import plotly.graph_objects as go
import sys

def ODESolution(x):
    return ((-(np.exp(0.5) + 1) / erfi(1 / np.sqrt(2))) * erfi(x / np.sqrt(2)) + 1) / np.exp(x ** 2 / 2) + x

def f0(x):
    return 1 - x

def f1(x):
    return x * (1 - x)

def f2(x):
    return x ** 2 * (1 - x)

def f3(x):
    return x ** 3 * (1 - x)

def f4(x):
    return x**4 * (1 - x)

def c0(x):
    return 1 - 4 * x

def c1(x):
    return - 2 + 2 * x - 3 * x**2

def c2(x):
    return 2 - 6 * x + 3 * x**2 - 4 * x**3

def c3(x):
    return 6 * x - 12 * x**2 + 4 * x**3 - 5 * x**4

def c4(x):
    return 12 * x**2 - 20 * x**3 + 5 * x**4 + 6 * x**5

def approximate_ode(n, funcs, poliCoeffs):
    def func(xp):
        return funcs[0](xp) + sum(poliCoeffs[i] * funcs[i + 1](xp) for i in range(n))
    return func

def read_csv_to_solution(file_solution):
    data = pd.read_csv(file_solution, header=None)
    solutions = data[0].tolist()
    return solutions


def draw_ODE(file_solution_2m, file_solution_3m, file_solution_4m):
    solution_2m = read_csv_to_solution(file_solution_2m)
    solution_3m = read_csv_to_solution(file_solution_3m)
    solution_4m = read_csv_to_solution(file_solution_4m)

    x_values = np.linspace(0, 1, 100)

    f_pred2 = approximate_ode(2, [f0, f1, f2], solution_2m)
    f_pred3 = approximate_ode(3, [f0, f1, f2, f3], solution_3m)
    f_pred4 = approximate_ode(4, [f0, f1, f2, f3, f4], solution_4m)

    y_pred2 = [f_pred2(x) for x in x_values]
    y_pred3 = [f_pred3(x) for x in x_values]
    y_pred4 = [f_pred4(x) for x in x_values]

    y_values = [ODESolution(x) for x in x_values]

    plt.figure(figsize=(10, 6))
    plt.plot(x_values, y_values, label="Exact Solution", linewidth=1.0)
    plt.plot(x_values, y_pred2, label="Approximate Solution (Degree 2)", linewidth=1.0)
    plt.plot(x_values, y_pred3, label="Approximate Solution (Degree 3)", linewidth=1.0)
    plt.plot(x_values, y_pred4, label="Approximate Solution (Degree 4)", linewidth=1.0)

    plt.xlabel("X Values")
    plt.ylabel("Y Values")
    plt.legend()
    plt.title("Comparison of ODE Solutions")
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python script.py <solution_2m.csv> <solution_3m.csv> <solution_4m.csv>")
        sys.exit(1)
    draw_ODE(sys.argv[1], sys.argv[2], sys.argv[3])
