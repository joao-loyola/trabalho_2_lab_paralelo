#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>
#define TAM 15 // tamanho do vetor principal
#include <time.h>
#define TAG_SEND_DIR 11
#define TAG_SEND_ESQ 12



/*
    ##################################################################################################
                                               _                                  
                                  ___  _ __ __| | ___ _ __   __ _  ___ __ _  ___  
                                 / _ \| '__/ _` |/ _ \ '_ \ / _` |/ __/ _` |/ _ \ 
                                | (_) | | | (_| |  __/ | | | (_| | (_| (_| | (_) |
                                 \___/|_|  \__,_|\___|_| |_|\__,_|\___\__,_|\___/ 
                                                                                  
                                     _                                  
                                 ___(_)_ __   ___ _ __ ___  _ __   __ _ 
                                / __| | '_ \ / __| '__/ _ \| '_ \ / _` |
                                \__ \ | | | | (__| | | (_) | | | | (_| |
                                |___/_|_| |_|\___|_|  \___/|_| |_|\__,_|
    ##################################################################################################
                                     
*/

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// quicksort
void order_vetor(int *vetor, int tam) {
    qsort(vetor, tam, sizeof(int), compare);
}

/*
    ##################################################################################################
*/

void split_min(int *vetor, int ini, int fim, int tam_padrao) {
    
    int pos_alteradas = 0;
    
    while( vetor[ini + pos_alteradas] < vetor[ini-1- pos_alteradas ]) pos_alteradas++;
    
    
    for(int i = 0; i < pos_alteradas; i++){
        int temp = vetor[ini + i];
        vetor[ini + i] = vetor[ini-pos_alteradas+i];
        vetor[ini-pos_alteradas+i] = temp;
        
    }

    

    
    return;

    // return
    while(1) {
        // menor valor da thread seguinte
        int temp = vetor[fim];
        
        if (temp < vetor[fim-1]) {
            // ordena o novo valor, O(n)
            int i;
            for (i = fim-2; vetor[i] > temp && i >= 0; i--) vetor[i+1] = vetor[i];
            vetor[i+1] = temp;
        }
        else break;
    }
}


void split_max(int *vetor, int ini, int fim, int tam_padrao) {
    
    return;
    
    
    while(1) {
        // maior valor da thread anterior
        int temp = vetor[ini-1];
        
        if (temp > vetor[ini]) {
            // ordena o novo valor, O(n)
            int i;
            for (i = ini+1; temp > vetor[i] && i <= fim-1; i++) vetor[i-1] = vetor[i];
            vetor[i-1] = temp;
        }
        else break;
    }
}



int main(int argc, char** argv) {
    /*
    ##################################################################################################
                   ___ _   _ ___ ____ ___    _    _     ___ _____   _    ____    _    ___                                 
                  |_ _| \ | |_ _/ ___|_ _|  / \  | |   |_ _|__  /  / \  / ___|  / \  / _ \ 
                   | ||  \| || | |    | |  / _ \ | |    | |  / /  / _ \| |     / _ \| | | |
                   | || |\  || | |___ | | / ___ \| |___ | | / /_ / ___ \ |___ / ___ \ |_| |
                  |___|_| \_|___\____|___/_/   \_\_____|___/____/_/   \_\____/_/   \_\___/ 
    #################################################################################################
    */
    // double time_spent = 0.0;
    // clock_t begin = clock();

    // leitura dos TAM valores
    FILE *f1 = fopen("input.txt", "r");
    int *vetor = (int*) malloc(sizeof(int)*TAM);
    for(int i = 0 ; i < TAM;i++){
        int temp;
        fscanf(f1, "%d", &temp);
        vetor[i] = temp;
    }
    fclose(f1);

    omp_set_num_threads(4);
    # pragma omp parallel shared(vetor)
    {
        int rank = omp_get_thread_num();
        int size = omp_get_num_threads();

        int tam_padrao = TAM/size; // tamanho do vetor local (sem resto)
        int inicio = rank * tam_padrao;
        int fim = inicio + tam_padrao;
        int resto = TAM % size;
        if (rank == size-1) fim += resto; // resto fica no último processo
        int tam = fim - inicio; // tamanho do vetor local para cada processo

        /*
        ######################################################################################################
        */
        
        // número de iterações extras (necessárias quando tem resto)
        int extra = ceil((float)(resto) / tam_padrao) + 1 ;

        // ordenação sequencial dos vetores locais
        
        for (int interator_process = 0; interator_process < size+extra; interator_process++) {
            
            #pragma omp barrier
            order_vetor(&vetor[inicio], tam);
            #pragma omp barrier
            
            
            if (interator_process % 2 == 1) { // iteração impar
                if (rank % 2 == 1) { //rank impar
                    if (rank < size-1) 
                        split_max(vetor, inicio, fim, tam_padrao);
                }
                else { //rank par
                    if (rank > 0)
                        split_min(vetor, inicio, fim, tam_padrao);
                }
            }
            else { // iteração par
                if (rank % 2 == 0 ) { //rank par
                    if (rank < size-1) 
                        split_max(vetor, inicio, fim, tam_padrao);
                }
                else { //rank impar
                    split_min(vetor, inicio, fim, tam_padrao);
                }
            }
        }
        
    }
    
    // tempo de execução
    // clock_t end = clock();
    // time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    
    // escreve vetor ordenado em um arquivo
    FILE *f2 = fopen("output.txt", "w");
    for (int i = 0; i < TAM; i++) fprintf(f2, "%d  ", vetor[i]);
    free(vetor); fclose(f2);

    // escreve tempo de execução em um arquivo
    // FILE *f1 = fopen("time_result.csv", "a");
    // fprintf(f1, "%f\n", time_spent);
    // fclose(f1);
    
    return 0;
}
