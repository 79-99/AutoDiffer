for ((i=0; i <= 20000; i+=1000));
do
	./example_openmp $i 6 -nv
done
