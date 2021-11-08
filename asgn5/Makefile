EXEC = encode decode node pq code io stack huffman
SOURCES = $(wildcard *.c)
OBJECTS = node.o pq.o code.o io.o stack.o huffman.o
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra -O2
LDFLAGS = -lm

all: encode decode

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

encode: $(OBJECTS) encode.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

decode: $(OBJECTS) decode.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^


%.o: %.c
	$(CC) $(CFLAGS) -c $<

tidy:
	rm -rf $(OBJECTS) encode.o decode.o

clean: tidy
	 rm -rf $(EXEC) encode decode
format:
	clang-format -i -style=file *.c *.h

