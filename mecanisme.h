#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef  struct segment {
    unsigned int id_flux :8;
    unsigned int type :8;
    unsigned int num_sequence:16;
    unsigned int num_ack:16;
    unsigned int ecn:8;
    unsigned int window:8;
    char data[44];

} segment_udp;

void ajout_data_to_segment(segment_udp * segment, char* message );
