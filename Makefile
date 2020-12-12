CC=gcc
CFLAGS=-I.
DEPS = bencode.h
OBJ = bencode.o test_bencode.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bencodemake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)