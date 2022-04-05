#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int guard(int n, char * err) { if (n == -1) { perror(err); exit(1); } return n; }

char* process(char * input, int* size) {
    char buffer[128];
    strcpy(buffer, input);

    for (int i = 0; i < strlen(buffer); i++)
        printf("buffer[%d]=%c\n", i, buffer[i]);
    if (!strcmp(buffer, "salute")) {
        printf("Saluting\n");
        return "Hello from the server!\n";
    }
    return "Enter a command, help to list\n";
}

int main(void) {
  int listen_fd = guard(socket(PF_INET, SOCK_STREAM, 0), "Could not create TCP socket");
  printf("Created new socket %d\n", listen_fd);
  guard(listen(listen_fd, 100), "Could not listen on TCP socket");
  struct sockaddr_in listen_addr;
  socklen_t addr_len = sizeof(listen_addr);
  guard(getsockname(listen_fd, (struct sockaddr *) &listen_addr, &addr_len), "Could not get socket name");
  printf("Listening for connections on port %d\n", ntohs(listen_addr.sin_port));
  for (;;) {
    int conn_fd = accept(listen_fd, NULL, NULL);
    printf("Got new connection %d\n", conn_fd);
    if (guard(fork(), "Could not fork") == 0) {
      pid_t my_pid = getpid();
      printf("%d: forked\n", my_pid);
      char buf[1024];
      for (;;) {
        ssize_t num_bytes_received = guard(recv(conn_fd, buf, sizeof(buf), 0), "Could not recv on TCP connection");
        if (num_bytes_received == 0) {
          printf("%d: received end-of-connection; closing connection and exiting\n", my_pid);
          guard(shutdown(conn_fd, SHUT_WR), "Could not shutdown TCP connection");
          guard(close(conn_fd), "Could not close TCP connection");
          exit(0);
        }
        printf("%d: received bytes; echoing\n", my_pid);
        int size;
        char *result = process(buf, &size);
        guard(send(conn_fd, result, size, 0), "Could not send to TCP connection");
        printf("%d: echoed bytes; receiving more\n", my_pid);
      }
    } else {
      // Child takes over connection; close it in parent
      close(conn_fd);
    }
  }
  return 0;
}