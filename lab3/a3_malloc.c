#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FREE 0
#define BLOCKED 1

#define HEAPSIZE 10000
char h_mem[HEAPSIZE] = {0};

struct h_Node{
    int STATUS;                 // defines the status of the block: 0 ifit is free and 1 if it is blocked 
    size_t SIZE;                // defines the size of the block in bytes
    void   *c_blk;              // defines the starting address of the current block
    void   *n_blk;              // defines the starting address of the next block
    struct h_Node * NEXT;       // points to the next h_Node containing the data for the next block linked to this one 
};

struct h_List{
    void *start;
    void *end;
    struct h_Node *head;
};

struct h_List *Heap;

int m_init(void) {
    /* This method should be called to initialize the heap area in your program, before calling any other methods.
     * It returns 0 for a successful initializing of the Heap and returns not 0 in case of any problems.
     * Use this method to make an initial size for the Heap segment. All memory allocation for dynamic usage should be done within this part.
     */
    Heap = sbrk(sizeof(struct h_List));                 // Allocate the Linked List
    printf("Here is the Linked List address: %p\n", Heap);
    Heap->start = (char*)h_mem;                         // Populate the start address field in the linked list. (start address of the heap)
    printf("Heap start address is: %p\n", Heap->start);
    Heap->end = (char*)(h_mem + (HEAPSIZE-1));          // Populate the end address field in the linked list. (end address of the heap)
    printf("Heap last address is: %p\n", Heap->end);
    Heap->head = sbrk(sizeof(struct h_Node));           // Allocate head of the "header" linked list. At the beginning, there is just one header.
    struct h_Node * head = Heap->head;                  
    printf("Here is the head node address: %p\n", head);
    head->STATUS = FREE;                                // Initialise status to free.
    head->c_blk = (char *)h_mem;                        // Initialise c_blk with start address of the heap.
    head->n_blk = NULL;                                 // If n_blk is NULL, it means that this block's last address is the same as the Heap's end address. This is the last header block
    head->NEXT = NULL;                                  // No next "header" block
    head->SIZE = 10000;                                 // Size of heap is 10,000 bytes.

    return 0;
}

// Linked List helper functions.
struct h_Node * find_header_block(void* address, struct h_Node * head){
    struct h_Node* temp = head;
    while(temp!=NULL){
        if(temp->c_blk == address){
            break;
        }
        temp = temp->NEXT;
    }
    return temp;
}

void* m_malloc(size_t size) {
    /* This method returns a pointer to the allocated block in the Heap with size bytes (at least). This is an entire separated block within the Heap and should not have any overlap with the other allocated blocks.
     * The method should search to find the best fit in the Heap for that given size and allocate it. In this process the memory has already been divided into various size of blocks. To manage these blocks a mechanism is provided at section 3.1.3 using a linked-list. Each node in this linked-list, naming h_Node, is connected to a block in the Heap and contains its information. Thus for tracking the information about each block, its relevant h_Node should be checked.
     */
    int foundBlock = 0;
    int bestFit = HEAPSIZE+1;
    struct h_Node * allocBlock = NULL;
    struct h_Node * allocBlockPrev = NULL;
    struct h_Node * temp = Heap->head;
    struct h_Node * prev = NULL;
    while(temp != NULL){
        if(temp->STATUS == FREE){
            int blockSize;
            if(temp->n_blk != NULL){
                blockSize = temp->n_blk - temp->c_blk;
            }
            else{
                blockSize = Heap->end - temp->c_blk + 1;
            }
            if(blockSize >= size){
                foundBlock = 1;
                if(blockSize < bestFit){
                    bestFit = blockSize;
                    allocBlock = temp;
                    allocBlockPrev = prev;
                }
            }
        }
        prev = temp;
        temp = temp->NEXT;
    }
    if(foundBlock == 1){
        // allocate new header block using sbrk(sizeof(struct h_Node));
        // adjust next pointers of the blocks.
        // adjust c_blk and n_blk
        // return c_blk of new blk
        printf("Found a block of size %d\n", bestFit);
        struct h_Node * newBlock = sbrk(sizeof(struct h_Node));
        newBlock->STATUS = BLOCKED;
        newBlock->SIZE = size;
        newBlock->NEXT = allocBlock;
        if(allocBlockPrev != NULL)
            allocBlockPrev->NEXT = newBlock;
        else
            Heap->head=newBlock;
        newBlock->c_blk = (char*)allocBlock->c_blk;
        newBlock->n_blk = allocBlock->c_blk + size;
        allocBlock->c_blk = newBlock->n_blk;
        allocBlock->SIZE -=size;
        printf("Created new header in malloc\n");
        return newBlock->c_blk;
    }
    else{
        // couldn't find a space on the heap.
        printf("Couldn't find a block of size %d\n", size);
        return NULL;
    }
    
}

