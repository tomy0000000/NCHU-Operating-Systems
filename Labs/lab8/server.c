#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for bzero()
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> //for close()
#define PortNumber 5555

int main(int argc, char *argv[]) {
  struct sockaddr_in address;
  int sock, byte_recv;
  char buffer[1024];
  char received_buffer[9] = "received\0";

  sock = socket(PF_INET, SOCK_DGRAM, 0);
  if (sock < 0)
    printf("Error creating socket\n");
  bzero(&address, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_port = htons(PortNumber);
  address.sin_addr.s_addr = INADDR_ANY;
  /*#define INADDR_ANY  ((unsigned long int) 0x00000000)
     INADDR_ANY allows the server to accept a client connection on any
     interface, in case the server host has multiple interfaces.*/
  if (bind(sock, (struct sockaddr *)&address, sizeof(address)) == -1) {
    printf("error binding\n");
    close(sock);
  }
  int address_length = sizeof(address);
  for (;;) {
    byte_recv = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&address, &address_length);
    sendto(sock, received_buffer, sizeof(received_buffer), 0, (struct sockaddr *)&address, address_length);
    if (byte_recv < 0)
      printf("Error recving packet\n");
    printf("data: %s\n", buffer);
  }
}
