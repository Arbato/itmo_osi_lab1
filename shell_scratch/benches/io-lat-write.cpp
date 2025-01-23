#include <iostream>
#include <cstdlib>
#include <climits>
#include <cstdio>





#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <sys/time.h>
#include <cstdio>

#define BLOCK_SIZE 4096  // Define block size for I/O latency test

using namespace std;

/**
 * Allocates a buffer of BLOCK_SIZE bytes.
 */
char* allocBuffer() {
    char* buf = new char[BLOCK_SIZE];
    if (!buf) {
        cerr << "Error: Memory allocation failed." << endl;
        exit(EXIT_FAILURE);
    }
    return buf;
}

/**
 * Measures the I/O write latency by writing BLOCK_SIZE chunks to a file.
 */
void ioLatencyWrite(const string& filename, long repetitions) {
    FILE* file = fopen(filename.c_str(), "wb");
    if (!file) {
        cerr << "Error: Cannot open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    char* buf = allocBuffer();

    for (long i = 0; i < repetitions; ++i) {
        setvbuf(file, NULL, _IONBF, 0);  // Disable buffering

        struct timeval start, stop;
        gettimeofday(&start, NULL);

        size_t written = fwrite(buf, sizeof(char), BLOCK_SIZE, file);

        gettimeofday(&stop, NULL);

        if (written != BLOCK_SIZE) {
            cerr << "Error: Writing to file failed." << endl;
            fclose(file);
            delete[] buf;
            exit(EXIT_FAILURE);
        }

        double elapsedTime = (stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_usec - start.tv_usec);
        cout << "Iteration " << i + 1 << ": Write latency = " << elapsedTime << " microseconds" << endl;
    }

    fclose(file);
    delete[] buf;
}

/**
 * Main function to execute the I/O latency write benchmark.
 */
size_t io_lat_write(string filename) {
    FILE* file = fopen(filename.c_str(), "wb");
    if (!file) {
        cerr << "Error: Cannot open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    char* buf = allocBuffer();

    setvbuf(file, NULL, _IONBF, 0);  // Disable buffering

    struct timeval start, stop;
    gettimeofday(&start, NULL);

    size_t written = fwrite(buf, sizeof(char), BLOCK_SIZE, file);

    gettimeofday(&stop, NULL);

    if (written != BLOCK_SIZE) {
        cerr << "Error: Writing to file failed." << endl;
        fclose(file);
        delete[] buf;
        exit(EXIT_FAILURE);
    }

    fclose(file);
    delete[] buf;
    return 1;
}

 

