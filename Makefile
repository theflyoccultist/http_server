CC=gcc
CFLAGS=-g -O0 -Wall -Wextra

SRCS=src/main.c src/server.c src/html_file.c
OBJ=$(SRCS:.c=.o)
BIN=http_server

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ)

clean:
	rm -f $(OBJ) $(BIN)
