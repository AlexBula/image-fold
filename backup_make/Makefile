TARGETS= transform

CXX = g++
CXXFLAGS = -Wall -O3 -pthread -ldlib -lpng -std=c++17

all: $(TARGETS)

transform: transform.o img-transform.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -pthread -ldlib -lpng
	
.PHONY: clean

clean:
	rm -f $(TARGETS) *.o *~ *.bak
