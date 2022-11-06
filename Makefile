CXX = g++ -std=c++17 -O3 -Wall -Wextra -pedantic
MAIN_BINARIES = $(basename $(wildcard *Main.cpp))
TEST_BINARIES = $(basename $(wildcard *Test.cpp))
HEADERS = $(wildcard *.h)
OBJECTS = $(addsuffix .o, $(basename $(filter-out %Main.cpp %Test.cpp, $(wildcard *.cpp))))

.PRECIOUS: %.o
.SUFFIXES:
.PHONY: all compile test valgrind checkstyle clean

all: compile test checkstyle

compile: $(MAIN_BINARIES) $(TEST_BINARIES)

test: $(TEST_BINARIES)
	for T in $(TEST_BINARIES); do ./$$T || exit; done

valgrind: $(TEST_BINARIES)
	for T in $(TEST_BINARIES); do valgrind --leak-check=full ./$$T; done

checkstyle:
	python3 ../cpplint.py --repository=. *.h *.cpp

clean:
	rm -f *.o
	rm -f $(MAIN_BINARIES)
	rm -f $(TEST_BINARIES)

%Main: %Main.o $(OBJECTS)
	$(CXX) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) -c $<
