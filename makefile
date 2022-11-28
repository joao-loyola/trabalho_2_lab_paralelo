all: compile
	rm time_result.csv
	touch time_result.csv
	echo  "tempo" >>  time_result.csv
	./main
	echo "."
	./main
	echo "."
	./main
	echo "."
	./main
	echo "."
	./main
	echo "."
	./main
	echo "."
	./main
	echo "."
	./main
	echo "."
	./main
	echo "."
	./main
	echo "."
	python3 compute.py

compile:
	gcc -o main main.c -fopenmp -lm