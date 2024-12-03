all: prog

prog: main.o matrix.o jacob.o
	g++ main.o matrix.o jacob.o -o prog



main.o: main.cpp matrix.hpp jacob.hpp
	g++ -g -Wall -Wextra -Werror -pedantic -std=gnu++0x -O3 -c main.cpp

matrix.o: matrix.cpp matrix.hpp
	g++ -g -Wall -Wextra -Werror -pedantic -std=gnu++0x -O3 -c matrix.cpp

jacob.o: jacob.cpp jacob.hpp
	g++ -g -Wall -Wextra -Werror -pedantic -std=gnu++0x -O3 -c jacob.cpp


clean:
	rm -f *.o prog
