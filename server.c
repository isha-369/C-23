#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<math.h>
#define PORT1 6000
#define PORT2 7000
#define MAXLINE 1024

int main(int argc,char* argv[]) {
    int sockfd,sockfd2,sockfdtcp,sockfdtcp2,connfd,connfd1;
    char buffer[MAXLINE];

    struct sockaddr_in servaddr,servaddr2, cliaddr,servaddrtcp,servaddrtcp2;

if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

 if ( (sockfd2 = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
 if ( (sockfdtcp = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
if ( (sockfdtcp2 = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    memset(&servaddrtcp, 0, sizeof(servaddrtcp));
    memset(&servaddrtcp2, 0, sizeof(servaddrtcp2));
    memset(&servaddr2,0,sizeof(servaddr2));

    servaddr.sin_family    = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT1);


    servaddr2.sin_family    = AF_INET; 
    servaddr2.sin_addr.s_addr = INADDR_ANY;
    servaddr2.sin_port = htons(PORT2);

    
    servaddrtcp.sin_family    = AF_INET; 
    servaddrtcp.sin_addr.s_addr  = INADDR_ANY;
    servaddrtcp.sin_port = htons(PORT1);

    
    servaddrtcp2.sin_family    = AF_INET; 
    servaddrtcp2.sin_addr.s_addr = INADDR_ANY;
    servaddrtcp2.sin_port = htons(PORT2);


if ( bind(sockfd, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
if ( bind(sockfd2, (const struct sockaddr *)&servaddr2,
            sizeof(servaddr2)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if ( bind(sockfdtcp, (const struct sockaddr *)&servaddrtcp,
            sizeof(servaddrtcp)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if ((listen(sockfdtcp, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    if ( bind(sockfdtcp2, (const struct sockaddr *)&servaddrtcp2,
            sizeof(servaddrtcp2)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
     if ((listen(sockfdtcp2, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    int len, n;
    len=sizeof(cliaddr);
  while(1){
  fd_set socks;
  FD_ZERO(&socks);
  FD_SET(sockfd, &socks);
  FD_SET(sockfd2, &socks);
  FD_SET(sockfdtcp, &socks);
  FD_SET(sockfdtcp2, &socks);
  
  int activity=select(FD_SETSIZE,&socks,NULL,NULL,0);
  if(activity>= 0) {
     if (FD_ISSET(sockfd, &socks)) {
       n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                       0, ( struct sockaddr *) &cliaddr,
                       &len);

            buffer[n] = '\0';

            printf(" datagram from client port 6000: %s\n", buffer);

            printf("Length: %ld\n", strlen(buffer));
     }
     if (FD_ISSET(sockfd2, &socks)) {
      n = recvfrom(sockfd2, (char *)buffer, MAXLINE,
                       0, ( struct sockaddr *) &cliaddr,
                       &len);

            buffer[n] = '\0';

            printf("datagram from client port 7000: %s\n", buffer);
            printf("Length: %ld\n", strlen(buffer));
     }
     if(FD_ISSET(sockfdtcp,&socks)){
         connfd = accept(sockfdtcp, (struct sockaddr*)&cliaddr, &len);
         read(connfd, buffer, sizeof(buffer));
        printf("message from client", buffer);

     }
     if(FD_ISSET(sockfdtcp2,&socks)){
         connfd = accept(sockfdtcp2, (struct sockaddr*)&cliaddr, &len);
         read(connfd, buffer, sizeof(buffer));
        printf("message from client", buffer);

     }
}
}
return 0;

}

