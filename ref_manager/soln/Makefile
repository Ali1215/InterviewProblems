OBJ = ref_manager.o we3_test.o
main = we3_solution
FLAGS = -Wall -O2 -g -std=c++11

all: $(main)

$(main): $(OBJ)
	g++ -o $@ $^

we3_test.o: we3_test.cpp
	g++ $(FLAGS) -c we3_test.cpp

ref_manager.o: ref_manager.cpp ref_manager.h
	g++ $(FLAGS) -c ref_manager.cpp

clean:
	rm -f $(OBJ) $(main)
