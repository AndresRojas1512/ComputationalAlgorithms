import numpy as np
from scipy.interpolate import interp1d
import sympy as sym

def f(x):
    return 2 / np.sqrt(2 * np.pi) * np.exp(-x ** 2 / 2)

def simpson(x, f):
    def symfunc(a, b):
        return ((b - a) / 6) * (f(a) + 4 * f((a + b) / 2) + f(b))
    return sum(symfunc(x[i], x[i + 1]) for i in range(len(x) - 1))

def bisection(f, y, a, b, maxIter=100, epsilon=1e-6):
    n = 1
    while n <= maxIter:
        c = (a + b) / 2
        if abs(f(c) - y) < epsilon:
            return c
        if (f(a) - y) * (f(c) - y) < 0:
            b = c
        else:
            a = c
        n += 1
    return (a + b) / 2

def laplace(x, integralCount=100):
    def underIntegral(x):
        return np.exp(-x ** 2 / 2)
    intx = np.linspace(0, x, integralCount + 1)
    return (2 / np.sqrt(2 * np.pi)) * simpson(intx, underIntegral)