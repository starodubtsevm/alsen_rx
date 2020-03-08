import numpy as np

#--------------------------------------
fs = 8000 #частота дискретизации
D = 10
Fs = fs/D
T = 3 # время симуляции, сек
t = np.arange(0.0, T, 1/fs) # дискреты времени
td = np.arange(0.0, T, 1/fs*D) # дискреты времени
fmod    = 13.89	 # Modulation freq in Hz (Bod)
#--------------------------------------

LEN_OF_BIT = int(Fs/fmod)


