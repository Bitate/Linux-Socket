#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#include<sys/epoll.h>
#include<stdlib.h>

#define EPOLL_REVS_SIZE 64

static void Usage(const char* proc)
{
    printf("Usage : %s, [local ip], [local port]\n", proc);
}

int startup(char *ip, int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock <0 )
    {
        perror("sock");
        exit(2);
    }
    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,  &opt, sizeof(opt));

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = inet_addr(ip);

    if (bind(sock, (struct sockaddr*)&local, sizeof(local))<0)
    {
        perror("bind");
        exit(3);
    }

    if (listen(sock, 10) < 0)
    {
        perror("listen");
        exit(4);
    }
    return sock;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        return 1;
    }

    int listen_sock = startup(argv[1],atoi(argv[2]));

    int epfd = epoll_create(256);
    if (epfd < 0)
    {
        perror("epoll create!\n");
        return 5;
    }

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = listen_sock;
    epoll_ctl(epfd, EPOLL_CTL_ADD, listen_sock, &ev );

    int nums = -1;
    struct epoll_event revs[EPOLL_REVS_SIZE];
    int timeout =-1;
    while (1)
    {
    switch ( (nums = epoll_wait(epfd,revs, EPOLL_REVS_SIZE, timeout )))

        {
            case 0:
               printf("time out ...\n");
               break;

            case -1:
               perror("epoll wait\n");
               break;
            default:
               {
                    int i =0;
                    for (;i< nums; i++)
                    {
                        // arrived socket fd
                        int sock = revs[i].data.fd;
                        if (sock == listen_sock && (revs[i].events & EPOLLIN))
                        {
                            struct sockaddr_in client;
                            socklen_t len = sizeof(client);

                            int new_sock = accept(listen_sock, (struct sockaddr*)&client, &len);
                            if(new_sock < 0)
                            {
                                perror("accept !\n");
                                continue;
                            }

                            printf(" get client :[%s] [%d]\n", inet_ntoa(client.sin_addr),htons(client.sin_port));
                            ev.events = EPOLLIN;
                            ev.data.fd = new_sock;
                            epoll_ctl(epfd, EPOLL_CTL_ADD, new_sock, &ev);


                        }
                        else if(sock != listen_sock)
                        {
                            if (revs[i].events & EPOLLIN)
                            {
                                char *buf[10240];
                                ssize_t s = read(sock, buf, sizeof(buf)-1);
                                if (s >0 )
                                {
                                    printf("client : %s\n", buf);
                                    ev.events = EPOLLOUT;
                                    ev.data.fd = sock;
                                    epoll_ctl(epfd, EPOLL_CTL_MOD, sock, &ev);
                                }
                                else if (s == 0)
                                {
                                    printf("client quit\n");
                                    close(sock);
                                    epoll_ctl(epfd, EPOLL_CTL_DEL, sock, NULL);
                                }
                                else{
                                    perror("read");
                                    close(sock);
                                    epoll_ctl(epfd, EPOLL_CTL_DEL, sock, NULL);
                                }
                            }

                            else if (revs[i]. events & EPOLLOUT)
                            {
                                const char *msg = "HTTP/1.0  OK 200 \r\n\r\n<html><h1>WX    EPOLL  </h1></html>";
                                 write(sock,msg, strlen(msg));
                                close(sock);
                                epoll_ctl(epfd, EPOLL_CTL_DEL,sock,NULL);

                            }
                            else
                            {}
                        }
                    }
               }
               break;

        }

    }
    return 0;
}
