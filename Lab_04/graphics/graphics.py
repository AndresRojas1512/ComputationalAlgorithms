import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import math

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
#----------------------

if __name__ == "__main__":
    # 2D
    # experimental_file = '../datasv_01.csv'
    # solution_file = '../solution_2d.csv'
    # draw_2d(solution_file, experimental_file)

    # 3D
    experimental_file = '../datadv_01.csv'
    solution_file = '../solution_3d.csv'
    draw_3d(solution_file, experimental_file)