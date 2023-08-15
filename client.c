#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

#define N 100
#define PORT 6567

int main()
{
        int sockfd = socket(AF_INET,SOCK_STREAM,0);
        struct sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);
        serv_addr.sin_addr.s_addr = INADDR_ANY;

        int status = connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

        if(status == -1){
            printf("Error in making the connection\n");
            return 0;
        }
        printf("Connection established!\n");
        char buffer_rec[N],buffer_send[N];
        while(1){
                printf("\nPlease enter the message to the server: ");
                gets(buffer_send);
                send(sockfd,buffer_send,sizeof(buffer_send),0);

                recv(sockfd,buffer_rec,sizeof(buffer_rec),0);

                printf("\nServer replied: %s\n",buffer_rec);

                if(strcmp(buffer_rec,"Goodbye") == 0 && strcmp(buffer_send,"Bye") == 0){
                        break;
                }
                else if(strcmp(buffer_rec,"Goodbye") == 0 && strcmp(buffer_send,"Bye") != 0){
                        printf("\nERROR wrong reply from server\n");
                        break;
                }
        }
        close(sockfd);
        return 0;
}