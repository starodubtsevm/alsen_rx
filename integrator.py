import numpy as np

#---------------------------------------
class integrator(object):

	def __init__(self):
		"""initialization"""
		self.T = 1/13.89
		self.len_buf = int(self.T/1/16000)
		self.buf  = [0] * self.len_buf 
		self.count = 0


	def proc(self,sample):
		'''Функция интегратора (скользящее усреднение по буферу)'''
		self.buf.insert(0,sample)
		self.buf.pop()
		#print(self.buf)
		mean = np.mean(self.buf)
		#print (mean)
		return mean


'''
#-----тестовый скрипт-------------------------------------------
data = np.arange(0,10,1)
integr1 = integrator()

for i in range (len(data)):
	integr1.proc(data[i])
'''
