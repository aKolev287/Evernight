CC = gcc
CFLAGS = -Wall -g

evernight: main.o terminal.o input.o file.o
	$(CC) $(CFLAGS) -o evernight main.o terminal.o input.o file.o

%.o: %.c editor.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o evernight