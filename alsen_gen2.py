import numpy as np
import matplotlib.pyplot as plt
from const import*


def proc_alsen(Fs, N, Code_alsen1, Code_alsen2):
    Fcar = 174.89
    A =1 * A_input
    imp_duty_count = int((1/fmod)/(1/fs))
    count_bit = 8
    Byte1 = Code_alsen1
    Byte2 = Code_alsen2
    diBit = 0
    phase = 0
    d_phase = 0
    y_res = []

    for i in range(N):
        if imp_duty_count < int((1/fmod)/(1/fs)):
            imp_duty_count=imp_duty_count+1
        else:
            imp_duty_count=0
            if count_bit==0:
                count_bit=8
                Byte1=Code_alsen1
                Byte2=Code_alsen2
            diBit=((Byte1 & 0x80)>>6)+((Byte2 & 0x80)>>7)
            if diBit == 0:
                d_phase = np.pi*0
            elif diBit == 1:
                d_phase = np.pi/2
            elif diBit == 3:
                d_phase = np.pi
            elif diBit == 2:
                d_phase = 3/2*np.pi
            phase = phase + d_phase
            if phase > (2*np.pi):
                phase -= (2*np.pi)
            #print (diBit,Byte1,Byte2,phase)
            Byte1=Byte1<<1
            Byte2=Byte2<<1
            count_bit=count_bit-1
         
        v = 2*np.pi*Fcar*1/fs*i+phase
        #print(imp_duty_count, count_bit)
        #print(round(phase,10))
        #print(round(v,4))
        f = A*np.sin(v)
        print(round(f,4))
        y_res.append(f)
    return y_res

