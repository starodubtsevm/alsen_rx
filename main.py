# -*- coding: utf-8 -*-
import numpy as np

import time
from alsen_gen2 import proc_alsen
from noise_gen import proc_noise
from rms import rms
from const import*
from rec_create import*
from print_func import*
from plot_func import*
from read_from_file import*

start_time1 = time.process_time() #старт таймера общего времени выполнения скрипта
counter_total = 0
counter_suc = 0
counter_total2 = 0
counter_suc2 = 0

first_suc_byte_flag = 0
t_reaction = 0
first_suc_byte_flag2 = 0
t_reaction2 = 0

# *--буферы для построения графиков---------------------------------------------
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

plot_en = True
# *--------------------------------------------------------------------------
# генерация тестового сигнала АЛС-ЕН (в буфер)

#signal = proc_alsen(fs, len(t), Code_alsen1, Code_alsen2)
signal = read_from_file()
#print (len(signal))
sig_rms = rms(signal)

# *--------------------------------------------------------------------------
# генерация шума (в буфер)
noise = proc_noise(len(t))
noise_rms = rms(noise)

# *--------------------------------------------------------------------------
# сложение входного сигнала и шума
sig = [signal[i] + noise[i] for i in range(len(t))]

# *--------------------------------------------------------------------------

# вычисление соотношения сигнал\шум
s_n = 20 * np.log(sig_rms/noise_rms)
s_n = str('{:.2f}'.format(s_n))

# *--------------------------------------------------------------------------
start_time2 = time.process_time() # старт таймера времени выполнения основного цикла

for i in range(len(t)):  # главный цикл приемника

# локальный генератор sin и cos
    gen0, gen90 = rx.local_gen(t)
    if plot_en == True:
        buf_gen0.append(gen0)
        buf_gen90.append(gen90)

# *--------------------------------------------------------------------------

# входные перемножители
    #buf_mux1_0 [t] = rx.mux1(gen0, sig[i])
    #buf_mux1_90.[t] = rx.mux1(gen90, sig[i])

    y0_aftermux1 = rx.mux1(gen0, sig[i])
    y90_aftermux1 = rx.mux1(gen90, sig[i])
    if plot_en == True:
        buf_mux1_0.append(y0_aftermux1)
        buf_mux1_90.append(y90_aftermux1)

# *--------------------------------------------------------------------------

# фильтры - интеграторы
    y0_afterlpf1 = flt_iir1.filter(y0_aftermux1)
    y90_afterlpf1 = flt_iir2.filter(y90_aftermux1)
    if plot_en == True:
        buf_lpf1_0.append(y0_afterlpf1)
        buf_lpf1_90.append(y90_afterlpf1)

# *--------------------------------------------------------------------------

# дифференциальный декодер
    if i % D == 0:
        y7,y8 = rx.diff_decode(y0_afterlpf1, y90_afterlpf1)
        if plot_en == True:
            buf_y7.append(y7)
            buf_y8.append(y8)
# *--------------------------------------------------------------------------

# функции sgn-(компараторы)
        y9 = rx.sgn(y7)
        y10 = rx.sgn(y8)
        if plot_en == True:
            buf_y9.append(y9)   # выходной сигнал канала 0
            buf_y10.append(y10) # выходной сигнал канала 90

# *--------------------------------------------------------------------------

# ФАПЧ
        sync0,err0,bit0 = pll0.proc(y9) # выходной сигнал ФАПЧ канал 0
        if plot_en == True:
            pll_buf0.append(sync0)
            pll_err_buf0.append(err0)
        #print (sync0,err0,bit0)

        sync90,err90,bit90 = pll90.proc(y10) # выходной сигнал ФАПЧ канал 90
        if plot_en == True:
            pll_buf90.append(sync90)
            pll_err_buf90.append(err90)
#*--------------------------------------------------------------------------

