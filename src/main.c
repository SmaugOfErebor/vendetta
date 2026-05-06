#include <stdio.h>
#include <string.h>

#include "packet.h"

/**
 * VENDETTA
 * Various ENcoding DEtector Through Traffic Analysis
 */
int main(int argc, char *argv[]) {
    const char *filename;
    struct packet_array *pa;
    
    /* Verify argument presence. */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file.hex|.txt>\n", argv[0]);
        return 1;
    }

    /* Verify input file extension. */
    filename = argv[1];
    if (!strstr(filename, ".hex") && !strstr(filename, ".txt")) {
        fprintf(stderr, "Error: Input file must be a .hex or .txt file.\n");
        return 1;
    }

    pa = read_packet_file(filename);
    /* TODO: Actually use the packet array to brute force determine the CRC input/output/algorithm. */
    free_packet_array(pa);

    printf("Test.\n");
    
    return 0;
}