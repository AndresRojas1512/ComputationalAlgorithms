def jacobian(*y, step):
    N = len(y)
    res = []
    res.append([1] + [0] * (N - 1))
    for i in range(1, N - 1):
        res.append([0] * (i - 1) + [1 / step**2] + [-2/step**2 - 3 * y[i]**2]  + [1/step**2] + [0] * (N - i - 2))
    res.append([0] * (N - 1) + [1])
    return res

def f(n, y0, y1, step):
    if n == 0:
        def resf(*y):
            return y[0] - y0
    elif n == N:
        def resf(*y):
            return y[n] - y1
    else:
        def resf(*y):
            return (y[n - 1] + -2 * y[n] + y[n + 1]) / step**2 - y[n]**3 - x[n]**2
    return resf