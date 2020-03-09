import numpy as np

def rms(data):
    '''Расчет RMS по входному массиву '''
    ms = 0
    for element in range (len(data)):
        ms += np.sqrt(np.mean(data[element]**2))
    ms = ms / len(data)
    rms = np.sqrt(ms)
    return rms
