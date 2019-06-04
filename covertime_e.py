from covertime import *

N = 100
T = 5000

for i in range(N):
   print(i, '|', count_cover_avg(N,i,T))
