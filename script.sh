
fname="vals_$1_$2"

touch $fname
printf "R,T\n" > $fname
for i in $(seq 1 1 $1); do
   printf "$i," >> $fname
   ./covertime $1 $i $2 >> $fname
done;
