#include "packet.h"

#include <stdio.h>
#include <stdlib.h>

struct packet_array *read_packet_file(const char *filename){
    FILE *input_file = fopen(filename, "r");
    
    if (!input_file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fclose(input_file);

    /* TODO: Actually read the file contents and return a proper pointer. */
    return NULL;
}

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