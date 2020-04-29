#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
    int SID;
    struct sockaddr_in server;
    char clientMessage[500];
    char serverMessage[500];
    //Create socket
    SID =  socket(AF_INET, SOCK_STREAM, 0);
    if(SID == -1)
    {
        printf("Error creating socket");
    }else{
        printf("Socket created");
    }
    //set sockaddr_in variables
    server.sin_port =htons ( 8081 );//port to connect on
    server.sin_addr.s_addr=inet_addr("127.0.0.1");//server ip
    server.sin_family = AF_INET;//ipv4 protocol

    //connect to server
    if(connect(SID, (struct sockaddr *)&server, sizeof(server))<0)
    {
        printf("connect failed. Error");
        return 1;
    }

    printf("connected to server ok\n");

    while(1)
    {
        printf("\nEnter message: ");
        scanf("%s", clientMessage);

        //send some data
        if( send ( SID, clientMessage, strlen(clientMessage),0)<0)
        {
            printf("send failed");
            return 1;

        }
        //receive a reply from the server
        if(recv(SID, serverMessage , 500, 0 )<0)
        {
            printf("IO error");
            break;
        }
        printf("\nServer sent:");
        printf(serverMessage);
    }
    close(SID);
    return 0;
} 