#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

struct sockaddr_in serv_addr;

int skfd, r, w;

unsigned short serv_port = 25020;
char serv_ip[] = "127.0.0.1";

char rbuff[128];
char sbuff[128];

int main()
{
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serv_port);
    inet_aton(serv_ip, (&serv_addr.sin_addr));

    printf("\nTCP CALCULATOR CLIENT.\n");

    if((skfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\nCLIENT ERROR: Cannot create socket.\n");
        exit(1);
    }

    if((connect(skfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0)
    {
        printf("\nCLIENT ERROR: Cannot connect to server.\n");
        close(skfd);
        exit(1);
    }

    printf("\nConnected to server.\n");

    printf("Enter expression (e.g., 10 + 5): ");
    fgets(sbuff, sizeof(sbuff), stdin);

    if((w = write(skfd, sbuff, strlen(sbuff))) < 0)
    {
        printf("\nCLIENT ERROR: Cannot send.\n");
        close(skfd);
        exit(1);
    }

    if((r = read(skfd, rbuff, sizeof(rbuff))) > 0)
    {
        rbuff[r] = '\0';
        printf("Result: %s\n", rbuff);
    }
    else
    {
        printf("\nCLIENT ERROR: Cannot receive.\n");
    }

    close(skfd);
    return 0;
}
