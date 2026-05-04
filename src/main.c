#include <stdio.h>

/**
 * V.E.N.D.E.T.T.A. 
 * Various ENcoding DEtector Through Traffic Analysis
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <packet_file>\n", argv[0]);
        return 1;
    }

    printf("Test.\n");

    return 0;
}