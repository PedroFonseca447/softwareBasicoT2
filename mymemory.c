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


    //para percorrer a memória usando o first fit como guia para alocar

    while(current){
            //procura o espaço na lista
        if((char*)current->start- (char*)memory->pool >= size){
            break;
        }

        prev = current;
        current = current->next;
    }

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

        return aux->start;//retorna o ponteiro para onde o aux começa na memoria
        
}



void mymemory_free(mymemory_t *mymemory, void *ptr){



    //os nodos de controle
    allocation_t *prev = NULL;
    allocation_t *current = mymemory->head;


    while (current){

        if(current->start == ptr){

            if(prev){
                //no meio da memoria
                
                prev->next = current->next;
                
            }else{
                //no inicio da memoria
                mymemory->head = current->next;
            }
            return;

        }    

        prev=current;
        current= current->next;
    }
    

}

void mymemory_display(mymemory_t *memory){

     //os nodos de controle
   // allocation_t *prev = NULL;
    allocation_t *current = memory->head;


    while(current){

        printf("Inicio bloco de memória em relação ao start: %p \n", current->start  );
        printf("Tamanho do bloco de memória: %ld \n", current->size);
        current = current->next;
    }


}

void mymemory_stats(mymemory_t *memory){

    allocation_t *current = memory -> head;


    size_t contador_alocacoes = 0;
    size_t memoria_total_alocada = 0;
    size_t  memoria_total_livre = memory->total_size;
    size_t maior_bloco_livre=0;
    size_t numero_de_fragmentos =0;


    void *aux = memory->pool;


    while(current){
        contador_alocacoes++;

        memoria_total_alocada += current->size;
        memoria_total_livre -=  current->size;


    size_t bloco_livre = (char*) current->start - (char*)aux;

        if(bloco_livre > 0){
            numero_de_fragmentos++;

            if(bloco_livre > maior_bloco_livre){
                maior_bloco_livre = bloco_livre;
            }
        }

        aux = (char*) current->start + current->size;
        current = current->next;
    }

    size_t ultimo_bloco = (char*)memory->pool - (char*) aux;

    if(ultimo_bloco > 0 ){
        numero_de_fragmentos++;
        if(ultimo_bloco > maior_bloco_livre){
            maior_bloco_livre = ultimo_bloco;
        }
    }


    printf("Número total de alocacoes: %zu \n", contador_alocacoes);
    printf("Memória total alocada: %zu \n", memoria_total_alocada);
    printf("Memória total livre: %zu \n", memoria_total_livre);
    printf("Tamanho do maior bloco de memória livre: %zu \n", maior_bloco_livre);
    printf("Número total de fragmentações externas: %zu \n", numero_de_fragmentos);
    
}


void mymemory_release(mymemory_t *memory){
    memory->head->next = NULL;
    memory->head = NULL;


}
