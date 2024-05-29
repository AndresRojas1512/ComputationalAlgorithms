import numpy as np
from scipy.interpolate import interp1d
import sympy as sym

def f(x):
    return 2 / np.sqrt(2 * np.pi) * np.exp(-x ** 2 / 2)

def simpson(func, a, b, n=200):
    h = (b - a) / (n*2)
    xs = np.array([a + i * h for i in range(n*2 + 1)])
    ys = np.array([func(x) for x in xs])
    s1 = 4 * np.sum([ys[2*i - 1] for i in range(1, n)])
    s2 = 2 * np.sum([ys[2*i] for i in range(1, n - 1)])
    s = (h / 3) * (ys[0] + s1 + s2 + ys[-1])
    return s

def bisect(func, a, b, eps=1e-6):
    eps1 = 5 * eps
    while abs(b - a) >= eps * abs((a + b) / 2) + eps1:
        if func(a) * func((a + b) / 2) < 0:
            b = (a + b) / 2
        else:
            a = (a + b) / 2
    return (a + b) / 2

def laplace(x):
    return simpson(f, 0, x)
