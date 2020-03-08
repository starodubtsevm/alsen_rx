from code import *

#---------------------------------------
class decode(object):

    def __init__(self):
        """initialization"""
        self.string  = [0] * 8 

    def proc(self,bit):

        self.string.insert(8, bit)
        self.string.pop(0)
        if self.string in array2C:
            return 1, self.string
        else:
            return 0, self.string
