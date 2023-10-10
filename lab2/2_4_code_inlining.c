#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define optimize

#define ARRAY_SIZE 10000

int func1(int a, int b) { return (a + b / 3); }

int main(void) {
    int i, x, sum;
    int t3[ARRAY_SIZE];  // increased from 100 to 10000

    // Timing variables
    double time_taken;
    clock_t start_t, end_t;

    /* Vector elements process, start the clock */
    start_t = clock();
    printf("Starting of the program, start_t = %ld\n", start_t);

#ifndef optimize
    printf("Not using optimization\n");
    /* Code3 */
    for (i = 0; i < 10000; i++) {
        x     = abs(rand());
        t3[i] = func1(i, x);
        sum += t3[i];
    }
    /* end of Code3 */
#else
    printf("Using optimization\n");
#define UNROLL_FACTOR 4
    // Code inlining
    for (i = 0; i < 10000; i++) {
        x     = abs(rand());
        t3[i] = (i + x) / 3;
        sum += t3[i];
    }
    /* end of Code2 */
#endif

    end_t = clock();
    printf("End of the program, end_t = %ld\n", end_t);
    printf("Time taken by CPU: %ld\n\n", end_t - start_t);
}