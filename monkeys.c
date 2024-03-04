#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

char random_char() {
    static int r = 0;
    static int bits = 0;
    if (bits == 0) {
        r = rand();
        bits = RAND_MAX;
    }
    char c = (r % 27) + 'a' - 1;
    r /= 27;
    bits /= 27;
    return c == '`' ? ' ' : c;
}

int parse_time(char *time_arg) {
    int len = strlen(time_arg);
    char unit = time_arg[len - 1];
    time_arg[len - 1] = '\0';
    int value = atoi(time_arg);
    switch (unit) { 
        case 's': return value;
        case 'm': return value * 60;
        case 'h': return value * 3600;
        case 'd': return value * 86400;
        case 'y': return value * 31536000;
        default: return -1;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) { 
        printf("Usage: monkeys <number of monkeys> <time to run>\n");
        return 1;
    }
    int n = atoi(argv[1]);
    int t = parse_time(argv[2]);
    if (n <= 0 || t <= 0) { 
        printf("Invalid arguments\n");
        return 1;
    }
    srand(time(NULL)); 
    FILE *files[n]; 
    char filenames[n][20]; 
    char last_chars[n]; 
    char buffers[n][BUFFER_SIZE];
    int buffer_counts[n];
    memset(buffer_counts, 0, sizeof(buffer_counts));
    for (int i = 0; i < n; i++) { 
        sprintf(filenames[i], "monkey%d.txt", i + 1); 
        files[i] = fopen(filenames[i], "w"); 
        if (files[i] == NULL) { 
            printf("Error opening file %s\n", filenames[i]);
            return 1;
        }
        last_chars[i] = '\0';
    }
    struct timespec start, current;
    clock_gettime(CLOCK_MONOTONIC, &start);
    while (1) { 
        for (int i = 0; i < n; i++) { 
            char c = random_char(); 
            buffers[i][buffer_counts[i]++] = c;
            if (buffer_counts[i] == BUFFER_SIZE) {
                fwrite(buffers[i], 1, BUFFER_SIZE, files[i]);
                buffer_counts[i] = 0;
            }
            last_chars[i] = c; 
        }
        clock_gettime(CLOCK_MONOTONIC, &current);
        double elapsed = current.tv_sec - start.tv_sec;
        elapsed += (current.tv_nsec - start.tv_nsec) / 1000000000.0;
        if (elapsed >= t) break;
        printf("\r");
        for (int i = 0; i < n; i++) {
            printf("Monkey %d: %c | ", i + 1, last_chars[i]);
        }
        printf("Time elapsed: %.9f seconds", elapsed);
        fflush(stdout);
    }
    printf("\n");
    for (int i = 0; i < n; i++) { 
        fwrite(buffers[i], 1, buffer_counts[i], files[i]);
        fclose(files[i]); 
    }
    return 0;
}
