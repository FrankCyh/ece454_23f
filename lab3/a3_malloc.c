
int m_init(void) {
    /* This method should be called to initialize the heap area in your program, before calling any other methods.
     * It returns 0 for a successful initializing of the Heap and returns not 0 in case of any problems.
     * Use this method to make an initial size for the Heap segment. All memory allocation for dynamic usage should be done within this part.
     */
    return 0;
}

void* m_malloc(size_t size) {
    /* This method returns a pointer to the allocated block in the Heap with size bytes (at least). This is an entire separated block within the Heap and should not have any overlap with the other allocated blocks.
     * The method should search to find the best fit in the Heap for that given size and allocate it. In this process the memory has already been divided into various size of blocks. To manage these blocks a mechanism is provided at section 3.1.3 using a linked-list. Each node in this linked-list, naming h_Node, is connected to a block in the Heap and contains its information. Thus for tracking the information about each block, its relevant h_Node should be checked.
     */
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
}

void h_layout(struct h_Node* ptr) {
    /* display the layout of the Heap after each modification */
    return;
}

int m_check(void) {
    /* check if the next and/or previous blocks are free to join them with the current block, after a free method called for the current block (the Coalescing concept).
     * It returns 0 for a successful consistency checking of the Heap, and returns -1 (or none zero) in case of any problems
     */
    return 0;
}