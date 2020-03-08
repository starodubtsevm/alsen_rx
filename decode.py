from code import *

#---------------------------------------
class decode(object):

    def __init__(self):
        """initialization"""
        self.string  = [0] * 8 

    def proc(self,bit):
        '''Сравнение битовой последовательности '''
        self.string.insert(8, bit)
        self.string.pop(0)
        s = self.string
        if self.string in array2C:
            res = 1
        else:
            res = 0
        return res,s
