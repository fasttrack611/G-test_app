// utils.c
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "utils.h"

#include <stdio.h>
#include <sys/time.h>

// Function to simulate work
void do_work() {
    
     printf("\n IN Module.. do_work()  \n");

    for (volatile int i = 0; i < 100000000; ++i); // Simulated delay
   sleep(4);						  // 
}


void measure_execution_time(void (*func)(), const char* label) {
    struct timeval start, end;

    printf("\n Module.. measure_execution_time \n");

    gettimeofday(&start, NULL);
    func();
    gettimeofday(&end, NULL);

    double duration = (end.tv_sec - start.tv_sec) +
                      (end.tv_usec - start.tv_usec) / 1e6;

    printf("[TIMER] %s took %.6f seconds to execute.\n", label, duration);
}


#if 0 
// Function to measure execution time of another function
void measure_execution_time(void (*func)(), const char* label) {
    clock_t start = clock();

    printf("\n Module.. measure_execution_time \n");
    func();  // Call the function

    clock_t end = clock();
    double duration = (double)(end - start) / CLOCKS_PER_SEC;

    printf("[TIMER] %s took %.6f seconds to execute.\n", label, duration);
}
#endif 
