#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

int main() 
{
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == -1)
    {
        perror("socket() failed");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9000);

    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr))) 
    {
        perror("bind() failed");
        return 1;
    }

    if (listen(listener, 5)) 
    {
        perror("listen() failed");
        return 1;
    }
    int num_process=8;
    for(int i=0;i< num_process;i++){
        if(fork()==0){
            while (1) {
                // Ch? k?t n?i m?i
                int client = accept(listener, NULL, NULL);
                printf("New client connected: %d\n", client);
                
                // Nh?n d? li?u t? client và in ra màn hình
                char buf[256];
                int ret = recv(client, buf, sizeof(buf), 0);
                buf[ret] = 0;
                puts(buf);
                
                // Tr? l?i k?t qu? cho client
                char *msg = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Xin chao cac ban</h1></body></html>";
                send(client, msg, strlen(msg), 0);
                
                // Ðóng k?t n?i
                close(client);
            }
            
            return 0;
        }
     }
     //Ti?n trình cha
     
     //Ðóng socket
     close(listener);
     // Ch? ti?n trình con k?t thúc
    for (int i = 0; i < num_process; i++) {
        wait(NULL);
    }
    
    return 0;
}
