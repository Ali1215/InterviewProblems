#Name: Ali Muneer
#Student ID: 1615694
#CMPUT 275; Winter 2021
#Weekly Exercise 5: Dynamic Hashing

OBJ = exercise5.o
FLAGS = -Wall -O2 -g -std=c++11

exercise5: exercise5.o
	g++ $(FLAGS) -o exercise5 $(OBJ)

exercise5.o: exercise5.cpp hash_table.h
	g++ $(FLAGS) -c exercise5.cpp

clean:
	rm -f $(OBJ) exercise5
