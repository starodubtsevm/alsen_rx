from code import*


class decode(object):

    def __init__(self):
        """initialization"""
        self.byte = 0
        self.res = 0
        self.base = 0

    def procNew(self,bit,ABase):
        '''Сравнение битовой последовательности '''

        self.byte = self.byte << 1              # {
        if bit == 1:                            # { входящие биты в байт
                self.byte = self.byte | 0x01    # { если бит 1 то добавляем 1

        print(hex(self.byte))
        if (self.byte % 256) in bauerCodeFullArray: # получение остатка от деления на 256
            self.res = 1                            #
        else:                                       #
            self.res = 0                            #

        try:
            index = int(bauerCodeFullArray.index(self.byte % 256) / 8)
            self.base = bauerCode[index]
        except Exception:
            self.res = 0
            self.base = 0xff

        if self.base != ABase:
            self.res = 0

        return self.res, s, hex(self.byte % 256), hex(self.base)

s = [0,0,1,0,1,1,0,0,0,0,1,0,1,1,0,0]

decoder0 = decode()

for i in range (len(s)):
    r,s,h,b = decoder0.procNew(s[i], 0x2C)
    #print (r,s,h,b)

#x = 15
#print (bin(x))
#y = x & -x

#print (bin(y))




