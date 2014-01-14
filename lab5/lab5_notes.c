
// Implicit List: first find
p = heap_start;
while ( (p < end) &&
        ((*p & 1) ||
         (*p <= len)))
    p = p + (*p & -2);  // *p & -2 = size of block

// Implicit List: free - coalesce (join) with next block
void free_block(ptr p) {
    *p = *p & -2;
    next = p + *p;
    if ((*next & 1) == 0)
        *p = *p + *next;
}


