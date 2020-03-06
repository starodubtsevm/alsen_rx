import numpy   as np
from IIR2Filter import *

class alsen_rx(object):
   '''Приемник сигналов АЛСЕН'''
   def __init__(self):
      '''Инициализация'''
      self.fs = 16000
      self.Fcar = 174.89 # несущая АЛС-ЕН
      self.bit_rate = 13.89
      self.A = 1
      self.k = 2 * np.cos(2 * np.pi * self.Fcar / self.fs)

      self.X0_0 = 0
      self.X1_0 = 0
      self.X2_0 = self.A * np.sin(2 * np.pi * self.Fcar / self.fs)

      self.X0_90 = -1
      self.X1_90 = 0
      self.X2_90 = self.A * np.sin(2 * np.pi * self.Fcar / self.fs)
      self.cycle_count = 0

      self._buff_size = int((1/self.bit_rate)/(1/self.fs))
      self._data0 = [0]*self._buff_size
      self._data90 = [0]*self._buff_size

   def local_gen(self,t):
      '''Локальный генератор cos и sin'''
      self.cycle_count = self.cycle_count + 1

      self.X0_0 = self.k*self.X1_0-self.X2_0
      y_0 = self.X0_0
      self.X2_0 = self.X1_0
      self.X1_0 = self.X0_0

      if self.cycle_count > 23:
         self.X0_90 = self.k*self.X1_90-self.X2_90
         y_90 = self.X0_90
         self.X2_90=self.X1_90
         self.X1_90=self.X0_90
         self.cycle_count = 24
      else:
         y_90 = 0

      return y_0, y_90

   def mux1(self,gen0,gen90,x):
      '''Входные перемножители'''
      y0 = x * gen0
      y90 = x * gen90
      return y0, y90

   def diff_decode(self,x0,x90):
      '''Дифференциальный декодер'''

      y1 = x0  * self.delay0(x0)
      y2 = x90 * self.delay0(x0)
      y3 = x0  * self.delay90(x90)
      y4 = x90 * self.delay90(x90)

      y5 = y2 - y3
      y6 = y1 + y4
      y7 = y6 + y5
      y8 = y6 - y5

      return y7, y8

   def delay0(self,x0):
      '''Задержка сигнала на длительность посылки канала 0'''
      self._data0.insert(0,x0)
      self._data0.pop()
      y0 = self._data0[self._buff_size-1]
      return y0
      
   def delay90(self,x90):
      '''Задержка сигнала на длительность посылки канала 90'''
      self._data90.insert(0,x90)
      self._data90.pop()
      y90 = self._data90[self._buff_size-1]
      return y90
      
   def sgn(self, sample):
      """Функция sgn"""
      if sample > 0:
          return 0
      if sample == 0:
          return 0
      if sample < 0:
          return 1

