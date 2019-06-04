

for i in $(seq 1000 100000 1000); do
   echo $i
   ./covertime 100000 $i 10000
done;
