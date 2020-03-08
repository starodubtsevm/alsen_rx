import numpy as np
import matplotlib.pyplot as plt
import time
from IIR2Filter import *
from FIR2Filter import*
from alsen_rx import*
from alsen_gen2 import*
from pll2 import*
from decode import*
from noise_gen import*

start_time1 = time.clock()
counter_total = 0
counter_suc =0
first_suc_byte_flag = 0
#*--буферы для построения графиков---------------------------------------------
sig = []
buf_gen0 = []
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

print_buff0 = []
print_buff90 = []
#*--------------------------------------------------------------------------

#*--генерация тестового сигнала АЛС-ЕН (в буфер)------------------------------
Code_alsen1 = 0x2C
Code_alsen2 = 0x2C
signal =[]
signal = proc_alsen(fs, len(t), Code_alsen1, Code_alsen2)

#*--------------------------------------------------------------------------

#*--генерация шума (в буфер)-------------------------------------------------
noise = []
noise = proc_noise(len(t))

#*--------------------------------------------------------------------------

#*--сложение входного сигнала и шума-----------------------------------------
for i in range (len(t)):
    sig.append(signal[i] + noise[i])

#*--------------------------------------------------------------------------

#*--создание узлов приемника ------------------------------------------------
#*--------------------------------------------------------------------------
rx = alsen_rx() #экземпляр приемника
rx.Fcar = 174.89 # частота несущей
rx.fs = fs #частота дискретизации
rx.bit_rate = 13.89 #скорость передачи данных

#*--фильтр-интегратор канала 0------------------------------------------------
#flt_iir1 = IIR2Filter(4, [13], 'low',design='cheby1',rs = 1, fs=fs)
flt_fir1 = FIR2Filter(255, 1,15,fs=fs)

#*--фильтр-интегратор канала 90------------------------------------------------
#flt_iir2 = IIR2Filter(4, [13], 'low',design='cheby1',rs = 1, fs=fs)
flt_fir2 = FIR2Filter(255, 1,15, fs=fs)

#*--ФАПЧ канала 0-------------------------------------------------------------
pll0 = pll2()
pll0.scale_fs = 70
pll0.sign_moment = 3.5
pll0.Fs = Fs

#*--ФАПЧ канала 90-------------------------------------------------------------
pll90 = pll2()
pll90.scale_fs = 70
pll90.sign_moment = 3.5
pll90.Fs = Fs

#*--Декодер канала 0----------------------------------------------------------
decoder0 = decode()

#*--Декодер канала 90 --------------------------------------------------------
decoder90 = decode()

#*--------------------------------------------------------------------------
#*--конец инициализации узлов приемника---------------------------------------

to_plot = True

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
    #y0_afterlpf1 = flt_iir1.filter(y0_aftermux1)
    #y90_afterlpf1 = flt_iir2.filter(y90_aftermux1)
    y0_afterlpf1 = flt_fir1.filter(y0_aftermux1)
    y90_afterlpf1 = flt_fir2.filter(y90_aftermux1)
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
       
        if sync0 == 1:
            counter_total+=1
            dec0,s0 = decoder0.proc(bit0)
            #выходной сигнал декодера канала 0 
            print_buff0.append(str('{:.2f}'.format(1.0/fs*i)))
            print_buff0.append(str(s0))
            if dec0 == 1:
                if first_suc_byte_flag == 0:
                    t_reaction = 1/fs * i
                    first_suc_byte_flag = 1
                counter_suc+=1
                print_buff0.append("\x1b[32m  ok!  \x1b[0m")
            else:
                print_buff0.append("\x1b[31m not ok \x1b[0m")

        if sync90 == 1:
            dec90,s90 = decoder90.proc(bit90)
            #выходной сигнал декодера канала 90 
            print_buff90.append(str('{:.2f}'.format(1.0/fs*i)))
            print_buff90.append(str(s90))
            if dec90 == 1:
                print_buff90.append("\x1b[32m  ok!  \x1b[0m")
            else:
                print_buff90.append("\x1b[31m not ok \x1b[0m")

#*--------------------------------------------------------------------------

time1 = (time.clock() - start_time1)
time2 = (time.clock() - start_time2)


if len(print_buff90) == len(print_buff0):
    lenght = len(print_buff0)
elif len(print_buff90)>len(print_buff0):
    lenght = len(print_buff0)
elif len(print_buff90)<len(print_buff0):
    lenght = len(print_buff90)

for i in range(0,lenght,3):
    print('{}c. кан0:{}{}{}c. кан90: {}{}\n'.format(print_buff0[i],\
    str(print_buff0[i+1]), str(print_buff0[i+2]),\
    print_buff90[i],str(print_buff90[i+1]), str(print_buff90[i+2])))
    print ("~" * 86)
print ("\n")
print ("*----------------------------------------------------------------*")

print ("на ветке develop")
print ("*----------------------------------------------------------------*")
print ("Частота сэмплирования на входе " + "\x1b[32m"+\
                              str(fs) +"\x1b[0m" +" Hz")
print ("Частота сэмплирования после интеграторов " + "\x1b[32m"+\
                               str(Fs) +"\x1b[0m" +" Hz")
print ("*----------------------------------------------------------------*")
print ("время симуляции   "+"\x1b[32m"+ str(T)+"\x1b[0m"+" сек.")
time2 = str('{:.2f}'.format(time2))
print("время выполнения основного цикла " + "\x1b[32m"+\
                                          str(time2)+"\x1b[0m" + " сек.")
time1 = str('{:.2f}'.format(time1))
print("общее время выполнения " + "\x1b[32m"\
                                        + str(time1)+"\x1b[0m" + " сек.")
print ("*----------------------------------------------------------------*")
print ("Всего передано бит " + "\x1b[32m"+\
                              str(counter_total) +"\x1b[0m")
print ("Верно принятых бит " + "\x1b[32m"+\
                               str(counter_suc) +"\x1b[0m")
print ("*----------------------------------------------------------------*")

print ("Задержка приема первого байта " + "\x1b[32m"+\
                               str(t_reaction) +"\x1b[0m" + " сек.")
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

