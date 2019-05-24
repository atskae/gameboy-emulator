PROG = gameboy
CC = g++
CFLAGS = -Wall -g
OBJS = main.o CPU.o

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp 

CPU.o: CPU.cpp
	$(CC) $(CFLAGS) -c CPU.cpp 

clean:
	rm *.o $(PROG)	
