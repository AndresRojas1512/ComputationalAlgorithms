import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import math
from scipy.special import erfi
import plotly.express as px
import plotly.graph_objects as go

def ODESolution(x):
    return ((-(np.exp(0.5) + 1) / erfi(1 / np.sqrt(2))) * erfi(x / np.sqrt(2)) + 1) / np.exp(x ** 2 / 2) + x

class Point:
    x: float
    y: float
    z: float
    weight: float

    def __init__(self, x, y, z, weight):
        self.x = x
        self.y = y
        self.z = z
        self.weight = weight

    def getX(self):
        return self.x

    def getY(self):
        return self.y

    def getZ(self):
        return self.z

    def getWeight(self):
        return self.weight

    def setX(self, x):
        self.x = x

    def setY(self, y):
        self.y = y

    def setZ(self, z):
        self.z = z

    def setWeight(self, weight):
        self.weight = weight

def read_csv_to_solution(file_solution):
    data = pd.read_csv(file_solution, header=None)
    solutions = data[0].tolist()
    return solutions

def read_csv_to_points_2d(file_exp_function):
    data = pd.read_csv(file_exp_function)
    points = []
    for index, row in data.iterrows():
        x = row['x']
        y = row['y']
        weight = row['weight']
        point = Point(x, y, 0, weight)
        points.append(point)
    return points

def approximate_function_2d(solution, x):
    y = 0
    for i in range(len(solution)):
        y += solution[i] * x**i
    return y

def draw_2d(file_solution, file_exp_function):
    points = read_csv_to_points_2d(file_exp_function)
    solution = read_csv_to_solution(file_solution)
    xMin, xMax = getIntervalX(points)
    xValues = np.linspace(xMin, xMax, 40)
    yValues = [approximate_function_2d(solution, x) for x in xValues]
    for p in points:
        plt.plot(p.getX(), p.getY(), 'r.')
    plt.plot(xValues, yValues, 'r', label="y = f(x)")
    plt.legend()
    plt.show()

def parseTableToCoordinates3D(points):
    xs = list()
    ys = list()
    zs = list()
    for p in points:
        xs.append(p.getX())
        ys.append(p.getY())
        zs.append(p.getZ())
    return np.array(xs), np.array(ys), np.array(zs)


def read_csv_to_points_3d(file_exp_function):
    data = pd.read_csv(file_exp_function)
    points = []
    for index, row in data.iterrows():
        x = row['x']
        y = row['y']
        z = row['z']
        weight = row['weight']
        point = Point(x, y, z, weight)
        points.append(point)
    return points

def getIntervalX(table):
    minim = table[0].getX()
    maxim = table[0].getX()
    for p in table:
        value = p.getX()
        if value > maxim:
            maxim = value
        if value < minim:
            minim = value
    return minim, maxim

def getIntervalY(table):
    minim = table[0].getY()
    maxim = table[0].getY()
    for p in table:
        value = p.getY()
        if value > maxim:
            maxim = value
        if value < minim:
            minim = value
    return minim, maxim

def getValue_2D(x, y, powx, powy):
    return x**powx * y**powy


def approximate_function_3d(solution, degree, x, y):
    result = 0
    c_index = 0
    for i in range(degree + 1):
        for j in range(degree + 1 - i):
            result += solution[c_index] * getValue_2D(x, y, i, j)
            c_index += 1
    return result

def find_degree(equations):
    a = 1
    b = 3
    c = 2 - 2 * equations
    discriminant = b**2 - 4 * a * c
    if discriminant < 0:
        return None
    root1 = (-b + math.sqrt(discriminant)) / (2 * a)
    root2 = (-b - math.sqrt(discriminant)) / (2 * a)
    possible_degrees = [int(root) for root in (root1, root2) if root >= 0 and root.is_integer()]
    return max(possible_degrees, default=None)


