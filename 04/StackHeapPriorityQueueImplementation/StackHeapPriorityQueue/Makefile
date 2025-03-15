CXX := g++
CXXFLAGS := -g -Wall --std=c++11
VALGRIND := valgrind --tool=memcheck --leak-check=yes
#DEFS=-DDEBUG
OBJS=llrec-test.o llrec.o

all: llrec-test

llrec-test: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o llrec-test $(OBJS)

llrec-test.o: llrec-test.cpp llrec.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c llrec-test.cpp -o llrec-test.o
llrec.o: llrec.cpp llrec.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -c llrec.cpp -o llrec.o

clean:
	rm -f *.o rh llrec-test *~

.PHONY: clean 