void m_free(void* ptr) {
    /*
     * This method returns the allocated block pointed to by ptr to the free space of the Heap.
     * This method should work if and only if the ptr is valid,
     * meaning that the `m_free(ptr)` should be called following a call to `m_malloc()` or `m_realloc()` that already generated its ptr parameter.
     * Like the real `free()` method, the `m_fee()` should set the allocated block as a free block now, and this should be done by modifying the information in the relevant h_Node of that block.Moreover, it should also check if the previous and / or next blocks are free or not, and if yes, join them to the current free block to make a bigger free block and finally update all the relevant `h_Nodes`.
     */
}
void* m_realloc(void* ptr, size_t size) {
    /* This method returns a pointer to the new allocated block in the Heap with size bytes (at least) after resizing an old block pointed to by ptr. This is an entire separated block within the Heap and should not have any
     * overlap with the other allocated blocks.
     * This method changes the size of the old block pointed to by ptr. The address of the new ptr could be the same as the old ptr or be different. Note that the content of the common parts between the old and the new blocks should be the same. For example if the old block has the size=200 bytes and the new block has the size=250 bytes, this means that the first 200 bytes of both blocks are the same (actually the old block will be replaced by the new one, but the contents should be kept for the common size).
     */
    m_free(ptr);
    return m_malloc(size);
}

void h_layout(struct h_Node* head) {
    /* display the layout of the Heap after each modification */
    struct h_Node* temp = head;
    int block_num = 0;
    while(temp!=NULL){
        block_num++;
        printf("BLOCK %d\n",block_num);
        if(temp->STATUS == 1)
            printf("Block Status: Blocked\n");
        else
            printf("Block Status: Free\n");

        printf("Block Size: %ld\n", temp->SIZE);
        printf("Block Start Address: %p\n", (char*)temp->c_blk);

        temp = temp->NEXT;
    }
    return;
}

int m_check(void) {
    /* check if the next and/or previous blocks are free to join them with the current block, after a free method called for the current block (the Coalescing concept).
     * It returns 0 for a successful consistency checking of the Heap, and returns -1 (or none zero) in case of any problems
     */
    
    return 0;
}

int main(){
    int return_val = m_init();
    printf ("\nPrinting Original Heap Layout\n\n");
    h_layout(Heap->head);
    char  *pt1 = m_malloc(2000);
    printf ("\nPrinting Heap Layout after first malloc\n\n");
    h_layout(Heap->head);       
    char  *pt2 = m_malloc(500);
    printf ("\nPrinting Heap Layout after second malloc\n\n");
    h_layout(Heap->head);
    char  *pt3 = m_malloc(300);
    printf ("\nPrinting Heap Layout after third malloc\n\n");
    h_layout(Heap->head);
    // m_free(pt2);
    // h_layout(Heap->head);
    char  *pt4 = m_malloc(1500);
    printf ("\nPrinting Heap Layout after fourth malloc\n\n");
    h_layout(Heap->head);
    char  *pt5 = m_malloc(1500);
    printf ("\nPrinting Heap Layout after fourth malloc\n\n");
    h_layout(Heap->head);
    char  *pt6 = m_malloc(1500);
    printf ("\nPrinting Heap Layout after fourth malloc\n\n");
    h_layout(Heap->head);
    char  *pt7 = m_malloc(1500);
    printf ("\nPrinting Heap Layout after fourth malloc\n\n");
    h_layout(Heap->head);
    char  *pt8 = m_malloc(1500);
    printf ("\nPrinting Heap Layout after fourth malloc\n\n");
    h_layout(Heap->head);
    char  *pt9 = m_malloc(150);
    printf ("\nPrinting Heap Layout after fourth malloc\n\n");
    h_layout(Heap->head);
    char  *pt10 = m_malloc(01);
    printf ("\nPrinting Heap Layout after fourth malloc\n\n");
    h_layout(Heap->head);
}