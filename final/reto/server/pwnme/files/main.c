#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int guard(int n, char * err) { if (n == -1) { perror(err); exit(1); } return n; }

void give_flag(int sock) {
  char flag[] = "Nah, don't feel like it\n";
  guard(send(sock, flag, strlen(flag), 0), "Could not send to TCP connection");
}

void run_func(int sock) {
  char buffer[128];
  ssize_t num_bytes_received = guard(recv(sock, buffer, 500, 0), "Could not recv on TCP connection");
  printf("[Pista]Buffer empieza en: %p\n", buffer);
  fflush(stdout);
  guard(send(sock, buffer, 500, 0), "Could not send to TCP connection");
  return;
}

int main(void) {
  char buf[1024];
  int listen_fd = guard(socket(PF_INET, SOCK_STREAM, 0), "Could not create TCP socket");
  printf("Created new socket %d\n", listen_fd);
  fflush(stdout);
  struct sockaddr_in listen_addr;
  socklen_t addr_len = sizeof(listen_addr);
  listen_addr.sin_family = AF_INET;
	listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	listen_addr.sin_port = htons(1337);
  bind(listen_fd, (struct sockaddr*)&listen_addr, addr_len);
  guard(listen(listen_fd, 100), "Could not listen on TCP socket");
  guard(getsockname(listen_fd, (struct sockaddr *) &listen_addr, &addr_len), "Could not get socket name");
  printf("Listening for connections on port %d\n", ntohs(listen_addr.sin_port));
  fflush(stdout);
  int conn_fd = accept(listen_fd, NULL, NULL);
  guard(send(conn_fd, "Welcome to the BEC high security server\n", strlen("Welcome to the BEC high security server\n"), 0), "Could not send to TCP connection");

  for (;;) {
    dup2(conn_fd, STDOUT_FILENO);
    dup2(conn_fd, STDERR_FILENO);
    dup2(conn_fd, STDIN_FILENO);
    guard(send(conn_fd, "Enter a command:", 16, 0), "Could not send to TCP connection");
    ssize_t num_bytes_received = guard(recv(conn_fd, buf, sizeof(buf), 0), "Could not recv on TCP connection");
    printf("received %ld bytes; echoing\n", num_bytes_received);
    fflush(stdout);
    
    if (num_bytes_received > 1 && num_bytes_received < 128) {
      if (!strncmp(buf, "cuak", num_bytes_received-1)) {
        guard(send(conn_fd, "Yeah, cuak and stuff\n", strlen("Yeah, cuak and stuff\n"), 0), "Could not send to TCP connection");
        continue;
      }
      if (!strncmp(buf, "flag", num_bytes_received-1)) {
        give_flag(conn_fd);
        continue;
      }
      if (!strncmp(buf, "run", num_bytes_received-1)) {
        run_func(conn_fd);
        continue;
      }
      if (!strncmp(buf, "help", num_bytes_received-1)) {
        guard(send(conn_fd, "No help for you, reverse me better\n", strlen("No help for you, reverse me better\n"), 0), "Could not send to TCP connection");
        continue;
      }    
      if (!strncmp(buf, "end", num_bytes_received-1)) {
        printf("received end-of-connection; closing connection and exiting\n");
        fflush(stdout);
        guard(shutdown(conn_fd, SHUT_WR), "Could not shutdown TCP connection");
        guard(close(conn_fd), "Could not close TCP connection");
        exit(0);
      }

      guard(send(conn_fd, buf, num_bytes_received, 0), "Could not send to TCP connection");
    }
    if (num_bytes_received > 128) {
      guard(send(conn_fd, "No intentes romper esto, prueba con el input en el comando run\n", strlen("No intentes romper esto, prueba con el input en el comando run\n"), 0), "Could not send to TCP connection");
    }
  }
  return 0;
}