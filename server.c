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
        int serv_sockfd = socket(AF_INET,SOCK_STREAM,0);
        struct sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);
        serv_addr.sin_addr.s_addr = INADDR_ANY;

        if(bind(serv_sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){return 0;}
        if(listen(serv_sockfd,1)<0) {return 0;}

        printf("Server listening on port %d.\n",PORT);
        int client_sockfd = accept(serv_sockfd,NULL,NULL);

        char buffer_rec[N];
        char buffer_send[N];

        while(1){
                recv(client_sockfd,buffer_rec,sizeof(buffer_rec),0);
                printf("\nclient socket sent message : %s",buffer_rec);
                if(strcmp(buffer_rec,"Bye") == 0){
                        strcpy(buffer_send,"Goodbye");
                        printf("\nReplied to client\nClient said bye: finishing\n");
                        send(client_sockfd,buffer_send,sizeof(buffer_send),0);
                        break;
                }
                strcpy(buffer_send,"OK");
                printf("\nReplied to client\n");
                send(client_sockfd,buffer_send,sizeof(buffer_send),0);
        }

        close(serv_sockfd);
        return 0;
}