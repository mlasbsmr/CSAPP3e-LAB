/*
 * echoclient.c - An echo client
 */
/* $begin echoclientmain */
#include "csapp.h"

int main(int argc, char **argv) 
{
    int clientfd;
    char *host, *port, buf[MAXLINE];
    rio_t rio;
int i;
    if (argc != 3) {
	fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
	exit(0);
    }
    host = argv[1];
    port = argv[2];

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);
    if(Fgets(buf, MAXLINE, stdin) != NULL)
        Rio_writen(clientfd, buf, strlen(buf));

    while ((i=Rio_readlineb(&rio, buf, MAXLINE))!=0){
        //printf("clients recieved %d bytes\n",i);
	    Fputs(buf, stdout);
    }

    Close(clientfd); //line:netp:echoclient:close
    exit(0);
}
/* $end echoclientmain */
