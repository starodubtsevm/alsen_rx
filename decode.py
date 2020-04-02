from code import *

#---------------------------------------
class decode(object):

    def __init__(self):
        """initialization"""
        self.string  = [0] * 8
        self.byte = 0
        self.iterator = 0

    def proc(self,bit):
        '''Сравнение битовой последовательности '''
        self.string.insert(8, bit)
        self.string.pop(0)
        s = self.string
        #if self.string in array2C:
        #    res = 1
        #else:
        #    res = 0

        self.iterator = self.iterator + 1
        if self.iterator == 9:
            self.byte = 0

        self.byte = self.byte << 1

        if bit == 1:
            self.byte = self.byte | 0x01

        if (self.byte%255) in bauerCodeFullArray:
            res = 1
        else:
            res = 0

        #if self.byte == 0 :
        #    self.byte = 1

        try:
            index = int(bauerCodeFullArray.index(self.byte%255) / 8)
            base = bauerCode[index]
        except Exception:
            res = 0
            base = 0xff

        return res,s,hex(self.byte%255),hex(base)
