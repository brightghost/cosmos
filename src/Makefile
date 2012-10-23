cosmos: cosmos.o space.o
	g++ -g -lncurses cosmos.o space.o -o cosmos 
cosmos.o: cosmos.cc
	g++ -c -g cosmos.cc 
space.o: space.cc
	g++ -c -g space.cc
clean: 
	rm cosmos *.o
