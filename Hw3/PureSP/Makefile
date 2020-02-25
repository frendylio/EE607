# For cleaning
clean:
	rm ./src/*.o
	rm ./bin/*.out

# For running
run: 
	./bin/a.out

# For compiling
all: bin/a.out

bin/a.out: src/main.o src/linkedlist.o src/network.o src/path.o src/print.o
	g++ src/main.o src/linkedlist.o src/network.o src/path.o src/print.o -o ./bin/a.out

src/linkedlist.o: src/linkedlist.cpp
	g++ -c src/linkedlist.cpp -o src/linkedlist.o

src/network.o: src/network.cpp
	g++ -c src/network.cpp -o src/network.o

src/path.o: src/path.cpp
	g++ -c src/path.cpp -o src/path.o	

src/print.o: src/print.cpp
	g++ -c src/print.cpp -o src/print.o	

src/main.o: src/main.cpp
	g++ -c src/main.cpp -o src/main.o
