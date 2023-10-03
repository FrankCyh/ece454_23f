
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void display_v(int a[], int n);

int func1(int a, int b);

int main(void) {
    int i, j;
    int t1[100], t2[100], t3[10000];
    long sum = 0;
    int k, x;
    int *ptr;

    // Timing variables
    double time_taken;
    clock_t start_t, end_t;


    printf("\nInside main()\n");

    /* Vector elements initialization */
    for (j = 0; j < 100; j++) {
        t1[j] = j;
        t2[j] = j;
    }

    display_v(t1, 100);
    display_v(t2, 100);

    /* Vector elements process, start the clock */


    /* Code1 */
    for (j = 0; j < 100; j++)
        for (i = 0; i < 100; i++) {
            t1[i] = t1[i] + t2[j];
        }
    /* end of Code1 */


    /* Code1-Loop Invariant Code Motion for Vector elements process */


    /* Code2 */
    for (i = 0; i < 100; i++) {
        t1[i] = t1[i] + 1;
    }
    /* end of Code2 */

    /* Code2-Reducing unnecessary statements (mem referencing) */



    /*Code2-Loop Unrolling */


    /*
    display_v(t1, 100);
    display_v(t2, 100);
     */


    /* Code3 */
    for (i = 0; i < 10000; i++) {
        x     = abs(rand());
        t3[i] = func1(i, x);
        sum += t3[i];
    }


    /* Code3-Inlining */



    printf("\n  Sum = %ld  \n", sum);

    /* end of Vector elements process, save the clock */


    /* calculate the time_taken to execute the Vector elements process */


    printf("Process took %f seconds to execute \n", time_taken);

    return 0;
}

void display_v(int a[], int n) {
    int l;
    printf("\n");
    for (l = 0; l < n; l++) printf(" %3d ", a[l]);
    printf("\n");
    return;
}

int func1(int a, int b) { return (a + b / 3); }
