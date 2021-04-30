#Name: Ali Muneer
#Student ID: 1615694
#CMPUT 275; Winter 2021
#Weekly Exercise 7: Divide and Conquer

OBJ = climbing.o driver.o
FLAGS = -O2 -g -std=c++11

climbing: $(OBJ)
	g++ $(FLAGS) -o $@ $^

climbing.o: climbing.cpp
	g++ $(FLAGS) -c climbing.cpp

driver.o: driver.cpp
	g++ $(FLAGS) -c driver.cpp

clean:
	rm -f $(OBJ) climbing
