#!/usr/bin/python3.7

from sys import stderr
from random import choices

def gen_seq(N, L, *probs):
   probs = list(probs)
   if len(probs) > N:
      print("The number of probabilities provided should not exceed N", file=stderr)
      return None

   if len(probs) < N:
      rem = 1 - sum(probs)
      p = rem / (N - len(probs))
      probs.extend([p] * (N - len(probs)))

   oA = ord('A')
   pop = [chr(oA + i) for i in range(N)]

   return ''.join(choices(pop, probs, k=L))
      

if __name__ == "__main__":
   from sys import argv
   args = argv[1:]

   if len(args) < 2:
      print("""
The correct usage of this program is 'gen_sequence.py N L [p1 p2 p3 ... pk]' 

Where N is the number of unique characters, L is the length of the sequence,
and p1, p2, p3 and so on to pk describe the probabilites of the first k of said
characters.

There may not be more than N of these probabilites, in which case the sum of
the probabilities should be 1. If k is less than N or there are no
probabilities provided, then remaining characters that do not have an assigned
probability will be given equal probability equal to:
      
      (1 - p1 - p2 - ... - pk) / (N - k)

If k is 0 (which means that no probabilities were provided), then each
character will have probability:
      
      1 / N

The resulting sequence will be printed to standard output, followed by an
endline character.
""", file=stderr)
      exit()

   print(gen_seq(int(args[0]), int(args[1]), *[float(p) for p in args[2:]]))
