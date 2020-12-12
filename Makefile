CC=gcc
CFLAGS=-Wall -I.
LDFlags=
OBJFILES=bencode.o test_bencode.o 
TARGET=test_bencode

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~