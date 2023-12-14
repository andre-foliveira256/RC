# Makefile for server and client programs

CC = gcc

# Define the targets and their dependencies
all: server client

server: server_main.c
	$(CC) $(CFLAGS) -o AS server_main.c

client: client_main.c
	$(CC) $(CFLAGS) -o user client_main.c

# Clean rule
clean:
	rm -f AS user
