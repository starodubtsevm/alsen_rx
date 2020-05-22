# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
import time
from alsen_gen2 import proc_alsen
from noise_gen import proc_noise
from rms import rms
from const import fs, Fs, D, t, A_input, td, T
from rec_create import*

def to_print(fs,Fs,T,time2,time1,counter_total,counter_total2,counter_suc,counter_suc2,t_reaction,t_reaction2, A_input,s_n):

    print ("\nна ветке mas")
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
    print ("Всего передано бит кан 0 " + "\x1b[32m"+\
                                  str(counter_total) +"\x1b[0m")
    print ("Верно принятых бит кан 0 " + "\x1b[32m"+\
                                   str(counter_suc) +"\x1b[0m")
    print ("*----------------------------------------------------------------*")

    print ("*----------------------------------------------------------------*")
    print ("Всего передано бит кан 90 " + "\x1b[32m"+\
                                  str(counter_total2) +"\x1b[0m")
    print ("Верно принятых бит кан 90 " + "\x1b[32m"+\
                                   str(counter_suc2) +"\x1b[0m")
    print ("*----------------------------------------------------------------*")

    print ("Задержка приема первого байта кан 0 " + "\x1b[32m"+\
      str('{:.2f}'.format(t_reaction)) +"\x1b[0m" + " сек.")
    print ("*----------------------------------------------------------------*")

    print ("Задержка приема первого байта кан 90 " + "\x1b[32m"+\
      str('{:.2f}'.format(t_reaction2)) +"\x1b[0m" + " сек.")
    print ("*----------------------------------------------------------------*")

    print ("Амплитуда сигнала " + "\x1b[32m"+\
                                   str(A_input) +"\x1b[0m" + " отсчетов")
    print ("*----------------------------------------------------------------*")
    print ("Соотношение сигнал/шум " + "\x1b[32m"+\
                                   str(s_n) +"\x1b[0m" + " dB")
    print ("*----------------------------------------------------------------*")

