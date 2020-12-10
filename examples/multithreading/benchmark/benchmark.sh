# Case A: Large equations but only up to 20 of them.
rm "data/std_case_A.txt"
touch "data/std_case_A.txt"
echo -n "Collecting data for std::thread Case A "
for VARIABLE in {1..20}
do
	echo -n "."
	./example_std_thread $VARIABLE 1500 -nv >> "data/std_case_A.txt"
done
echo " done!"

# Case B: Small equations but up to 20000 of them.
rm "data/std_case_B.txt"
touch "data/std_case_B.txt"
echo -n "Collecting data for std::thread Case B "
for ((i=0; i <= 20000; i+=1000));
do
	echo -n "."
	./example_std_thread $i 5 -nv >> "data/std_case_B.txt"
done
echo " done!"

# Case A: Large equations but only up to 20 of them.
rm "data/openmp_case_A.txt"
touch "data/openmp_case_A.txt"
echo -n "Collecting data for openmp Case A "
for VARIABLE in {1..20}
do
	echo -n "."
	./example_openmp $VARIABLE 1500 6 -nv >> "data/openmp_case_A.txt"
done
echo " done!"

# Case B: Small equations but up to 20000 of them.
rm "data/openmp_case_B.txt"
touch "data/openmp_case_B.txt"
echo -n "Collecting data for openmp Case B "
for ((i=0; i <= 20000; i+=1000));
do
	echo -n "."
	./example_openmp $i 5 6 -nv >> "data/openmp_case_B.txt"
done
echo " done!"

echo "Data written to data/ directory!"
