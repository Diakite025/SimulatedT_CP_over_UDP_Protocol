#include <sys/types.h>  
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "mecanisme.h"


int main(int argc, char *argv[])
{

    int s = socket(AF_INET, SOCK_DGRAM, 0);

    if (s == -1)
    {
        perror("socket error");
    }

    //structure ip_addr_receiver  contient l'adresse ip de la destination
    struct in_addr ip_addr_receiver;   

    int k=inet_pton(AF_INET, "127.0.0.1",&ip_addr_receiver);
    if(k==-1){ perror("error: in ");}

    // structure addr_receiver contient le port où l'app destination va écouter et son addresse ip
    struct sockaddr_in addr_receiver;

    addr_receiver.sin_family = AF_INET;
    addr_receiver.sin_port = htons(6666); // l'app destination va écouter sur le port 6666
    addr_receiver.sin_addr = ip_addr_receiver; 

    
    // associer le socket s à un port et un ip contenu dans addr_receiver
    bind(s, (struct sockaddr *)&addr_receiver, sizeof(addr_receiver));

    //on recupére le port et l'ip de l'application source
    struct sockaddr_in addr_sender; 
    
    socklen_t size_sender; 

    // crée un segment pour stocker le segment envoyé par la source
    segment_udp segment;

    // on recupére le segment envoyé par la source via le primitive recvfrom
    recvfrom(s,&segment,sizeof(segment),0,(struct sockaddr *)&addr_sender, &size_sender);
    
    
    printf("%s\n",segment.data);

    

    // affichage de l'addresse ip de l'ip de la source  en décimal pointé

    char *ip_addr_sender = malloc(INET_ADDRSTRLEN);

    inet_ntop(AF_INET, &(addr_sender), ip_addr_sender, INET_ADDRSTRLEN);

    printf("l'adresse ip de l'application est :%s\n", ip_addr_sender);

    // affichage du port
    printf("le port de l'aplication client : %d\n", addr_sender.sin_port);

    close(s);

}