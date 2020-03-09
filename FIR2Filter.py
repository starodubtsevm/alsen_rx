#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import scipy.signal as signal

class FIR2Filter(object):           

    def createCoeffs(self,ntaps,lowcut,highcut,fs,window='hamming'):
        nyq = 0.5 * fs
        self.COEFFS = signal.firwin(ntaps, [lowcut, highcut], nyq=nyq, pass_zero=False,
        window=window, scale=False)
        return self.COEFFS

    def __init__(self,ntaps,lowcut,highcut,fs):
        self.COEFFS = self.createCoeffs(ntaps,lowcut,highcut,fs)
        self._data = np.zeros(len(self.COEFFS))
        self.size= len(self.COEFFS)
        self.index= 0

    def filter(self,sample):
        """sample processed """

        if len(self._data) == self.size:
            self._data[self.index]= sample
        else:
            self._data.append(sample)
        self.index= (self.index + 1) % self.size
        acc = 0 # accumulator
        indx = self.index

        for j in range (len(self.COEFFS)):
            acc = acc + self._data[indx] * self.COEFFS[j]
            if indx == ((self.size)-1):
                indx = 0
            else:
                indx += 1

        return (acc ) # result to 16 bit value


