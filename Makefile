CC=g++
CFLAGS=-W -Wall -ansi -pedantic -std=c++11
LDFLAGS=
LIBINCLUDES=../libs/catch/catch.hpp

SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

EXEC=tests

all:
	$(EXEC)

#$(EXEC): $(OBJECTS)
#	$(CC) $(OBJECTS) -o $(EXEC)

# Generic rule
#%.o: %.cpp
#	$(CC) -c $(CFLAGS) $< -o $@

tests: bin/tests.o bin/workday.o bin/journalentry.o bin/generalworkperiod.o bin/datetime.o
	$(CC) bin/tests.o bin/workday.o bin/journalentry.o bin/generalworkperiod.o bin/datetime.o -o bin/tests

bin/tests.o: src/tests.cpp 
	$(CC) -c src/tests.cpp $(CFLAGS) -o bin/tests.o

bin/datetime.o: src/datetime.cpp
	$(CC) -c src/datetime.cpp $(CFLAGS) -o bin/datetime.o

bin/generalworkperiod.o: src/generalworkperiod.cpp
	$(CC) -c src/generalworkperiod.cpp $(CFLAGS) -o bin/generalworkperiod.o

bin/journalentry.o: src/journalentry.cpp
	$(CC) -c src/journalentry.cpp $(CFLAGS) -o bin/journalentry.o

bin/workday.o: src/workday.cpp
	$(CC) -c src/workday.cpp $(CFLAGS) -o bin/workday.o

clean:
	rm -f bin/*.o bin/$(EXEC)
