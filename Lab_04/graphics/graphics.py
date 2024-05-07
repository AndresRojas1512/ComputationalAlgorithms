import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

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

def read_csv_to_solution(file_solution):
    data = pd.read_csv(file_solution, header=None)
    solutions = data[0].tolist()
    return solutions

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

def approximate_function_2d(solution, x):
    y = 0
    for i in range(len(solution)):
        y += solution[i] * x**i
    return y

def approximate_function_3d(solution, degree, x, y):
    result = 0
    c_index = 0
    for i in range(degree + 1):
        for j in range(degree + 1 - i):
            result += solution[c_index] * getValue_2D(x, y, i, j)
            c_index += 1
    return result

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


if __name__ == "__main__":
    # 2D
    experimental_file = '../datasv_01.csv'
    solution_file = '../solution_2d.csv'
    draw_2d(solution_file, experimental_file)

    # 3D
    # experimental_file = '../datadv_01.csv'
    # approximation_file = '../aproxfunction3d.csv'
    # plot_experimental_and_approximation_3d(experimental_file, approximation_file)