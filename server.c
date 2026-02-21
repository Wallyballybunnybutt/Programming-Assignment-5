// #include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> //I'm on windows
#include <sys/types.h>

#define MAX 256

int main(int argc, char const* arg[])
{   //https://stackoverflow.com/questions/64642216/best-practice-for-initializing-winsock-in-a-networking-library
    //https://www.youtube.com/watch?v=l-QCr8krKog
    WSADATA wsa; //initializes winstock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }
    // create server socket 
    int serverSocketID = socket(AF_INET, SOCK_STREAM, 0);

    // string store data to be sent to client 
    char serverMsg[255] = "Server -> Client: Hello Client"; //message too big
    if (serverSocketID < 0) {
        printf("Error: Socket creation failed.\n");
        return 1;
    }
    // define server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9001);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocketID, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("Error: bind FAILED.\n");
        return 1;
    }

    if (listen(serverSocketID, 1) < 0) {
        printf("Error: FAILED.\n");
        return 1;
    }
    printf("Listening for Connections\n");
    listen(serverSocketID, 1);
    // listen for connections 
    // second parameter that this server will keep a backlog of 1 request 
    

    // define variable to hold client socket
    while (1) { //infinite loop
        int clientSocket = accept(serverSocketID, NULL, NULL);
        if (clientSocket < 0) {
            printf("There was an error: Accept failed!\n");
            continue;
        }
        char filename[MAX]; //filename from client
        char buffer[MAX];
        int i = 1;

        recv(clientSocket, filename, MAX, 0);
        FILE *file;
        file = fopen(filename, "r");

        if (!file) {
            send(clientSocket, "Error: FNF.", MAX, 0); //file not found
        } else {
            char buffer[MAX + 1];
            int bytes = fread(buffer, 1, MAX + 1, file); 

            if (bytes > MAX) {
                send(clientSocket, serverMsg, MAX, 0); //sends Default message
            } else {
                buffer[bytes] = '\0';
                send(clientSocket, buffer, MAX, 0); //sends message
            }

        }
        fclose(file);
    }
    printf("Responded to client request!\n");
    WSACleanup();
    return 0;
}
