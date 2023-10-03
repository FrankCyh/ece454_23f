#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define optimize

#define ARRAY_SIZE 10000

int main(void) {
    int i, j;
    int t1[ARRAY_SIZE], t2[ARRAY_SIZE];  // increased from 100 to 10000

    // Timing variables
    double time_taken;
    clock_t start_t, end_t;

    /* Vector elements initialization */
    for (j = 0; j < ARRAY_SIZE; j++) {
        t1[j] = j;
        t2[j] = j;
    }

    /* Vector elements process, start the clock */
    start_t = clock();
    printf("Starting of the program, start_t = %ld\n", start_t);

#ifndef optimize
    printf("Not using optimization\n");
    /* Code2 */
    for (i = 0; i < ARRAY_SIZE; i++) {
        t1[i] = t1[i] + 1;
    }
    /* end of Code2 */
#else
    printf("Using optimization\n");
#define UNROLL_FACTOR 4
    /* Loop unrolling  */
    // Unroll by 4
    for (i = 0; i < ARRAY_SIZE - UNROLL_FACTOR; i += UNROLL_FACTOR) {
        t1[i]     = t1[i] + 1;
        t1[i + 1] = t1[i + 1] + 1;
        t1[i + 2] = t1[i + 2] + 1;
        t1[i + 3] = t1[i + 3] + 1;
    }
    for (; i < ARRAY_SIZE; i++) {
        t1[i] = t1[i] + 1;
    }
    /* end of Code2 */
#endif

    end_t = clock();
    printf("End of the program, end_t = %ld\n", end_t);
    printf("Time taken by CPU: %ld\n\n", end_t - start_t);
}