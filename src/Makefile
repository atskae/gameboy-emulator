PROG = gameboy
CC = g++
CFLAGS = -Wall -g
OBJS = main.o CPU.o Insn.o Operand.o

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp 

CPU.o: CPU.cpp
	$(CC) $(CFLAGS) -c CPU.cpp 

Insn.o: Insn.cpp
	$(CC) $(CFLAGS) -c Insn.cpp 

Operand.o: Operand.cpp
	$(CC) $(CFLAGS) -c Operand.cpp 

clean:
	rm *.o $(PROG)	
