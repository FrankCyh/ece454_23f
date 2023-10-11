
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Heap_Size 10000
char h_mem[Heap_Size] = {0};
void *h_mem_start;
void *h_mem_end;
void *c_break;

void *m_sbrk(int incr);

int main(void) {
    struct h_Node {
        int STATUS; // defines the status of the block: 0 if it is free and 1 if it is blocked 
        size_t SIZE; // defines the size of the block in bytes 
        void *c_blk; // defines the starting address of the current block
        void *n_blk; // defines the starting address of the next block
        struct h_Node *NEXT; // points to the next h_Node containing the data for the next block linked to this one
    };

    h_mem_start = (char *)h_mem;
    h_mem_end   = (char *)h_mem + (Heap_Size - 1);
    c_break     = (void *)&h_mem;

    printf("\n h_mem= %p          c_break = %p", h_mem, c_break);
    printf("\n h_mem_start = %p   h_mem_end = %p", h_mem_start, h_mem_end);


    m_sbrk(0);
    printf("\n 1- h_mem_start=%p   c_break=%p   h_mem_end=%p", h_mem_start, c_break, h_mem_end);
    m_sbrk(+5);
    printf("\n 2- h_mem_start=%p   c_break=%p   h_mem_end=%p", h_mem_start, c_break, h_mem_end);
    m_sbrk(+100);
    printf("\n 3- h_mem_start=%p   c_break=%p   h_mem_end=%p\n", h_mem_start, c_break, h_mem_end);

    return (0);
}

void *m_sbrk(int incr) {
    if (incr == 0) {
        return c_break;
    }
    if (incr < (char *)h_mem_start - (char *)c_break) {
        printf("Memory Underflow: No memory address prior to heap_start");
        return (void *)-1;
    }
    if (incr > (char *)h_mem_end - (char *)c_break) {
        printf("Memory Overflow: No memory address after heap_end");
        return (void *)-1;
    }

    c_break = (void *)((char *)c_break + incr);
    return c_break;
}
