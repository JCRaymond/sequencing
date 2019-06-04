#!/usr/bin/python3.7

from random import randint

class Ranges:

   def __init__(self, *ranges):
      self.ranges = ranges
      self.__simplify()

   def __simplify(self):
      self.ranges = sorted(self.ranges)
      i = 1
      while i < len(self.ranges):
         r1 = self.ranges[i-1]
         r2 = self.ranges[i]
         if r2[0] <= r1[1] + 1:
            self.ranges[i-1] = (r1[0], max(r1[1], r2[1]))
            del self.ranges[i]
         else:
            i+=1

   def __add__(self, other):
      return Ranges(*self.ranges, *other.ranges)

   def __addi__(self, other):
      self.ranges.extend(other.ranges)
      self.__simplify()

   def __eq__(self, other):
      return self.ranges == other.ranges

   def __str__(self):
      return str(self.ranges)


def count_cover(N, R):
   total = Ranges()
   target = Ranges((1,N))
   ms = N-R
   c = 0
   while total != target:
      i = randint(1, ms)
      nr = Ranges((i,i+R))
      total += nr
      c += 1
   return c


def count_cover_avg(N, R, T):
   return sum(count_cover(N, R) for _ in range(T)) / T


if __name__ == "__main__":
   from sys import argv, stderr
   
   args = argv[1:]

   if len(args) < 2:
      print("""
The correct usage of this program is 'covertime.py N R [T]'

Where N is the size of the range ([1, N]), and R is the size of intervals being
chosen at random. T is by default 1, and is the number of trials to run and
average. With high enough T, the value should approach the expected number of
trials for the values provided.

The output is the average number of intervals required over T trials
""", file=stderr)
      exit()

   N, R, *args = args
   N = int(N)
   R = int(R)
   if len(args) >= 1:
      T, *args = args
      T = int(T)
      print(count_cover_avg(N, R, T))
   else:
      print(count_cover(N,R))
   

