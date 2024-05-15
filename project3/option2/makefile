CC = gcc
CFLAGS = -Wall -g

all: filesystem

filesystem: filesystem_manager.o filesystem_operations.o
    # Make sure to use a Tab character for indentation on the next line
	$(CC) $(CFLAGS) -o filesystem filesystem_manager.o filesystem_operations.o

filesystem_manager.o: filesystem_manager.c filesystem_structs.h
    # Make sure to use a Tab character for indentation on the next line
	$(CC) $(CFLAGS) -c filesystem_manager.c

filesystem_operations.o: filesystem_operations.c filesystem_structs.h
    # Make sure to use a Tab character for indentation on the next line
	$(CC) $(CFLAGS) -c filesystem_operations.c

clean:	
    # Make sure to use a Tab character for indentation on the next line
	rm -f *.o filesystem
