#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* read_shader(const char* filename) {

    char* folder = "shader/";
    char* filepath = malloc(strlen(filename) + strlen(folder) + 1);

    strcpy(filepath, folder);
    strcat(filepath, filename);

    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Get file size
    if (fseek(file, 0, SEEK_END) != 0) {
        perror("Error seeking to end of file");
        fclose(file);
        return NULL;
    }

    long file_size = ftell(file);
    if (file_size == -1) {
        perror("Error getting file size");
        fclose(file);
        return NULL;
    }

    if (fseek(file, 0, SEEK_SET) != 0) {
        perror("Error seeking to start of file");
        fclose(file);
        return NULL;
    }

    // Allocate buffer
    char *buffer = malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }

    // Read content
    size_t bytes_read = fread(buffer, 1, file_size, file);
    if (bytes_read != file_size) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return NULL;
    }

    // Null-terminate
    buffer[file_size] = '\0';

    // Cleanup and return
    fclose(file);
    return buffer;
}
