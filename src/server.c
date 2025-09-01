#include "server.h"
#include "html_file.h"
#include "mime_types.h"
#include <magic.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

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

void handle_client(int client_fd, const char *file_path, size_t filesize,
                   magic_t magic) {
  char request_buf[1024];
  int valread = recv(client_fd, request_buf, sizeof(request_buf) - 1, 0);

  const char *mime = get_mime_type(magic, file_path);

  // response message
  dprintf(client_fd,
          "HTTP/1.1 200 OK\r\n"
          "Content-Type: %s\r\n"
          "Content-Length: %ld\r\n"
          "\r\n",
          mime, filesize);

  if (valread > 0) {
    request_buf[valread] = '\0';
    printf("Recieved: %s\n", request_buf);
    write(client_fd, file_path, filesize);
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

  struct html_file page = read_file(getenv("HTML_PAGE"));
  if (!page.file_buffer) {
    perror("HTML page could not be loaded");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  printf("Server is listening on port %d\n", PORT);
  printf("(Press CTRL + C to quit)\n");

  magic_t magic = init_magic();
  if (!magic)
    exit(EXIT_FAILURE);

  while (1) {
    // accept connection
    int client_fd =
        accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
    if (client_fd < 0) {
      perror("Accept failed");
      continue;
    }

    // handle connection
    handle_client(client_fd, page.file_buffer, page.filesize, magic);
    close(client_fd);
  }
  free_file(&page);
  free_mime(magic);
  close(server_fd);
}
