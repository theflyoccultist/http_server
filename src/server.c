#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

struct sockaddr_in server_addr, client_addr; // server and client addresses

int create_server_socket(int port) {
  server_addr.sin_family = AF_INET;         // IPv4
  server_addr.sin_addr.s_addr = INADDR_ANY; // localhost
  server_addr.sin_port = htons(port);

  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  return server_fd;
}

void handle_client(int client_fd, const char *file_path) {
  char request_buf[1024];
  int valread = recv(client_fd, request_buf, sizeof(request_buf) - 1, 0);

  if (valread > 0) {
    request_buf[valread] = '\0';
    printf("Recieved: %s\n", request_buf);
    send(client_fd, file_path, strlen(file_path), 0);
    printf("Message sent\n");
  }
}

void start_server() {
  socklen_t server_len = sizeof(server_addr);
  socklen_t addr_len = sizeof(client_addr);

  // Make socket
  int server_fd = create_server_socket(PORT);
  if (server_fd < 0) {
    perror("Failed to create socket");
    exit(EXIT_FAILURE);
  }

  // bind socket to port
  if (bind(server_fd, (struct sockaddr *)&server_addr, server_len) == -1) {
    perror("Bind failed");
    exit(EXIT_FAILURE);
  }

  // listen for connections
  if (listen(server_fd, 10) == -1) {
    perror("Listen failed");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  printf("Server is listening on port %d\n", PORT);

  // response message
  const char *hello = "HTTP/1.1 200 OK\r\n"
                      "Content-Type: text/plain\r\n"
                      "Content-Length: 10\r\n"
                      "\r\n"
                      "Pwat Pwat\n";

  while (1) {
    // accept connection
    int client_fd =
        accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
    if (client_fd < 0) {
      perror("Accept failed");
      continue;
    }

    // handle connection
    handle_client(client_fd, hello);
    close(client_fd);
  }

  close(server_fd);
}
