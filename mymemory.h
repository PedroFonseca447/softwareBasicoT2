#ifndef MYMEMORY_H
#define MYMEMORY_H


typedef struct allocation {
    void *start;
    size_t size;
    struct allocation *next;
} allocation_t;


typedef struct {
    void *pool;
    size_t total_size;
    allocation_t *head;
}   mymemory_t;

//aloca o bloco de memória total e retorna um ponteiro
mymemory_t* mymemory_init(size_t size);
//tenta alocar um bloco de memória, Se for bem sucedido retorna um ponteiro contrário null
void* mymemory_alloc(mymemory_t *memory, size_t size);

void mymemory_free(mymemory_t *mymemory, void *ptr);

void mymemory_display(mymemory_t *memory);

void mymemory_release(mymemory_t *memory);

#endif