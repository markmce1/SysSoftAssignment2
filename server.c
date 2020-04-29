#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
    int s;
    int cs;
    int connSize;
    int READSIZE;
    struct sockaddr_in server, client;
    char message[500];

    //create socket
    s=socket(AF_INET, SOCK_STREAM,0);
    if(s==-1)
    {
        printf("could not create socket");
    }else{
        printf("Socket succesfully created");
    }

    //set sockaddr_in variables
    server.sin_port = htons( 8081 ); // SET THE PROT FOR COMMS
    server.sin_family = AF_INET; //USE IPV4
    server.sin_addr.s_addr = INADDR_ANY;
    //WHEN IDADDR_ANY IS SPECIFIED IN THE BIND CALL, THE
    //SOCKET WILL BE BOUND TO ALL LOCAL INTERNFACES

    //bind
    if( bind(s,(struct  sockaddr *)&server, sizeof(server))<0)
    {
        perror("Bind issue!");
        return 1;
    }else{
        printf("Bind complete");
    }
    //listen for a connection
    listen(s,3);
    //accept and incoming connection
    printf("waiting for incoming connection from client>>");
    connSize=sizeof(struct sockaddr_in);

    //accept connection from an incoming client
    cs = accept(s,(struct sockaddr *)&client, (socklen_t*)&connSize);
    if ( cs < 0)
    {
        perror("can't establish connection");
        return 1;
    }
    else{
        printf("connection from client accepted");
    }

    while(1){
        memset(message,0,500);
        //READSIZE =read( cs,message,500);
        READSIZE = recv(cs, message, 2000,0);
        printf("Client said: %s\n", message);
        //puts(message);
        write(cs,"What ?? ", strlen("what ??"));

    }
    if(READSIZE ==0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(READSIZE == -1)
    {
        perror("Read error");
    }
    return 0;

}
