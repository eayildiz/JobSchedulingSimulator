# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Source Files
SRC = job_input.c job.c simulator.c schedule.c

# Object Files
OBJ = job_input.o job.o simulator.o schedule.o

# Output Executable
OUTPUT = schedule.o

# Default Rule
all: $(OUTPUT)

# Linking Rule
$(OUTPUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJ)

# Compilation Rules with Dependencies
job_input.o: job_input.c job_input.h job.h
	$(CC) $(CFLAGS) -c job_input.c

job.o: job.c job.h
	$(CC) $(CFLAGS) -c job.c

simulator.o: simulator.c simulator.h job.h
	$(CC) $(CFLAGS) -c simulator.c

schedule.o: schedule.c job.h job_input.h simulator.h
	$(CC) $(CFLAGS) -c schedule.c

# Clean Rule
clean:
	rm -f $(OBJ) $(OUTPUT)
