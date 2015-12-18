# Makefile for the smash program
CFLAGS = -g -Wall -pthread
CC = gcc $(CFLAGS)
CCLINK = $(CC)
OBJS = main.o list.o
RM = rm -f
# Creating the  executable
Bank: $(OBJS)
	$(CCLINK) -o Bank $(OBJS)
# Creating the object files
main.o: main.c Account.h

list.o: list.c list.h Account.h

# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*

