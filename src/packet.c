#include "packet.h"

#include <stdlib.h>

void free_packet(struct packet *p) {
    if (!p) return;
    free(p->content);
    free(p);
}

void free_packet_array(struct packet_array *pa) {
    int i;
    if (!pa) return;
    for (i = 0; i < pa->length; i++) {
        free_packet(pa->packets[i]);
    }
    free(pa->packets);
    free(pa);
}