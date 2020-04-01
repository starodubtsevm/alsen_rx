




Byte1=0x01
Byte2=0x02

for i in range(8):
    diBit=((Byte1 & 0x80)>>7)+((Byte2 & 0x80)>>7)
    print (diBit)
    Byte1=Byte1<<1
    Byte2=Byte2<<1
