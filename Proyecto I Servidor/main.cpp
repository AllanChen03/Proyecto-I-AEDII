#include<stdio.h>
#include<stdlib.h>
#include<sstream>
#include<string>
#include<netdb.h>
#include<netinet/in.h>
#include<string.h>
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

using namespace std;

void doprocessing (int sock, int cliente);
void sendM(int socket,int client);

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno,cliente;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n, pid;
    socklen_t clilen;


    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 8080;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (::bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here
       * process will go in sleep mode and will wait
       * for the incoming connection
    */

    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    cout<<"Servidor Iniciado..."<<endl;

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        cliente=cliente+1;

        if (newsockfd < 0) {
            perror("ERROR aceptando conexion");
            exit(1);
        }

        /* Create child process */
        pid = fork();

        if (pid < 0) {
            perror("ERROR on fork");
            exit(1);
        }

        if (pid == 0) {

            cout<<"Nueva conexion "<<cliente<<endl;
            close(sockfd);
            doprocessing(newsockfd,cliente);
            exit(0);
        }
        else {
            close(newsockfd);
        }

    }
}

void doprocessing (int sock, int cliente1) {
    int n;
    char buffer[256], *msj;
    bzero(buffer,256);
    n = read(sock,buffer,255);
    if (n < 0) {
        perror("ERROR leyendo de socket");
        exit(1);
    }
    cout<<"Mensaje de cliente "<<cliente1<<":"<<buffer<<endl;
    sendM(sock,cliente1);

}

void sendM(int socket, int client){
    char *buff;
    int n;
    cout << "\nServidor: ";
    cin >> buff;
    n=write(socket, buff,strlen(buff));
    doprocessing(socket,client);
    cout<<n<<endl;
    if(n<0){
        cout<<"Error enviando respuesta"<<endl;
    }
    cout<<n<<endl;

}