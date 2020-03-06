import numpy as np
import matplotlib.pyplot as plt
from alsen_rx import*
from alsen_gen2 import*
from pll2 import*
from decode import*

fs = 16000 #частота дискретизации
T = 3 # время симуляции, сек
t = np.arange(0.0, T, 1/fs) # дискреты времени

#*--буферы для построения графиков------------------------------
buf_gen0 =[]
buf_gen90 = []
buf_mux1_0 = []
buf_mux1_90 = []
buf_lpf1_0 = []
buf_lpf1_90 = []
buf_y7 = []
buf_y8 = []
buf_y9 = []
buf_y10 = []
pll_buf0 = []
pll_err_buf0 = []
pll_buf90 = []
pll_err_buf90 = []

#*--------------------------------------------------------------------------

#*--генерация тестового сигнала АЛС-ЕН (в буфер)------------------------------
Code_alsen1 = 0x2C
Code_alsen2 = 0x2C
sig =[]
sig = proc_alsen(fs, len(t), Code_alsen1, Code_alsen2)
#*--------------------------------------------------------------------------

#*--создание узлов приемника ------------------------------------------------
#*--------------------------------------------------------------------------
rx = alsen_rx()  #экземпляр приемника
rx.Fcar = 174.89  # частота несущей
rx.fs = fs  # частота дискретизации
rx.bit_rate = 13.89  #скорость передачи данных

#*--фильтр-интегратор канала 0------------------------------------------------
flt_iir1 = IIR2Filter(2, [26], 'low',design='cheby1',rs = 1, fs=fs)

#*--фильтр-интегратор канала 90------------------------------------------------
flt_iir2 = IIR2Filter(2, [26], 'low',design='cheby1',rs = 1, fs=fs)

#*--ФАПЧ канала 0-------------------------------------------------------------
pll0 = pll2(1)

#*--ФАПЧ канала 90-------------------------------------------------------------
pll90 = pll2(1)

#*--Декодер канала 0----------------------------------------------------------
decoder0 = decode()

#*--Декодер канала 90 --------------------------------------------------------
decoder90 = decode()

#*--------------------------------------------------------------------------
#*--конец инициализации узлов приемника---------------------------------------

for i in range (len(t)): # главный цикл приемника

#*--локальный генератор sin  и cos------------------------------------------
    gen0, gen90 = rx.local_gen(t)
    buf_gen0.append(gen0)
    buf_gen90.append(gen90)

#*--------------------------------------------------------------------------

#*--входные перемножители --------------------------------------------------
    y0_aftermux1, y90_aftermux1 = rx.mux1(gen0, gen90, sig[i])
    buf_mux1_0.append(y0_aftermux1)
    buf_mux1_90.append(y90_aftermux1)

#*--------------------------------------------------------------------------

#*--фильтры -интеграторы-----------------------------------------------------
    y0_afterlpf1 = flt_iir1.filter(y0_aftermux1)
    y90_afterlpf1 = flt_iir2.filter(y90_aftermux1)
    buf_lpf1_0.append(y0_afterlpf1)
    buf_lpf1_90.append(y90_afterlpf1)

#*--------------------------------------------------------------------------

#*--дифференциальный декодер-------------------------------------------------
    y7,y8 = rx.diff_decode(y0_afterlpf1, y90_afterlpf1)
    buf_y7.append(y7)
    buf_y8.append(y8)

#*--------------------------------------------------------------------------

#*--функции sgn-(компараторы)-------------------------------------------------
    y9 = rx.sgn(y7)
    y10 = rx.sgn(y8)
    buf_y9.append(y9)   # выходной сигнал канала 0
    buf_y10.append(y10) # выходной сигнал канала 90

#*--------------------------------------------------------------------------

#*--ФАПЧ--------------------------------------------------------------------
    sync0,err0,bit0 = pll0.proc(y9) #выходной сигнал ФАПЧ канал 0
    pll_buf0.append(sync0)
    pll_err_buf0.append(err0)

    sync90,err90,bit90 = pll90.proc(y10) #выходной сигнал ФАПЧ канал 90
    pll_buf90.append(sync90)
    pll_err_buf90.append(err90)

#*--------------------------------------------------------------------------

#*--Декодеры (прием байтов)-------------------------------------------------
    if sync0 == 1:
        print ("первый канал")
        dec0 = decoder0.proc(bit0) #выходной сигнал декодера канала 0
    else:
        pass

    if sync90 == 1:
        print ("второй канал")
        dec90 = decoder90.proc(bit90) #выходной сигнал декодера канала 90
    else:
        pass

#*--------------------------------------------------------------------------

#*--построение графиков-------------------------------------------------
ax1 = plt.subplot(511)
ax2 = plt.subplot(512, sharex=ax1)
ax3 = plt.subplot(513, sharex=ax1, sharey=ax2)
ax4 = plt.subplot(514, sharex=ax1)
ax5 = plt.subplot(515, sharex=ax1)

ax1.plot(t,sig)
ax1.grid(True)

ax2.plot(t,pll_buf0)
ax2.plot(t,buf_y9)
ax2.grid(True)

ax3.plot(t,pll_buf90)
ax3.plot(t,buf_y10)
ax3.grid(True)

ax4.plot(t,pll_err_buf0)
ax4.grid(True)

ax5.plot(t,pll_err_buf90)
ax5.grid(True)

plt.show()
#*--------------------------------------------------------------------------

