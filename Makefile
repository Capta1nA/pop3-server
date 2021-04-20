CC=gcc
CFLAGS=-std=c99
BINS=server
OBJS=server.o threadpool.o workqueue.o

all: $(BINS)

server: $(OBJS)
	$(CC) $(CFLAGS) -c -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.dSYM $(BINS)