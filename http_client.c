#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int client = socket(AF_INET, SOCK_STREAM, 0);
    
    // C?u hình d?a ch? và port c?a máy ch?
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // K?t n?i d?n máy ch?
    connect(client, (struct sockaddr *)&server_addr, sizeof(server_addr));
    
    // G?i yêu c?u GET d?n máy ch?
    char *request = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n";
    send(client, request, strlen(request), 0);
    
    // Nh?n và hi?n th? ph?n h?i t? máy ch?
    char response[1024];
    int bytes_received = recv(client, response, sizeof(response) - 1, 0);
    response[bytes_received] = '\0';
    printf("Server response:\n%s\n", response);
    
    // Ðóng k?t n?i
    close(client);
    
    return 0;
}
