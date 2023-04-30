CXX = g++
LDFLAGS = `pkg-config --libs --cflags glew` -lglut
CFLAGS = -Wall -Iinclude

SRC_DIR = src 
VPATH = src

all: main.o
	$(CXX) $^ $(CFLAGS) -o main $(LDFLAGS) -g  

%.o: %.cc
	$(CXX) $< $(CFLAGS) -o $@ -c -g

clear:
	rm -rf main *.o
