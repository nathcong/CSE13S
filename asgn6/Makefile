EXEC = decrypt encrypt keygen numtheory randstate rsa
SOURCES = $(wildcard *.c)
OBJECTS = numtheory.o randstate.o rsa.o
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra -O2 $(shell pkg-config --cflags gmp) -g
LDFLAGS = -lm $(shell pkg-config --libs gmp)

all: decrypt encrypt keygen

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

encrypt: $(OBJECTS) encrypt.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

decrypt: $(OBJECTS) decrypt.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

keygen: $(OBJECTS) keygen.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

tidy:
	rm -rf $(OBJECTS) encrypt.o decrypt.o keygen.o

clean: tidy
	 rm -rf $(EXEC) encrypt decrypt keygen

format:
	clang-format -i -style=file *.c *.h

