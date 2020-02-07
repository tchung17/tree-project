CC=g++
CFLAGS=-std=c++11 -pedantic -Wall -Wextra -g

both: tTreeTest cTreeTest 

tTreeTest: TTreeTest.o
	$(CC) TTreeTest.o -o tTreeTest

cTreeTest: CTreeTest.o CTree.o
	$(CC) CTreeTest.o CTree.o -o cTreeTest 

TTreeTest.o: TTreeTest.cpp Tree.h Tree.inc
	$(CC) $(CFLAGS) -c TTreeTest.cpp

CTreeTest.o: CTreeTest.cpp CTree.h
	$(CC) $(CFLAGS) -c CTreeTest.cpp

CTree.o: CTree.cpp CTree.h 
	$(CC) $(CFLAGS) -c CTree.cpp 

clean:
	rm -f *.o tTreeTest cTreeTest 
