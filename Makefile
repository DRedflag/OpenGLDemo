CXX = g++
LDFLAGS = `pkg-config --libs --cflags glew` -lglut -lm
CFLAGS = -Wall -Iinclude

SRC_DIR = src 
VPATH = src

all:	main.o \
	translation.o \
	mathcore.o \
	util.o
	$(CXX) $^ $(CFLAGS) -o main $(LDFLAGS) -g  

%.o: %.cc
	$(CXX) $< $(CFLAGS) -o $@ -c -g

run: all
	./main
clear:
	rm -rf main *.o
