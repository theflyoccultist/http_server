CC=gcc
CFLAGS=-g -O0 -Wall -Wextra
LDFLAGS=-lmagic

SRCS=src/main.c src/server.c src/html_file.c src/mime_types.c
OBJ=$(SRCS:.c=.o)
BIN=http_server

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ) $(BIN)
