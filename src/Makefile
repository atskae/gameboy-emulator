PROG = gameboy
CC = g++
CFLAGS = -Wall -g
OBJS = main.o CPU.o Insn.o Reg.o

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp 

CPU.o: CPU.cpp
	$(CC) $(CFLAGS) -c CPU.cpp 

Insn.o: Insn.cpp
	$(CC) $(CFLAGS) -c Insn.cpp 

Reg.o: Reg.cpp
	$(CC) $(CFLAGS) -c Reg.cpp 

clean:
	rm *.o $(PROG)	
