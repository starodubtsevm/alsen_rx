import timeit


signal = []
noise = []
sig = []

for i in range(1000000):
    signal.append(i)
    
for i in range(1000000):
    noise.append(i)


def calc():
    #for i in range(1000000):
        #sig.append(signal[i] + noise[i])
    sig = [signal[i] + noise[i] for i in range(1000000)]

starttime = timeit.default_timer()
print("The start time is :",starttime)
calc()
print("The time difference is :", timeit.default_timer() - starttime)


#import random
#
#names = ['Маша', 'Петя', 'Вася']
#
#secret_names = map(lambda x: random.choice(['Шпунтик', 'Винтик', 'Фунтик']), names)
