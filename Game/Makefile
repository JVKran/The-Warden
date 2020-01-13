CC = g++
CFLAGS = -g -Wall
SRCS = main.cpp
PROG = main

OPENCV = `pkg-config opencv --cflags --libs`
LIBS = $(OPENCV)

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS)

.PHONY: clean run

clean:
	rm *.o $(PROG)

run:
	@./main