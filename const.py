import numpy as np

#--------------------------------------
fs              = 8000                       # частота дискретизации
Fcar            = 174.89                     # частота несущей АЛСЕН, Гц
D               = 10                         # фактор децимации
Fs              = fs/D                       # новая частота дискретизации после понижения
T               = 3                          # время симуляции, сек
t               = np.arange(0.0, T, 1/fs)    # дискреты времени
td              = np.arange(0.0, T, 1/fs*D)  # дискреты времени после понижения
fmod            = 10.9                       # скорость передачи Гц (Bod)
LEN_OF_BIT      = int(Fs/fmod)               # длительность бита (для ФАПЧ)
A_input         = 10000                      # амплиитуда входного сигнала (uint16)
A_input_noise   = 1000                      # амплиитуда белого шума (uint16)
Code_alsen1     = 0x32
Code_alsen2     = 0x2C


