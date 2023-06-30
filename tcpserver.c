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
struct sockaddr_in server, cli;
int cli_len;
int sd, n, i, len;
int data, temp;
char buffer[100];
if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
{
perror("Socket failed:");
exit(1);
}
// server socket address structure initialisation
bzero(&server, sizeof(server) );
server.sin_family = AF_INET;
server.sin_port = htons(atoi(argv[1]));
server.sin_addr.s_addr = htonl(INADDR_ANY);
if(bind(sd, (struct sockaddr*)&server, sizeof(server)) < 0)
{
perror("bind failed:");
exit(1);
}
listen(sd,5);
if((data = accept(sd , (struct sockaddr *) &cli, &cli_len)) < 0)
{
perror("accept failed:");
exit(1);
}
read(data,buffer, sizeof(buffer));
len = strlen(buffer);
for( i =0; i<= len/2; i++)
{
temp = buffer[i];
buffer[i] = buffer[len - 1-i];
buffer[len-1-i] = temp;
}
write (data,buffer, sizeof(buffer));
close(data);
close(sd);
}
