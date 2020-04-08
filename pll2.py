from const import *

#---------------------------------------
class pll2(object):

    def __init__(self):
        """initialization"""

        self.syncCount = LEN_OF_BIT
        self.phErrCount = 0
        self.phErr = 0
        self.syncro = 0
        self.receiveFlag = 1
        self.edgeFlag = 0
        self.frontDet = 0
        self.sample = 0
        self.Fs = Fs
        self.scale_fs = 80
        self.__corr = Fs/self.scale_fs
        self.sign_moment = 3.5

    def proc (self,sample):

        #print("sample {}".format(sample))
        #print("LEN_OF_BIT {}".format(LEN_OF_BIT))
        #print("Fs {}".format(self.Fs))
        #print("scale_fs {}".format(self.scale_fs))
        #print("corr {}".format(self.__corr))
        #print("sign_moment {}".format(self.sign_moment))

        """find edge """
        self.sample = sample
        self.frontDet = self.frontDet << 1
        self.frontDet |= self.sample
        #print("frontDet {}".format(self.frontDet))
        #print("_______________________")

        """find @ check syncro """
        self.syncCount -= 1
        if (self.syncCount != 0):
            self.phErrCount += 1
            if (self.phErrCount >= LEN_OF_BIT) or (self.frontDet & 0x0003 == 0x0001):
                self.phErrCount = 0
                #print("self.phErrCount = 0")
            self.syncro = 0

            #print("phErr {}".format(self.phErr))

            return self.syncro,self.phErr,self.sample
        else:
            self.phErr = self.phErrCount - LEN_OF_BIT/self.sign_moment
            if (abs(self.phErr) >= LEN_OF_BIT * 3 / 200):
                if(abs(self.phErr) >= LEN_OF_BIT * 3 / 50):
                    if(self.receiveFlag == 1):
                        if(self.phErr < 0): 
                            self.syncCount = LEN_OF_BIT + self.__corr
                        else:
                            self.syncCount = LEN_OF_BIT - self.__corr
                    else:
                        self.syncCount = LEN_OF_BIT-5-self.phErr*1/8
                else: 
                    if (self.phErr < 0): 
                        self.syncCount = LEN_OF_BIT +2
                    else:
                        self.syncCount = LEN_OF_BIT-2
            else:
                self.syncCount = LEN_OF_BIT
            self.syncro = 1
            #print("phErr {}".format(self.phErr))
            return self.syncro,self.phErr,self.sample

