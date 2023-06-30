#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define PORT 3599
int main() {
 int sockfd, newSockFd, size, firstTime = 1, currentPacket;
 char data[100];
 struct sockaddr_in client;
 memset(&client, 0, sizeof(client));
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 if (sockfd == -1) {
 printf("Error in socket creation\n");
 } else {
 printf("Socket created\n");
 }
 client.sin_family = AF_INET;
 client.sin_port = PORT;
 client.sin_addr.s_addr = inet_addr("127.0.0.1");
 printf("Starting up\n");
 size = sizeof(client);
 printf("Establishing Connection\n");
 if (connect(sockfd, (struct sockaddr *)&client, size) == -1) {
 printf("Error in Connecting to Server\n");
 exit(1);
 } else {
 printf("Connection Established\n");
 }
 memset(&data, 0, sizeof(data));
 sprintf(data, "REQUEST");
 if (send(sockfd, data, strlen(data), 0) == -1) {
 printf("Error is Sending Request for Data\n");
 exit(1);
 }
 do {
 memset(&data, 0, sizeof(data));
 recv(sockfd, data, 100, 0);
 currentPacket = atof(data);
 printf("Got packet: %d\n", currentPacket);
 if (currentPacket == 3 & firstTime) {
 printf("Simulation: Packet Data Corrupted or incomplete\n");
 printf("Sending RETRANSMIT\n");
 memset(&data, 0, sizeof(data));
 sprintf(data, "RETRANSMIT");
 if (send(sockfd, data, strlen(data), 0) == -1) {
 printf("Error in sending RETRANSMIT\n");
 exit(1);
 }
 firstTime = 0;
 } else {
 printf("Packet accepted, sending ACK\n");
 }
 memset(&data, 0, sizeof(data));
 sprintf(data, "ACK");
 if (send(sockfd, data, strlen(data), 0) == -1) {
 printf("Error in sending ACK\n");
 exit(1);
 }
 } while (currentPacket = 5);
 printf("All packets recieved, exiting\n");
 close(sockfd);
}
