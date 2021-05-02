#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define ERROR(msg) std::cerr << "Client Error: " << msg << ". " << strerror(errno) << std::endl;
#define LOG(msg) std::cout << "Client Log: " << msg << std::endl;

int main()
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd == -1)
    {
        ERROR("Cannot create socket");
        return -1;
    }
    LOG("Socket created");

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("192.168.1.6");
    addr.sin_port = htons(1500);

    if(connect(socket_fd, (sockaddr*)&addr, sizeof(struct sockaddr_in))==-1)
    {
        ERROR("Cannot connect");
        return -1;
    }
    LOG("Connected successfully");

    char buf[100];
    ssize_t bytes = recv(socket_fd, buf, 100, 0);
    buf[bytes]=0;

    std::cout << "Please enter a string" << std::endl;

    //Fixme: Possible stack smashing.
    std::cin >> buf;
    send(socket_fd, buf, strlen(buf), 0);

    shutdown(socket_fd, SHUT_RDWR);
    close(socket_fd);
    
    return 0;

}