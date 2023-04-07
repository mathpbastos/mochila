#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM_OBJETOS 5
#define VOLUME_MAX 15 // kgs

int peso_obj[NUM_OBJETOS] = {4, 1, 2, 12, 1};
float valor_obj[NUM_OBJETOS] = {10, 1, 2, 4, 2};
int mochila[NUM_OBJETOS] = {0, 0, 0, 0, 0};
float valor_peso[NUM_OBJETOS] = {0, 0, 0, 0, 0};
int idx_obj_valor_peso[NUM_OBJETOS] = {0, 1, 2, 3, 4}; // vetor que terá o index dos objetos após ordenarmos o array valor_peso.
int peso_mochila = 0;

void gerar_FO_aleatoria(){
    srand(time(NULL));
    for(int i = 0; i < 10000; i++){
        int objeto = rand() % 5 + 0; // gera aleatórios entre 0 e 4
        if(((peso_mochila + peso_obj[objeto]) < 15) && mochila[objeto] == 0){
            mochila[objeto] = 1; // add objeto na mochila
            peso_mochila += peso_obj[objeto]; // atualiza o peso
        }
    }
}

void gerar_array_custo_peso(){
    // criando uma relação custo/peso para determinar os objetos mais vantajosos.
    for(int i = 0; i < NUM_OBJETOS; i++){
        valor_peso[i] = valor_obj[i] / peso_obj[i];
    }

    /* 
        Ordenando de forma decrescente o vetor de custo/peso para 
        efeitos de comparação na hora de inserir na mochila.
        O vetor idx_obj_valor_peso mantém o index dos objetos, para sabermos qual é qual
        mesmo após a ordenação.

        O algoritmo de ordenação é o BubbleSort.
    */
    for(int i = 0; i < NUM_OBJETOS - 1; i++){
        for(int j = 0; j < NUM_OBJETOS - i - 1; j++){
            if(valor_peso[j] < valor_peso[j+1]){
                float valor_peso_aux = valor_peso[j];
                valor_peso[j] = valor_peso[j+1];
                valor_peso[j+1] = valor_peso_aux;

                int idx_aux = idx_obj_valor_peso[j];
                idx_obj_valor_peso[j] = idx_obj_valor_peso[j+1];
                idx_obj_valor_peso[j+1] = idx_aux;
            }
        }
    }

}

void gerar_FO_gulosa(){
    for(int i = 0; i < NUM_OBJETOS; i++){
        if(((peso_mochila + peso_obj[idx_obj_valor_peso[i]]) < 15)){
            mochila[idx_obj_valor_peso[i]] = 1;
            peso_mochila += peso_obj[idx_obj_valor_peso[i]];
        }
    }
}

void imprimir_solucao(){
    int fo = 0;
    printf("Mochila: ");
    for(int i = 0; i < NUM_OBJETOS; i++){
        printf("%d ", mochila[i]);
        if(mochila[i] == 1){
            fo += valor_obj[i];
        }
    }
    printf("-- FO: %d | PESO: %d", fo, peso_mochila);
}

int main(){
    
    gerar_array_custo_peso();
    gerar_FO_gulosa();
    imprimir_solucao();

    return 0;
}