def draw_3d(file_solution, file_exp_function):
    points = read_csv_to_points_3d(file_exp_function)
    solution = read_csv_to_solution(file_solution)
    minX, maxX = getIntervalX(points)
    minY, maxY = getIntervalY(points)
    xValues = np.linspace(minX, maxX, 40)
    yValues = np.linspace(minY, maxY, 40)
    degree = find_degree(len(solution))
    zValues = [approximate_function_3d(solution, degree, xValues[i], yValues[i]) for i in range(len(xValues))]


    def make_2D_matrix():
        xGrid, yGrid = np.meshgrid(xValues, yValues)
        zGrid = np.array([
            [
                approximate_function_3d(
                    solution,
                    degree,
                    xGrid[i][j],
                    yGrid[i][j]
                ) for j in range(len(xValues))
            ] for i in range(len(yValues))
        ])
        return xGrid, yGrid, zGrid

    fig = plt.figure("График функции, полученный аппроксимации наименьших квадратов")
    xpoints, ypoints, zpoints = parseTableToCoordinates3D(points)
    axes = fig.add_subplot(projection='3d')
    axes.scatter(xpoints, ypoints, zpoints, c='red')
    axes.set_xlabel('OX')
    axes.set_ylabel('OY')
    axes.set_zlabel('OZ')
    xValues, yValues, zValues = make_2D_matrix()
    print("xValues: ", xValues)
    print("yValues: ", yValues)
    print("zValues: ", zValues)
    axes.plot_surface(xValues, yValues, zValues)
    plt.show()

# ODE
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

def draw_ODE(file_solution_2m, file_solution_3m, file_solution_4m):
    # Assuming read_csv_to_solution returns a list of coefficients
    solution_2m = read_csv_to_solution(file_solution_2m)
    solution_3m = read_csv_to_solution(file_solution_3m)
    solution_4m = read_csv_to_solution(file_solution_4m)

    x_values = np.linspace(0, 1, 100)

    # Replace with the appropriate functions that create approximated solutions
    f_pred2 = approximate_ode(2, [f0, f1, f2], solution_2m)
    f_pred3 = approximate_ode(3, [f0, f1, f2, f3], solution_3m)
    f_pred4 = approximate_ode(4, [f0, f1, f2, f3, f4], solution_4m)

    y_pred2 = [f_pred2(x) for x in x_values]
    y_pred3 = [f_pred3(x) for x in x_values]
    y_pred4 = [f_pred4(x) for x in x_values]

    y_values = [ODESolution(x) for x in x_values]

    # Create a new figure
    plt.figure(figsize=(10, 6))

    # Plot the actual and approximated solutions with a thinner line
    plt.plot(x_values, y_values, label="Exact Solution", linewidth=1.0)
    plt.plot(x_values, y_pred2, label="Approximate Solution (Degree 2)", linewidth=1.0)
    plt.plot(x_values, y_pred3, label="Approximate Solution (Degree 3)", linewidth=1.0)
    plt.plot(x_values, y_pred4, label="Approximate Solution (Degree 4)", linewidth=1.0)

    # Add labels, legend, and title
    plt.xlabel("X Values")
    plt.ylabel("Y Values")
    plt.legend()
    plt.title("Comparison of ODE Solutions")

    # Display the plot
    plt.grid(True)
    plt.show()


#----------------------

if __name__ == "__main__":
    # 2D
    # experimental_file = '../datasv_01.csv'
    # solution_file = '../solution_2d.csv'
    # draw_2d(solution_file, experimental_file)

    # 3D
    # experimental_file = '../datadv_01.csv'
    # solution_file = '../solution_3d.csv'
    # draw_3d(solution_file, experimental_file)

    # ODE
    solution_file_2m = '../solution_2m.csv'
    solution_file_3m = '../solution_3m.csv'
    solution_file_4m = '../solution_4m.csv'
    draw_ODE(solution_file_2m, solution_file_3m, solution_file_4m)