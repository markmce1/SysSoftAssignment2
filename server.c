#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>




int main(int argc, char *argv[])
{
    int s;
    int cs;
    int connSize;
    int READSIZE;
    struct sockaddr_in server, client;

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

    //receieving files
    FILE *fp;
    int ch =0;
    char buffer[1024];
    char file_name[300];
    //somehow read in file_name
    read(cs, file_name, 255);
    fp = fopen(file_name, "a");
    int words;

    read(cs, &words, sizeof(int));

    while(ch !=words)
    {
        read(cs, buffer, 255);
        fprintf(fp, "%s", buffer);
        ch++;
    }
    printf("The file has been received");//check if file is there in that location, otherwise say did not write

    close(cs);
    close(s);

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
