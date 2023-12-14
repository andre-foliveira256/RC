# Compiler
CC := gcc

# Source files
SRCS := client_main.c server_main.c

# Desired executable names
EXECS := user AS

# Default target
all: $(EXECS)

# Compile each source file into the corresponding executable
user: client_main.c
	$(CC) $< -o $@

AS: server_main.c
	$(CC) $< -o $@

clean:
	rm -f $(EXECS)
