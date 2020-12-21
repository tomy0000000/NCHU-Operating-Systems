#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for bzero()
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> //for close()
#define Server_PortNumber 5555
#define Server_Address "172.17.0.2"

int main(int argc, char *argv[]) {
  struct sockaddr_in address;
  int sock, byte_sent, byte_recv;
  char buffer[1024];
  char received_buffer[1024];

  sock = socket(PF_INET, SOCK_DGRAM, 0);
  if (sock < 0)
    printf("Error creating socket\n");

  bzero(&address, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_port = htons(Server_PortNumber);
  address.sin_addr.s_addr = inet_addr(Server_Address);
  int address_length = sizeof(address);

  while (1) {
    printf("$ ");
    fgets(buffer, 1024, stdin);
    byte_sent = sendto(sock, buffer, sizeof(buffer), 0,
                       (struct sockaddr *)&address, address_length);
    if (byte_sent < 0)
      printf("Error sending packet\n");
    byte_recv = recvfrom(sock, received_buffer, sizeof(received_buffer), 0, (struct sockaddr *)&address, &address_length);
    if (byte_recv < 0)
      printf("Error recving packet\n");
    printf("data: %s\n", received_buffer);
  }

  close(sock);
  return 0;
}
