cosmos: src/cosmos.o src/space.o
	g++ -g -lncurses src/cosmos.o src/space.o -o cosmos 
cosmos.o: src/cosmos.cc
	g++ -c -g src/cosmos.cc 
space.o: src/space.cc
	g++ -c -g src/space.cc
clean: 
	rm cosmos src/*.o
