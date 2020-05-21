import numpy as np
from random import gauss
from random import seed
from const import*


def proc_noise(N):

    np.series = []
    A = 1 * A_input_noise
    seed(1)
    series = [gauss(0.0, 1.0) for i in range(N)]
    for i in range (N):
        series[i] = series[i]*A
    return series

