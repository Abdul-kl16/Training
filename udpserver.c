#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<stdlib.h>
main(int argc, char * argv[])
{
int n;
int sock_fd;
int i,j,k;
int row_1, row_2, col_1, col_2;
struct sockaddr_in servaddr, cliaddr;
int len = sizeof(cliaddr);
int matrix_1[10][10], matrix_2[10][10], matrix_product[10][10];
int size[2][2];
if(argc != 2)
{
fprintf(stderr, "Usage: ./server port\n");
exit(1);
}
if((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
{
printf("Cannot create socket\n");
exit(1);
}
bzero((char*)&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(atoi(argv[1]));
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
if(bind(sock_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
{
perror("bind failed:");
exit(1);
}
// MATRICES RECEIVE
if((n = recvfrom(sock_fd, size, sizeof(size), 0, (struct sockaddr *)&cliaddr, &len)) == -1)
{
perror("size not received:");
exit(1);
}
// RECEIVE MATRIX 1
if((n = recvfrom(sock_fd, matrix_1, sizeof(matrix_1), 0, (struct sockaddr *)&cliaddr, &len)) == -1)
{
perror("matrix 1 not received:");
exit(1);
}
// RECEIVE MATRIX 2
if((n = recvfrom(sock_fd, matrix_2, sizeof(matrix_2), 0, (struct sockaddr *)&cliaddr, &len)) == -1)
{
perror("matrix 2 not received:");
exit(1);
}
row_1 = size[0][0];
col_1 = size[0][1];
row_2 = size[1][0];
col_2 = size[1][1];
for (i =0; i < row_1 ; i++)
for (j =0; j <col_2; j++)
{
matrix_product[i][j] = 0;
}
for(i =0; i< row_1 ; i++)
for(j=0; j< col_2 ; j++)
for (k=0; k < col_1; k++)
{
matrix_product[i][j] += matrix_1[i][k]*matrix_2[k][j];
}
n = sendto(sock_fd, matrix_product, sizeof(matrix_product),0, (struct sockaddr*)&cliaddr,
sizeof(cliaddr));
if( n < 0)
{
perror("error in matrix product sending");
exit(1);
}
close(sock_fd);
}

