from code import *

#---------------------------------------
class decode(object):

	def __init__(self):
		"""initialization"""
		self.string  = [0] * 8 
		self.count = 0
		self.count_free = 0

	def proc(self,bit):
	
			self.bit = bit

			self.string.insert(8, self.bit)
			self.string.pop(0)
			print(self.string)
			if self.string in array2C:
				print ("gotcha! ")
				self.count_free += 1
				if self.count_free == 3: 
					print ("free!")
					self.count_free = 0
			else:
				print ("not ok")
				self.count_free = 0

			self.count +=1
