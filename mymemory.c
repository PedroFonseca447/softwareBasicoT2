void mymemory_stats(mymemory_t *memory) {
    if (!memory) {
        return;
    }

    allocation_t *current = memory->head;

    int contador_alocacoes = 0;
    int memoria_total_alocada = 0;
    int memoria_total_livre = memory->total_size;
    int maior_bloco_livre = 0;
    int numero_de_fragmentacoes = 0;

    void *aux = memory->pool;

    while (current) {
        contador_alocacoes++;
        memoria_total_alocada += current->size;
        memoria_total_livre -= current->size;

        // Calcula o tamanho do bloco livre entre alocações
        int bloco_livre = (char*)current->start - (char*)aux;

        if (bloco_livre > 0) {
            numero_de_fragmentacoes++;

            if (bloco_livre > maior_bloco_livre) {
                maior_bloco_livre = bloco_livre;
            }
        }

        aux = (char*)current->start + current->size;
        current = current->next;
    }

    // Verifica o bloco livre após a última alocação até o final do pool
    int bloco_livre_final = (char*)memory->pool + memory->total_size - (char*)aux;
    if (bloco_livre_final > 0) {
        numero_de_fragmentacoes++;

        if (bloco_livre_final > maior_bloco_livre) {
            maior_bloco_livre = bloco_livre_final;
        }
    }

    printf("Número total de alocações: %d\n", contador_alocacoes);
    printf("Memória total alocada: %d bytes\n", memoria_total_alocada);
    printf("Memória total livre: %d bytes\n", memoria_total_livre);
    printf("Tamanho do maior bloco contíguo de memória livre: %d bytes\n", maior_bloco_livre);
    printf("Número de fragmentações de memória livre: %d\n", numero_de_fragmentacoes);
}

