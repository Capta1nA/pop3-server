# the compiler gcc for C program, define as g++ for C++
PROJ = server.c
CC = gcc
DOXYGEN = doxygen #name of doxygen binary


# compiler flags:
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -std=c99 -lpthread -Wall
LFLAGS = -lm

# the build target executable:
TARGET = server
default: all

all: $(TARGET)

$(TARGET): server.c threadpool.c workqueue.c handler.c authorization.c TRANSACTION.c config.c
	$(CC) server.c threadpool.c workqueue.c handler.c authorization.c TRANSACTION.c config.c $(CFLAGS) -o $(TARGET) 

clean:
	-rm -f $(TARGET) 