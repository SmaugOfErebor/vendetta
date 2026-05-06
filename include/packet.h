#ifndef PACKET_H
#define PACKET_H

struct packet {
    char *content;
    int length;
};

struct packet_array {
    struct packet **packets;
    int length;
};

/* struct packet_array *read_packet_file(const char *filename); */

void free_packet(struct packet *p);
void free_packet_array(struct packet_array *pa);

#endif