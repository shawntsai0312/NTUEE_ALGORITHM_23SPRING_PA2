# # CC and CFLAGS are varilables
# CC = g++
# CFLAGS = -c
# AR = ar
# ARFLAGS = rcv
# # -c option ask g++ to compile the source files, but do not link.
# # -g option is for debugging version
# # -O2 option is for optimized version
# DBGFLAGS = -g -D_DEBUG_ON_
# OPTFLAGS = -O2

# all	: bin/mps bin/lc
# 	@echo -n ""

# # optimized version
# bin/mps	: src/maxPlanarSubset.cpp
# bin/lc : src/lineChecker.cpp
# 			$(CC) $< -o $@
# # clean all the .o and executable files
# clean:
# 		rm -rf *.o lib/*.a lib/*.o bin/*

all: bin/mps bin/lc

bin/mps: src/maxPlanarSubset.cpp
	g++ -o bin/mps src/maxPlanarSubset.cpp

bin/lc: src/lineChecker.cpp
	g++ -o bin/lc src/lineChecker.cpp

clean:
	rm -f program1 program2


