#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define optimize

#define ARRAY_SIZE 100000

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
    /* Code1 */
    for (j = 0; j < ARRAY_SIZE; j++)
        for (i = 0; i < ARRAY_SIZE; i++) {
            t1[i] = t1[i] + t2[j];
        }
    /* end of Code1 */
#else
    printf("Using optimization\n");
    /* LICM Optimization  */
    int tmp = 0;
    for (j = 0; j < ARRAY_SIZE; j++) {
        tmp = t2[j];
        for (i = 0; i < ARRAY_SIZE; i++) {
            t1[i] = t1[i] + tmp;
        }
    }
    /* end of Code1 */
#endif

    end_t = clock();
    printf("End of the program, end_t = %ld\n", end_t);
    printf("Time taken by CPU: %ld\n\n", end_t - start_t);
}