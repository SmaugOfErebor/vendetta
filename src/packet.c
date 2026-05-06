#include "packet.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 2048

typedef enum {
    PACKET_OK = 0,
    PACKET_OVERFLOW = -1,
    PACKET_EMPTY = -2
} packet_status;

static packet_status get_packet_length(const char * const buffer, int * const out_length) {
    char* endline_pos = strchr(buffer, '\n');

    if (endline_pos) {
        *out_length = endline_pos - buffer;
    } else {
        endline_pos = strchr(buffer, '\0');
        *out_length = endline_pos - buffer;

        if (*out_length == BUFFER_SIZE - 1) return PACKET_OVERFLOW;
    }

    if (*out_length == 0) return PACKET_EMPTY;
    return PACKET_OK;
}

static void get_packet_content(const char * const buffer, struct packet * const p) {
    p->content = malloc(p->length);
    memcpy(p->content, buffer, p->length);
}

static void clean_and_exit(FILE *f, struct packet *p, struct packet_array *pa, const char *msg) {
    fputs(msg, stderr);
    fclose(f);
    if (p) free(p);
    free(pa);
    exit(EXIT_FAILURE);
}

struct packet_array *read_packet_file(const char * const filename){
    FILE *input_file = fopen(filename, "r");
    struct packet_array *pa = malloc(sizeof(struct packet_array));
    struct packet *p;
    char buffer[BUFFER_SIZE];
    int pa_size = 8;
    
    if (!input_file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    pa->length = 0;
    pa->packets = malloc(pa_size* sizeof(struct packet *));

    while (fgets(buffer, sizeof(buffer), input_file)) {
        p = malloc(sizeof(struct packet));
        
        switch (get_packet_length(buffer, &(p->length))) {
            case PACKET_OK:
                get_packet_content(buffer, p);
                break;

            case PACKET_OVERFLOW:
                clean_and_exit(input_file, p, pa, "Packet contents exceeded the maximum size.\n");
                break;

            case PACKET_EMPTY:
                clean_and_exit(input_file, p, pa, "Input file contains empty line.\n");
                break;
        }

        pa->length++;
        if (pa->length > pa_size) {
            pa_size *= 2;
            pa->packets = realloc(pa->packets, pa_size * sizeof(struct packet *));
        }

        pa->packets[pa->length - 1] = p;
    }

    if (pa->length == 0) {
        clean_and_exit(input_file, NULL, pa, "Input file contains no packets.\n");
    }

    if (pa_size != pa->length) {
        pa->packets = realloc(pa->packets, pa->length  * sizeof(struct packet *));
    }

    fclose(input_file);
    return pa;
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