#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include "mecanisme.h"
#include <string.h>
int main(int argc, char *argv[])
{

    int s = socket(AF_INET, SOCK_DGRAM, 0);

    if (s == -1)
    {
        perror("socket error");
    }

    // on créee une structure qui va contenir le port d'écoute de l'application source
    struct sockaddr_in local_adrr_source;

    local_adrr_source.sin_family = AF_INET;
    local_adrr_source.sin_port = htons(3333); // port d'écoute de l'app sources : 3333

    bind(s, (struct sockaddr *)&local_adrr_source, sizeof(local_adrr_source));

    // on créee une structure qui va contenir le port d'écoute de l'application destination
    struct sockaddr_in local_addr_dest;

    local_addr_dest.sin_family = AF_INET;
    local_addr_dest.sin_port = htons(6666);                     // le port d'écoute de l'app destination :6666
    inet_pton(AF_INET, "127.0.0.1", &local_addr_dest.sin_addr); // addresse ip de l'app destination est 127.0.0.1

    segment_udp segment; // 1er segment à envoyer

    strcpy(segment.data, "hello"); // ajout de données à envoyer dans le segment

    sendto(s, &segment, sizeof(segment), 0, (struct sockaddr *)&local_addr_dest, sizeof(local_addr_dest));

    close(s);
}