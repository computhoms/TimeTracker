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

tests: bin/tests.o bin/datetime.o bin/generalworkperiod.o bin/journalentry.o bin/workday.o bin/timetracker.o bin/duration.o bin/timeplanner.o
	$(CC) -std=c++11 -o bin/tests $^ $(LDFLAGS)

# Construct object files from src cpp files
bin/%.o:src/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

# bin/tests.o: src/tests.h $(LIBINCLUDES)
# bin/datetime.o: src/datetime.h
# bin/generalworkperiod.o: src/generalworkperiod.h
# bin/journalentry.o: src/journalentry.h
# bin/workday.o: src/workday.h
# bin/timetracker.o: src/timetracker.h



# bin/datetime.o: src/datetime.cpp src/datetime.h
# 	$(CC) -c src/datetime.cpp $(CFLAGS) -o bin/datetime.o

# bin/generalworkperiod.o: src/generalworkperiod.cpp src/generalworkperiod.h
# 	$(CC) -c src/generalworkperiod.cpp $(CFLAGS) -o bin/generalworkperiod.o

# bin/journalentry.o: src/journalentry.cpp src/journalentry.h
# 	$(CC) -c src/journalentry.cpp $(CFLAGS) -o bin/journalentry.o

# bin/workday.o: src/workday.cpp src/workday.h
# 	$(CC) -c src/workday.cpp $(CFLAGS) -o bin/workday.o

# bin/tests.o: src/tests.cpp
# 	$(CC) -c src/tests.cpp $(CFLAGS) -o bin/tests.o

# bin/timetracker.o: src/timetracker.cpp src/timetracker.h
# 	$(CC) -c src/timetracker.cpp $(CFLAGS) -o bin/timetracker.o

clean:
	rm -f bin/*.o bin/$(EXEC)
