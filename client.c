#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> //I'm on windows
#include <sys/types.h>

#define MAX 256

int main(int argc, char const* arg[])
{
    //https://stackoverflow.com/questions/64642216/best-practice-for-initializing-winsock-in-a-networking-library
    //https://www.youtube.com/watch?v=l-QCr8krKog
    WSADATA wsadata; //initializes winstock
    if (WSAStartup(MAKEWORD(2,2), &wsadata) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }


    // create server socket 
    int serverSocketID = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocketID < 0) {
        printf("Error: Socket creation failed.\n");
        return 1;
    }
    // define server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9001);
    serverAddr.sin_addr.s_addr = inet_addr("192.168.7.208"); //ip address
    if (connect(serverSocketID, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("Error: Could not connect to the server. \n");
        return 1; //tries to connect client to server
    }
    else {
        char filename[MAX];
        char serverMsg[MAX + 1];

        printf("Enter filename: ");
        scanf("%s", filename);

        send(serverSocketID, filename, MAX, 0); //sends filename to server
        int byte = recv(serverSocketID, serverMsg, MAX, 0);

        if (byte < 0) {
            printf("FAILED. \n");
        } else {
            serverMsg[byte] = '\0';
            printf("Message from the Server: %s\n", serverMsg); //should be what is in hello.txt
        }
    }
    closesocket(serverSocketID);
    WSACleanup();
    return 0;

}