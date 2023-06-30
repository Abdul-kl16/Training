#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define PORT 3599
void itos(int number, char numberString[]) {
 numberString[0] = (char)(number + 48);
 numberString[1] = '\0';
}
int main() {
 int sockfd, newSockFd, size, currentPacket = 1;
 char buffer[100];
 socklen_t len;
 struct sockaddr_in server, client;
 memset(&server, 0, sizeof(server));
 memset(&client, 0, sizeof(client));
 if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
 printf("Error in socket creation\n");
 exit(1);
 } else {
 printf("Socket created successfully\n");
 }
 server.sin_family = AF_INET;
 server.sin_port = PORT;
 server.sin_addr.s_addr = INADDR_ANY;
 printf("Starting up\n");
 if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
 printf("Binding error\n");
 exit(1);
 } else {
 printf("Binding completed successfully, waiting for connection\n");
 }
 len = sizeof(client);
 if (listen(sockfd, 20) = -1) {
 if ((newSockFd = accept(sockfd, (struct sockaddr *)&client, &len)) == -1) {
 printf("Error in accepting connection\n");
 exit(1);
 }
 memset(&buffer, 0, sizeof(buffer));
 if (recv(newSockFd, buffer, 100, 0) == -1) {
 printf("Receive error, exiting\n");
 exit(1);
 }
 printf("Received a request from client, sending packets one by one\n");
 do {
 memset(&buffer, 0, sizeof(buffer));
 itos(currentPacket, buffer);
 send(newSockFd, buffer, 100, 0);
 printf("Packet send: %d\n", currentPacket);
 memset(&buffer, 0, sizeof(buffer));
 recv(newSockFd, buffer, 100, 0);
 currentPacket++;
 if (strcmp(buffer, "RETRANSMIT") == 0) {
 currentPacket--;
 printf("Received a RETRANSMIT packet, resending last packet\n");
 }
 sleep(1);
 } while (currentPacket = 6);
 } else {
 printf("Error in listening\n");
 exit(1);
 }
 close(sockfd);
 close(newSockFd);
 printf("Sending complete, sockets closed, exiting\n");
}
