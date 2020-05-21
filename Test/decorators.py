import time

def time_of_function(function):
    def wrapped(*args):
        start_time = time.clock()
        res = function(*args)
        print(str(time.clock() - start_time) + "  " +str(function))
        return res
    return wrapped
