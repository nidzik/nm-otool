#!/bin/bash

for i
do
	echo $i
	
../ft_nm $i > mine
nm $i > your
echo "diff"
diff mine your
done
#./ft_nm /bin/sync > mine
#nm /bin/sync > your
#echo "diff sync"
#diff mine your
#echo gg
