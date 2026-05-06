#include <stdio.h>
#include <string.h>

/**
 * VENDETTA
 * Various ENcoding DEtector Through Traffic Analysis
 */
int main(int argc, char *argv[]) {
    const char *filename;
    FILE *input_file;

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

    /* Ensure that the file can be opened. */
    input_file = fopen(filename, "r");
    if (!input_file) {
        perror("Error opening file");
        return 1;
    }

    printf("Test.\n");
    fclose(input_file);

    return 0;
}