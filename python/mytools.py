import time
def mytimer(cnt=100):
    class Timer:
        def __init__(self, func):
            self.func = func
            self.alltime = 0
            self.maxtime = 0
            self.mintime = 1000
            self.avgtime = 0
        def __call__(self, *args, **kargs):
            for i in range(cnt):
                start = time.clock()
                result = self.func(*args, **kargs)
                elasped = time.clock()-start
                self.alltime += elasped
                if self.mintime > elasped:
                    self.mintime = elasped
                if self.maxtime < elasped:
                    self.maxtime = elasped
            self.avgtime = self.alltime / cnt
            print('run %s, cnt = %s' % (self.func.__name__, cnt))
            print('\tavgtime: %.5fms' % (self.avgtime*1000))
            print('\tmaxtime: %.5fms' % (self.maxtime*1000))
            print('\tmintime: %.5fms' % (self.mintime*1000))
            return result
    return Timer

@mytimer(cnt=100)
def listcmp(N):
    return [x*2 for x in range(N)]

listcmp(50000)
