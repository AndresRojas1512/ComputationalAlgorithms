import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import math
import sys

class Point:
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

def parseTableToCoordinates3D(points):
    xs = list()
    ys = list()
    zs = list()
    for p in points:
        xs.append(p.getX())
        ys.append(p.getY())
        zs.append(p.getZ())
    return np.array(xs), np.array(ys), np.array(zs)

def draw_3d(solution_files, file_exp_function):
    points = read_csv_to_points_3d(file_exp_function)
    minX, maxX = getIntervalX(points)
    minY, maxY = getIntervalY(points)
    xValues = np.linspace(minX, maxX, 40)
    yValues = np.linspace(minY, maxY, 40)

    fig = plt.figure("3D Approximation Functions")
    axes = fig.add_subplot(projection='3d')

    for file_solution in solution_files:
        solution = read_csv_to_solution(file_solution)
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

        xGrid, yGrid, zGrid = make_2D_matrix()
        axes.plot_surface(xGrid, yGrid, zGrid, alpha=0.5, label=f"Degree {degree} Approximation")

    xpoints, ypoints, zpoints = parseTableToCoordinates3D(points)
    axes.scatter(xpoints, ypoints, zpoints, c='red')
    axes.set_xlabel('OX')
    axes.set_ylabel('OY')
    axes.set_zlabel('OZ')
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python Fxplot.py <experimental_file> <solution_file1> <solution_file2> ...")
        sys.exit(1)

    experimental_file = sys.argv[1]
    solution_files = sys.argv[2:]
    draw_3d(solution_files, experimental_file)
