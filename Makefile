CC=gcc
CFLAGS=-Wall -Wextra
SRCS=src/main.c src/server.c
OBJ=$(SRCS:.c=.o)
BIN=http_server

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ)

clean:
	rm -f $(OBJ) $(BIN)
