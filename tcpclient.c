#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
int main( int argc, char *argv[])
{
struct sockaddr_in server;
int sd ;
char buffer[200];
if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
{
perror("Socket failed:");
exit(1);
}
// server socket address structure initialisation
bzero(&server, sizeof(server) );
server.sin_family = AF_INET;
server.sin_port = htons(atoi(argv[2]));
inet_pton(AF_INET, argv[1], &server.sin_addr);
if(connect(sd, (struct sockaddr *)&server, sizeof(server))< 0)
{
perror("Connection failed:");
exit(1);
}
fgets(buffer, sizeof(buffer), stdin);
buffer[strlen(buffer) - 1] = '\0';
write (sd,buffer, sizeof(buffer));
read(sd,buffer, sizeof(buffer));
printf("%s\n", buffer);
close(fd);
}
