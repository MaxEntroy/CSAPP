CXX= g++ -std=c++17
CXXFLAGS= -g -Wall -Wextra
LDFLAGS=
LIBS= -pthread

main: main.o
	$(CXX) -o $@ $(LDFLAGS) main.o $(LIBS)

main.o: main.cc mysem.h

clean:
	rm -rf main main.o

.PHONY: clean
