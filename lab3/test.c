#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    void *c_break = sbrk(0x1000);

    printf("1 - %p \n", c_break);
    c_break = sbrk(0);
    printf("2 - %p \n", c_break);
    c_break = sbrk(0);
    printf("3 - %p \n", c_break);
}
/* Output:
 * 1 - 0x55f184dbd000
 * 2 - 0x55f184dde000
 * 3 - 0x55f184dde000
 */