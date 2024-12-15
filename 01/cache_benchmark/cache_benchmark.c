#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define ARRAY_SIZE (1024 * 1024 * 64)  // 64 MB of integers
#define CACHE_LINE 64                   // 64 bytes = 16 integers

// Cache-friendly: Sequential access
uint64_t sequential_sum(int* arr, size_t size) {
    uint64_t sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// Cache-unfriendly: Random access
uint64_t random_sum(int* arr, size_t size) {
    uint64_t sum = 0;
    // Pre-generate random indices
    size_t* indices = (size_t*)malloc(size * sizeof(size_t));
    for (size_t i = 0; i < size; i++) {
        indices[i] = i;
    }
    // Fisher-Yates shuffle
    for (size_t i = size - 1; i > 0; i--) {
        size_t j = rand() % (i + 1);
        size_t temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }
    
    // Sum using random access pattern
    for (size_t i = 0; i < size; i++) {
        sum += arr[indices[i]];
    }
    
    free(indices);
    return sum;
}

// Cache-block aware: Process in blocks
uint64_t block_sum(int* arr, size_t size) {
    uint64_t sum = 0;
    size_t block_size = CACHE_LINE / sizeof(int);
    
    for (size_t block = 0; block < size; block += block_size) {
        size_t end = (block + block_size < size) ? block + block_size : size;
        for (size_t i = block; i < end; i++) {
            sum += arr[i];
        }
    }
    return sum;
}

int main() {
    srand(time(NULL));
    
    // Allocate and initialize array
    int* array = (int*)malloc(ARRAY_SIZE * sizeof(int));
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 100;
    }
    
    // Warm up the cache
    volatile uint64_t warmup = sequential_sum(array, 1000);
    
    clock_t start, end;
    uint64_t sum;
    double time_taken;
    
    // Test 1: Sequential access
    start = clock();
    sum = sequential_sum(array, ARRAY_SIZE);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Sequential Sum: %lu\nElements processed: %d\nTime: %.3f seconds\nElements/second: %.2f million\n\n", 
           sum, ARRAY_SIZE, time_taken, (ARRAY_SIZE / time_taken) / 1000000.0);
    
    // Test 2: Random access (true cache-unfriendly)
    start = clock();
    sum = random_sum(array, ARRAY_SIZE);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Random Sum: %lu\nElements processed: %d\nTime: %.3f seconds\nElements/second: %.2f million\n\n", 
           sum, ARRAY_SIZE, time_taken, (ARRAY_SIZE / time_taken) / 1000000.0);
    
    // Test 3: Block access
    start = clock();
    sum = block_sum(array, ARRAY_SIZE);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Block Sum: %lu\nElements processed: %d\nTime: %.3f seconds\nElements/second: %.2f million\n\n", 
           sum, ARRAY_SIZE, time_taken, (ARRAY_SIZE / time_taken) / 1000000.0);
    
    free(array);
    return 0;
}
