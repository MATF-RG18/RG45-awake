PROGRAM = main
CC      = g++
CFLAGS  = -g -ansi -Wall -I/usr/X11R6/include -I/usr/pkg/include -lm
CXXFLAGS = -Wno-write-strings
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL ${PWD}/libIrrKlang.so -pthread

$(PROGRAM): main.o image.o
	$(CC) $(LDFLAGS) -o $(PROGRAM) image.o main.o $(LDLIBS)

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM)

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
