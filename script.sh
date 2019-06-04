
N=1000

for i in $(seq 1 1 $N); do
   printf "$i,"
   ./covertime $N $i 100000
done;
