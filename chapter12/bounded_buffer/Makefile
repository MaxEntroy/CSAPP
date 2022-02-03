CXX= g++ -std=c++17
CXXFLAGS= -g -Wall -Wextra
LDFLAGS=
LIBS= -pthread

main: main.o bounded_buffer.o
	$(CXX) -o $@ $(LDFLAGS) main.o bounded_buffer.o $(LIBS)

bounded_buffer.o: bounded_buffer.cc bounded_buffer.h
main.o: main.cc bounded_buffer.h mysem.h

clean:
	rm -rf  bounded_buffer.o main.o main

.PHONY: clean
