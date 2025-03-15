CXX=g++
CXXFLAGS=-g -Wall -Werror -std=c++11 -I /usr/include/gtest/
DEFS=-DUSE_SOL_CLASSNAME
GTEST_LD_FLAGS=-lgtest -lgtest_main -lpthread
TARGETS=record1 record2 record-test str-test
WORKOBJ = course.o student.o passfailcourse.o scalecourse.o

all: $(TARGETS)

record12: record1 record2
record: record1 record2

str-gtest: str-gtest.cpp str.o
	$(CXX) $(CXXFLAGS) $(DEFS) $^ -o $@ $(GTEST_LD_FLAGS)

str-test: str-test.cpp str.o
	$(CXX) $(CXXFLAGS) $(DEFS) $^ -o $@ 

str.o: str.cpp str.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -c $< -o $@

course.o: course.cpp course.h
	$(CXX) $(CXXFLAGS) course.cpp -c -o course.o
	
student.o: student.cpp student.h course.o
	$(CXX) $(CXXFLAGS) student.cpp -c -o student.o
	
passfailcourse.o: passfailcourse.cpp passfailcourse.h course.o
	$(CXX) $(CXXFLAGS) passfailcourse.cpp -c -o passfailcourse.o

scalecourse.o: scalecourse.cpp scalecourse.h course.o
	$(CXX) $(CXXFLAGS) scalecourse.cpp -c -o scalecourse.o

record1: record1.cpp course.o student.o passfailcourse.o scalecourse.o
	$(CXX) $(CXXFLAGS) record1.cpp $(WORKOBJ) -o record1

record2: record2.cpp course.o student.o passfailcourse.o scalecourse.o
	$(CXX) $(CXXFLAGS) record2.cpp $(WORKOBJ) -o record2

record3: record3.cpp course.o student.o passfailcourse.o scalecourse.o
	$(CXX) $(CXXFLAGS) record3.cpp $(WORKOBJ) -o record3

record-test: .guides/test/record-test.cpp course.o student.o passfailcourse.o scalecourse.o
	$(CXX) $(CXXFLAGS) -I. .guides/test/record-test.cpp $(WORKOBJ) -o .guides/test/record-test



clean:
	rm -rf *.o $(TARGETS)
