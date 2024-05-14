import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
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

def draw_2d(solution_files, file_exp_function):
    points = read_csv_to_points_2d(file_exp_function)
    xMin, xMax = getIntervalX(points)
    xValues = np.linspace(xMin, xMax, 1000)

    plt.figure(figsize=(10, 6))
    for file_solution in solution_files:
        solution = read_csv_to_solution(file_solution)
        degree = len(solution) - 1;
        yValues = [approximate_function_2d(solution, x) for x in xValues]
        plt.plot(xValues, yValues, label=f"Degree {degree} Approximation")

    for p in points:
        plt.plot(p.getX(), p.getY(), 'r.')

    plt.xlabel("X Values")
    plt.ylabel("Y Values")
    plt.legend()
    plt.title("Comparison of Approximation Functions")
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python Fxplot.py <experimental_file> <solution_file1> <solution_file2> ...")
        sys.exit(1)

    experimental_file = sys.argv[1]
    solution_files = sys.argv[2:]
    draw_2d(solution_files, experimental_file)
