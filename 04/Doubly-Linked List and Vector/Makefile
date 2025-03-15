CC = g++
CXXFLAGS = -g -Wall -Werror
ALL = bigint-test delist-test

all: $(ALL)

delist-test: delist-test.cpp delist.o
	$(CC) $(CXXFLAGS) $^ -o $@ 

delist.o: delist.cpp delist.h 
	$(CC) $(CXXFLAGS) -c $< -o $@

bigint-test: bigint-test.cpp bigint.o
	$(CC) $(CXXFLAGS) $^ -o $@ 

bigint.o: bigint.cpp bigint.h
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(ALL) bigint-test delist-test *.o

