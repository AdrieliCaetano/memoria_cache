#include <stdio.h>
#include <stdlib.h>
#define NUM 4 // alterar aqui para modificar o número de linhas da cache

//dados que cada linha de uma memória cache possui
typedef struct dados{
    int v;
    int tag;
    int data;
}TDados;

//estrutura de uma memória cache associativa por conjuntos (4-way) com NUM linhas
typedef struct mem_cache{
    TDados set0[NUM];
    TDados set1[NUM];
    TDados set2[NUM];
    TDados set3[NUM];
}TMem_cache;

//cria uma mémoria cache associativa (4-way) preenchida com dados aleatórios
//os valores da tag e do data são iguais ao valor do endereço mapeado na cache
//a linha da cache (index) em que o endereço deve ser mapeado é dado pelo resto da divisão do endereço pela quantidades de linhas(NUM)
TMem_cache *cria(void){
    TMem_cache *mem = (TMem_cache*) calloc(1,sizeof(TMem_cache));
    int x,y; // y=endereço, x=index(linha)
    for(int i = 0; i < NUM/2; i++){
        y = (rand() % 1000) + 1;
        x = y % NUM;
        mem->set0[x].v = 1;
        mem->set0[x].tag = y;
        mem->set0[x].data = y;

    }
    for(int i = 0; i < NUM/2; i++){
        y = (rand() % 1000) + 1;
        x = y % NUM;
        mem->set1[x].v = 1;
        mem->set1[x].tag = y;
        mem->set1[x].data = y;

    }
    for(int i = 0; i < NUM/2; i++){
        y = (rand() % 1000) + 1;
        x = y % NUM;
        mem->set2[x].v = 1;
        mem->set2[x].tag = y;
        mem->set2[x].data = y;
    }
    for(int i = 0; i < NUM/2; i++){
        y = (rand() % 1000) + 1;
        x = y % NUM;
        mem->set3[x].v = 1;
        mem->set3[x].tag = y;
        mem->set3[x].data = y;
    }
    return mem;
}
//imprime a memoria cache
void imprime(TMem_cache *mem){
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n--------------------------------------");
    printf("\n                 Set 0             ");
    printf("\n--------------------------------------");
    printf("\nIndex     V       Tag            Data\n");
    printf("......................................");
    for (int i = 0; i < NUM; i++){
        printf("\n%4d      %d      %4d            %4d", i,mem->set0[i].v, mem->set0[i].tag, mem->set0[i].data);
    }
    printf("\n");

    printf("\n--------------------------------------");
    printf("\n                 Set 1             ");
    printf("\n--------------------------------------");
    printf("\nIndex     V       Tag            Data\n");
    printf("......................................");
    for (int i = 0; i < NUM; i++){
        printf("\n%4d      %d      %4d            %4d", i,mem->set1[i].v, mem->set1[i].tag, mem->set1[i].data);
    }
    printf("\n");

    printf("\n--------------------------------------");
    printf("\n                 Set 2             ");
    printf("\n--------------------------------------");
    printf("\nIndex     V       Tag            Data\n");
    printf("......................................");
    for (int i = 0; i < NUM; i++){
        printf("\n%4d      %d      %4d            %4d", i,mem->set2[i].v, mem->set2[i].tag, mem->set2[i].data);
    }
    printf("\n");

    printf("\n--------------------------------------");
    printf("\n                 Set 3             ");
    printf("\n--------------------------------------");
    printf("\nIndex     V       Tag            Data\n");
    printf("......................................");
    for (int i = 0; i < NUM; i++){
        printf("\n%4d      %d      %4d            %4d", i,mem->set3[i].v, mem->set3[i].tag, mem->set3[i].data);
    }
    printf("\n");
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");


}
//verifica se o endereço está mapeado em alguma linha de um dado set da cache
int verifica_set(TMem_cache *mem, int n, int index, int set){
    if(set == 0){
        if(mem->set0[index].v == 0){
            return 0;
        }
        else{
            if(mem->set0[index].tag != n){
                return 0;
            }
            else{
                return 1;
            }
        }
    }
    if(set == 1){
        if(mem->set1[index].v == 0)
            return 0;
        else{
            if(mem->set1[index].tag != n)
                return 0;
            else{
                return 1;
            }
        }
    }
    if(set == 2){
        if(mem->set2[index].v == 0)
            return 0;
        else{
            if(mem->set2[index].tag != n)
                return 0;
            else{
                return 1;
            }
        }
    }
    if(set == 3){
        if(mem->set3[index].v == 0)
            return 0;
        else{
            if(mem->set3[index].tag != n)
                return 0;
            else{
                return 1;
            }
        }
    }
    printf("\nSet invalido!\n");
    return -1;
}
//retorna o numero do primeiro set vazio no indice dado
//se todos estiverem cheio, retorna -1
int set_vazio(TMem_cache *mem, int index){
    if(mem->set0[index].v == 0)
        return 0;
    if(mem->set1[index].v == 0)
        return 1;
    if(mem->set2[index].v == 0)
        return 2;
    if(mem->set3[index].v == 0)
        return 3;
    return -1;
}
//faz a operação de leitura na cache
//n é o endereço
int load(TMem_cache *mem, int n){
    int index = n%NUM;
    int set0 = verifica_set(mem, n, index, 0);
    int set1 = verifica_set(mem, n, index, 1);
    int set2 = verifica_set(mem, n, index, 2);
    int set3 = verifica_set(mem, n, index, 3);
    if (set0 || set1 || set2 || set3){
        return 1; //hit: endereço já está cache
    }
    else { // endereço não está na cache
        int x = set_vazio(mem, index); //procura um set vazio na linha index
            if(x!= -1) //encontrou um set vazio: salva o endereço nesse set
            {
                if(x == 0)
                {
                    mem->set0[index].v = 1;
                    mem->set0[index].tag = n;
                    mem->set0[index].data = n;
                }
                if(x == 1)
                {
                    mem->set1[index].v = 1;
                    mem->set1[index].tag = n;
                    mem->set1[index].data = n;
                }
                if(x == 2)
                {
                    mem->set2[index].v = 1;
                    mem->set2[index].tag = n;
                    mem->set2[index].data = n;
                }
                if(x == 3)
                {
                    mem->set3[index].v = 1;
                    mem->set3[index].tag = n;
                    mem->set3[index].data = n;
                }
            }
            else{//não encontrou um set vazio
                x = rand() % NUM; // seleciona aleatoriamente um set para substituir o endereço que está no set pelo novo endereço
                if(x == 0)
                {
                    mem->set0[index].v = 1;
                    mem->set0[index].tag = n;
                    mem->set0[index].data = n;
                }
                if(x == 1)
                {
                    mem->set1[index].v = 1;
                    mem->set1[index].tag = n;
                    mem->set1[index].data = n;
                }
                if(x == 2)
                {
                    mem->set2[index].v = 1;
                    mem->set2[index].tag = n;
                    mem->set2[index].data = n;
                }
                if(x == 3)
                {
                    mem->set3[index].v = 1;
                    mem->set3[index].tag = n;
                    mem->set3[index].data = n;
                }
            }
        return 0; // miss
    }
}

int main(){
    TMem_cache *mem = cria();
    int acessos = 5; // alterar aqui para modifcar quantidade de acessos a serem feitos
    int endereco;
    int hit = 0;
    int miss = 0;
    printf("\n            CACHE INICIAL           \n");
    imprime(mem);
    for(int i = 0; i < acessos; i++){
        //printf("\n\nDigite um endereco para ser acessado (o numero deve ser maior do que 0):   ");
        //scanf("%d", &endereco);
        endereco = (rand() % 1000) + 1;
        printf("\n\nProximo endereco a ser acessado: %d\nPressione enter para continuar...", endereco);
        getchar();
        if (load(mem, endereco))
            hit += 1;
        else
            miss += 1;
        printf("\n\n            CACHE APOS ACESSO %d           \n", i);
        imprime(mem);
        printf("\n--------------------------------------");
        printf("\nHits: %d                 Miss: %d\n", hit, miss);
        printf("--------------------------------------");
    }
    printf("\n\n TOTAL DE HITS E MISS:");
    printf("\n--------------------------------------");
    printf("\nHits: %d                 Miss: %d\n", hit, miss);
    printf("--------------------------------------");

    free(mem);
    return 0;
}
