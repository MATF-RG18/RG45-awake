PROGRAM = main
CC      = g++
CFLAGS  = -g -ansi -Wall -I/usr/X11R6/include -I/usr/pkg/include -lm
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lGLEW

$(PROGRAM): main.o image.o
	$(CC) $(LDFLAGS) -o $(PROGRAM) image.o main.o $(LDLIBS)

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
