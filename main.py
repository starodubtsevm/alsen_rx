import numpy as np
import matplotlib.pyplot as plt
import time
from IIR2Filter import *
from FIR2Filter import*
from alsen_rx import*
from alsen_gen2 import*
from pll2 import*
from decode import*

start_time1 = time.clock()

#*--буферы для построения графиков---------------------------------------------
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
rx = alsen_rx() #экземпляр приемника
rx.Fcar = 174.89 # частота несущей
rx.fs = fs #частота дискретизации
rx.bit_rate = 13.89 #скорость передачи данных

#*--фильтр-интегратор канала 0------------------------------------------------
flt_iir1 = IIR2Filter(4, [13], 'low',design='cheby1',rs = 1, fs=fs)
#flt_fir1 = FIR2Filter(255, 1,15,fs=fs)

#*--фильтр-интегратор канала 90------------------------------------------------
flt_iir2 = IIR2Filter(4, [13], 'low',design='cheby1',rs = 1, fs=fs)
#flt_fir2 = FIR2Filter(255, 1,15, fs=fs)

#*--ФАПЧ канала 0-------------------------------------------------------------
pll0 = pll2()
pll0.scale_fs = 70
pll0.Fs = Fs

#*--ФАПЧ канала 90-------------------------------------------------------------
pll90 = pll2()
pll90.scale_fs = 70
pll90.Fs = Fs

#*--Декодер канала 0----------------------------------------------------------
decoder0 = decode()

#*--Декодер канала 90 --------------------------------------------------------
decoder90 = decode()

#*--------------------------------------------------------------------------
#*--конец инициализации узлов приемника---------------------------------------

print ("на ветке develop")
to_plot =True

start_time2 = time.clock()

for i in range (len(t)): # главный цикл приемника

#*--локальный генератор sin  и cos------------------------------------------
    gen0, gen90 = rx.local_gen(t)
    buf_gen0.append(gen0)
    buf_gen90.append(gen90)

#*--------------------------------------------------------------------------

#*--входные перемножители --------------------------------------------------
    y0_aftermux1 = rx.mux1(gen0, sig[i])
    y90_aftermux1 = rx.mux1(gen90, sig[i])
    buf_mux1_0.append(y0_aftermux1)
    buf_mux1_90.append(y90_aftermux1)

#*--------------------------------------------------------------------------

#*--фильтры -интеграторы-----------------------------------------------------
    y0_afterlpf1 = flt_iir1.filter(y0_aftermux1)
    y90_afterlpf1 = flt_iir2.filter(y90_aftermux1)
    #y0_afterlpf1 = flt_fir1.filter(y0_aftermux1)
    #y90_afterlpf1 = flt_fir2.filter(y90_aftermux1)
    buf_lpf1_0.append(y0_afterlpf1)
    buf_lpf1_90.append(y90_afterlpf1)

#*--------------------------------------------------------------------------

#*--дифференциальный декодер-------------------------------------------------
    if i%D == 0:
    
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
        #print (sync0,err0,bit0)
        
        sync90,err90,bit90 = pll90.proc(y10) #выходной сигнал ФАПЧ канал 90
        pll_buf90.append(sync90)
        pll_err_buf90.append(err90)
#*--------------------------------------------------------------------------

#*--Декодеры (прием байтов)-------------------------------------------------
        buff = ["кан0 ","кан90 "]

        if sync0 == 1:
            dec0,string0 = decoder0.proc(bit0)
            #выходной сигнал декодера канала 0 
            buff.insert(1, string0)
            if dec0 == 1:
                buff.insert(2,"  gotcha!  ")
            else:
                buff.insert(2,"  missing  ")
            

        if sync90 == 1:
            dec90,string90 = decoder90.proc(bit90)
            #выходной сигнал декодера канала 90 
            buff.insert(4, string90)
            
            if dec90 == 1:
                 buff.insert(5,"  gotcha!  ")
            else:
                 buff.insert(5,"  missing  ")
            print(str(buff))
#*--------------------------------------------------------------------------

time1 = (time.clock() - start_time1)
time2 = (time.clock() - start_time2)

print ("*----------------------------------------------------------------*")
print ("на ветке develop")
print ("Частота сэемплирования на входе " + str(fs) +" Hz")
print ("Частота сэмплирования после интеграторов " + str(Fs)  +" Hz")
print ("*----------------------------------------------------------------*")
print ("время симуляции   " + str(T) +" сек.")
print("время выполнения основного цикла "+ str ('{:.2f}'.format(time2))+ " сек.")
print("общее время выполнения "+ str ('{:.2f}'.format(time1))+ " сек.")
print ("*----------------------------------------------------------------*")


#*--построение графиков-------------------------------------------------
if to_plot == True:

    ax1 = plt.subplot(511)
    ax2 = plt.subplot(512, sharex=ax1)
    ax3 = plt.subplot(513, sharex=ax1, sharey=ax2)
    ax4 = plt.subplot(514, sharex=ax1)
    ax5 = plt.subplot(515, sharex=ax1)

    ax1.plot(t,sig)
    ax1.grid(True)

    ax2.plot(td,pll_buf0)
    ax2.plot(td,buf_y9)
    ax2.grid(True)

    ax3.plot(td,pll_buf90)
    ax3.plot(td,buf_y10)
    ax3.grid(True)

    ax4.plot(t,buf_lpf1_0)
    #ax4.plot(t,buf_mux1_0)
    ax4.grid(True)

    ax5.plot(t,buf_lpf1_90)
    #ax5.plot(t,buf_mux1_90)
    ax5.grid(True)

    plt.show()
#*--------------------------------------------------------------------------

