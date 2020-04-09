import numpy   as np
from const import*


class alsen_rx(object):
   '''Приемник сигналов АЛСЕН'''
   def __init__(self):
      '''Инициализация'''
      self.Fcar = 174.89 # несущая АЛС-ЕН
      self.bit_rate = fmod
      self.fs = fs
      self.A = 1
      self.k = 2 * np.cos(2 * np.pi * self.Fcar / self.fs)

      self.X0_0 = 0
      self.X1_0 = 0
      self.X2_0 = self.A * np.sin(2 * np.pi * self.Fcar / self.fs)

      self.X0_90 = 0
      self.X1_90 = 0
      self.X2_90 = self.A * np.sin(2 * np.pi * self.Fcar / self.fs)
      self.cycle_count = 0

      self._buff_size = int((1/self.bit_rate)/(1/self.fs)/D)
      self._data0 = [0]*self._buff_size
      self._data90 = [0]*self._buff_size

   def local_gen(self,t):
      '''Локальный генератор cos и sin'''
      self.cycle_count = self.cycle_count + 1

      self.X0_0 = self.k*self.X1_0-self.X2_0
      y_0 = self.X0_0
      self.X2_0 = self.X1_0
      self.X1_0 = self.X0_0

      if self.cycle_count > 13:
         self.X0_90 = self.k*self.X1_90-self.X2_90
         y_90 = self.X0_90
         self.X2_90=self.X1_90
         self.X1_90=self.X0_90
         self.cycle_count = 13
      else:
         y_90 = 0

      return y_0, y_90

   def mux1(self,gen,x):
      '''Входные перемножители'''
      y = x * gen
      return y

   def diff_decode(self,x0,x90):
      '''Дифференциальный декодер'''

      y1 = x0  * self.delay0(x0)
      y2 = x90 * self.delay0(x0)
      y3 = x0  * self.delay90(x90)
      y4 = x90 * self.delay90(x90)

      y7 = (y2-y3) + (y1+y4) # Окунев стр 171
      y8 = (y1+y4) - (y2-y3)

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
      return 0 if( sample > 0 or sample == 0) else 1

