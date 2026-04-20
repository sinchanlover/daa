#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

struct sockaddr_in serv_addr, cli_addr;

int listenfd, connfd, r, w, cli_addr_len;

unsigned short serv_port = 25020;
char serv_ip[] = "127.0.0.1";

char buff[128];

int main()
{
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serv_port);
    inet_aton(serv_ip, (&serv_addr.sin_addr));

    printf("\nTCP CALCULATOR SERVER.\n");

    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\nSERVER ERROR: Cannot create socket.\n");
        exit(1);
    }

    if((bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0)
    {
        printf("\nSERVER ERROR: Cannot bind.\n");
        close(listenfd);
        exit(1);
    }

    if((listen(listenfd, 5)) < 0)
    {
        printf("\nSERVER ERROR: Cannot listen.\n");
        close(listenfd);
        exit(1);
    }

    cli_addr_len = sizeof(cli_addr);

    for( ; ; )
    {
        printf("\nSERVER: Listening...\n");

        connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &cli_addr_len);

        if(connfd < 0)
        {
            printf("\nSERVER ERROR: Cannot accept.\n");
            continue;
        }

        printf("\nConnected from %s\n", inet_ntoa(cli_addr.sin_addr));

        if((r = read(connfd, buff, 128)) > 0)
        {
            buff[r] = '\0';

            int a, b, result;
            char op;

            sscanf(buff, "%d %c %d", &a, &op, &b);

            switch(op)
            {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if(b != 0) result = a / b;
                    else
                    {
                        sprintf(buff, "Error: Division by zero");
                        write(connfd, buff, strlen(buff));
                        close(connfd);
                        continue;
                    }
                    break;
                default:
                    sprintf(buff, "Invalid operator");
                    write(connfd, buff, strlen(buff));
                    close(connfd);
                    continue;
            }

            sprintf(buff, "%d", result);

            write(connfd, buff, strlen(buff));

            printf("Computed: %d %c %d = %d\n", a, op, b, result);
        }

        close(connfd);
    }
}