# Декодеры (прием байтов)
        if sync0 == 1:
            counter_total += 1
            dec0,s0,byte,base = decoder0.procNew(bit0)
            # выходной сигнал декодера канала 0
            #print_buff0.append(str('{:.2f}'.format(1.0/fs * i)))
            #print_buff0.append(str(s0))
            if dec0 == 1:
                if first_suc_byte_flag == 0:
                    t_reaction = 1/fs * i
                    first_suc_byte_flag = 1
                counter_suc += 1
                '''
                print('{}c. кан0 :{} Code: {} Byte: {}; Base: {} {}'.format(str('{:.2f}'.format(1.0/fs * i)),
                                                                   str(s0),
                                                                   str(hex(Code_alsen2)),
                                                                   str(byte),
                                                                   str(base),
                                                                   "\x1b[32m  ok!  \x1b[0m"))
                '''                                                  
                print('{} c. кан0 : Rx_Byte : {}  Base : {} '.format(str('{:.2f}'.format(1.0/fs * i)),
                                                                     str(byte),
                                                                     str(base)))
                                                                 
            else:
                '''
                print('{}c. кан0 :{} Code: {} Byte: {}; Base: {} {}'.format(str('{:.2f}'.format(1.0 / fs * i)),
                                                                str(s0),
                                                                str(hex(Code_alsen2)),
                                                                str(byte),
                                                                str(base),
                                                                "\x1b[31m not ok \x1b[0m"))
                '''                                                
        if sync90 == 1:
            counter_total2 += 1
            dec90,s90,byte,base = decoder90.procNew(bit90)
            # выходной сигнал декодера канала 90
            #print_buff90.append(str('{:.2f}'.format(1.0/fs * i)))
            #print_buff90.append(str(s90))
            if dec90 == 1:
                if first_suc_byte_flag2 == 0:
                    t_reaction2 = 1/fs * i
                    first_suc_byte_flag2 = 1
                counter_suc2 += 1
                '''
                print('{}c. кан90:{} Code: {} Byte: {}; Base: {} {}'.format(str('{:.2f}'.format(1.0 / fs * i)),
                                                                   str(s90),
                                                                   str(hex(Code_alsen1)),
                                                                   str(byte),
                                                                   str(base),
                                                                   "\x1b[32m  ok!  \x1b[0m"))
                '''                                                   
                print('{} c. кан90 : Rx_Byte: {} Base : {} '.format(str('{:.2f}'.format(1.0/fs * i)),
                                                                   str(byte),
                                                                   str(base)))
                                                                   
            else:
                '''
                print('{}c. кан90:{} Code: {} Byte: {}; Base: {} {}'.format(str('{:.2f}'.format(1.0 / fs * i)),
                                                                   str(s90),
                                                                   str(hex(Code_alsen1)),
                                                                   str(byte),
                                                                   str(base),
                                                                   "\x1b[31m not ok \x1b[0m"))
                '''                                                       
# *--------------------------------------------------------------------------

time1 = (time.process_time() - start_time1)
time2 = (time.process_time() - start_time2)

lenght = 0

if len(print_buff90) == len(print_buff0):
    lenght = len(print_buff0)
elif len(print_buff90)>len(print_buff0):
    lenght = len(print_buff0)
elif len(print_buff90)<len(print_buff0):
    lenght = len(print_buff90)
    
# печать результата
#print('Code_alsen1 = {}; Code_alsen2 = {}'.format(hex(Code_alsen1).upper(),hex(Code_alsen2).upper()))
to_print(fs,Fs,T,time2,time1,counter_total,counter_total2,counter_suc,counter_suc2,t_reaction,t_reaction2,A_input,s_n)

# построение графиков
if plot_en is True:
    to_plot(sig, buf_lpf1_0, buf_lpf1_90, pll_buf0, buf_y9, pll_buf90, buf_y10, pll_err_buf0)
'''
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
pll_buf0 = []
pll_err_buf0 = []
pll_buf90 = []
pll_err_buf90 = []
'''
