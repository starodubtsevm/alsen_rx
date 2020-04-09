from code import *

#---------------------------------------
class decode(object):

    def __init__(self):
        """initialization"""
        self.string = [0]*8
        self.byte = 0
        self.res = 0
        self.base = 0

    def procNew(self,bit,ABase):
        '''Сравнение битовой последовательности '''
        
        self.string.insert(8, bit)
        self.string.pop(0)
        s = self.string
        
        self.byte = self.byte << 1
                                         # { 
        if bit == 1:                     # { входящие биты в байт
            self.byte = self.byte | 0x01 # { если бит 1 то добавляем 1

        if (self.byte % 256) in bauerCodeFullArray: # выделяем последний байт
            self.res = 1 # если он в таблице - хорошо :)
        else:
            self.res = 0 # если 

        try:
            index = int(bauerCodeFullArray.index(self.byte % 256) / 8)
            self.base = bauerCode[index]
        except Exception:
            self.res = 0
            self.base = 0xff

        if self.base != ABase:
            self.res = 0

        return self.res, s, hex(self.byte % 256), hex(self.base)

    def proc(self,bit,ABase):
        '''Сравнение битовой последовательности '''
        self.string.insert(8, bit)
        self.string.pop(0)
        s = self.string
        if self.string in array:
            self.res = 1
        else:
            self.res = 0

        return self.res,s,hex(self.byte),hex(self.base)
