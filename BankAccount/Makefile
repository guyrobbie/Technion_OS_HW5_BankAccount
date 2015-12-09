# Makefile for the smash program
#CC = gcc
#CFLAGS = -g -Wall
#CCLINK = $(CC)
#OBJS = main.o
#RM = rm -f
## Creating the  executable
#Bank: $(OBJS)
#	$(CCLINK) -o Bank $(OBJS)
## Creating the object files
#main.o: BankAccount/main.c
## Cleaning old files before new make
#clean:
#	$(RM) $(TARGET) *.o *~ "#"* core.*
CC=gcc
CFLAGS=-g -Wall -lpthread
LDFLAGS=
SOURCES= ./BankAccount/main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=Bank

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@