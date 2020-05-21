# -*- coding: utf-8 -*-
import IIR2Filter
# from FIR2Filter import *
from alsen_rx import alsen_rx
from pll2 import pll2
from decode import decode
from const import fs, Fs, D, t, A_input, td, T

# создание узлов приемника
# *--------------------------------------------------------------------------
rx = alsen_rx()      # экземпляр приемника

# фильтр-интегратор канала 0
flt_iir1 = IIR2Filter.IIR2Filter(4, [13], 'low', design='cheby1', rs=1, fs=fs)
# flt_fir1 = FIR2Filter(255, 1,15,fs=fs)
#print("Коэффициенты flt_iir1")
#print(flt_iir1.COEFFS)
#print(len(flt_iir1.COEFFS))

# фильтр-интегратор канала 90
flt_iir2 = IIR2Filter.IIR2Filter(4, [13], 'low', design='cheby1', rs=1, fs=fs)
# flt_fir2 = FIR2Filter(255, 1,15, fs=fs)
#print("Коэффициенты flt_iir2")
#print(flt_iir2.COEFFS)
#print(len(flt_iir2.COEFFS))

# ФАПЧ канала 0
pll0 = pll2()
pll0.scale_fs = 70
pll0.sign_moment = 4.5
pll0.Fs = Fs

# ФАПЧ канала 90
pll90 = pll2()
pll90.scale_fs = 70
pll90.sign_moment = 4.5
pll90.Fs = Fs

# Декодер канала 0
decoder0 = decode()

# Декодер канала 90
decoder90 = decode()

# *--------------------------------------------------------------------------
# конец инициализации узлов приемника
