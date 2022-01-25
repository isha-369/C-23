#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define MAXLINE 1024
int main(int argc, char* argv[]) {
    int sockfd;
    
    char *message=malloc(0);
    
    strcpy(message,argv[2]);

    int length=strlen(argv[2]);
    char *lengthPart=calloc(4 , sizeof(char));
    int i;
    for(i=3;i>=0;i--)
    {
        int t=length%10;
        lengthPart[i]=t+'0';
        t/=10;
    }
    strcat(lengthPart,message)
    struct sockaddr_in  servaddr;

    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));


 servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[1]));
    servaddr.sin_addr.s_addr = INADDR_ANY;
     if (connect(sockfd, (struct sockaddr*)&servaddr,sizeof(servaddr)) < 0) {
        printf("\n Error : Connect Failed \n");
    }
    
    write(sockfd, lengthPart, strlen(lengthPart));
    close(sockfd);
return 0;
}