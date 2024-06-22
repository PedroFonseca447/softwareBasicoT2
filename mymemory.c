#include <stdio.h>
#include <stdlib.h>
#include "mymemory.h"


mymemory_t* mymemory_init(size_t size){
    mymemory_t *memory = (mymemory_t *) malloc(sizeof(mymemory_t));
   
    //baseado no size passado por parametro passa o tamanho de pool
    //inicializa o valor da lista
    //faz a alocação
    memory->pool = malloc(size);
    if(!memory->pool){
        printf("Erro na alocação de pool de memória. \n");
        free(memory);
        return NULL;
    }

    //o tamanho do pool 
    memory->total_size = size;
    //pega o ponteiro e aponta para o start
    memory-> head = NULL;


    return memory;
}

void* mymemory_alloc(mymemory_t *memory, size_t size ){

    //  NODO HEAD;

    //os nodos de controle
    allocation_t *prev = NULL;
    allocation_t *current = memory->head;

    //Node aux = new Node(size);
    //node aux new node
    allocation_t *aux = (allocation_t*) malloc(sizeof(allocation_t));
    //(size)
    aux-> size = size;


    if(prev){

        prev->next = aux;// vincula na lista
        aux->start = (char*) prev->start + prev->size;
    }
    else{
        //insere no inicio
        aux-> start = memory->pool;
        //coloca o aux como o novo head
        memory->head = aux;
    }

        aux-> next= current;

        return aux->start;//sua relação ao start
        
}
