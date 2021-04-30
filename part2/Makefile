#Name: Ali Muneer
#Student ID: 1615694
#CMPUT 275; Winter 2021
#Assignment 1 Part 2

flags = -O2 -g -std=c++11
VPATH = server:client

all: server client

# server section
server: server.o dijkstra.o digraph.o 
	cd server && g++ -o server server.o dijkstra.o digraph.o

server.o: server.cpp digraph.cpp dijkstra.cpp wdigraph.h digraph.h dijkstra.h
	cd server && g++ $(flags) -c server.cpp
	
dijkstra.o: dijkstra.cpp dijkstra.h wdigraph.h digraph.h digraph.cpp
	cd server && g++ $(flags) -c dijkstra.cpp

digraph.o: digraph.cpp digraph.h
	cd server && g++ $(flags) -c digraph.cpp



# client section
client: client.o
	cd client && g++ $(flags) -o $@ $^

client.o: client.cpp
	cd client && g++ $(flags) -c client.cpp



clean:
	cd client && rm -f client client.o outpipe inpipe
	cd server && rm -f server server.o dijkstra.o digraph.o
	rm -f inpipe outpipe

