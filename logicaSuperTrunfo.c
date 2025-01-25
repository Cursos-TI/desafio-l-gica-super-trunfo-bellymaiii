#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{

char codigo[4];
int populacao;
float area;
float PIB;
int pontos_Turisticos;
float densidade_populacional;
float PIB_percapita;
float super_poder;
} cidade;

void calcularSuper_poder(cidade* cidade){
cidade->super_poder=cidade->populacao + cidade->area + cidade->PIB + cidade->pontos_Turisticos + cidade->densidade_populacional + cidade->PIB_percapita;
}

void preencherCidade(cidade* cidade, char estado, int numero_cidade, int populacao, float area, float PIB, int pontos_Turisticos){

snprintf(cidade->codigo, sizeof(cidade-> codigo), "%c%02d", estado, numero_cidade);

cidade->populacao= populacao;
cidade->area= area;
cidade->PIB= PIB;
cidade->pontos_Turisticos= pontos_Turisticos;

if(cidade->area > 0){
   cidade->densidade_populacional=cidade->populacao / cidade->area;
}

else{
    cidade->densidade_populacional=0;
}

if(cidade->populacao > 0){
    cidade->PIB_percapita= cidade->PIB / cidade->populacao;
}

else{
    cidade->PIB_percapita=0;
}
CalcularSuper_Poder(cidade);

}

void cadastrarCidade(cidade* cidade){

printf("digite o codigo da cidade:");
scanf("%s", &cidade->codigo);

printf("digite a populacao:");
scanf("%d",&cidade->populacao);

printf("digite a area:");
scanf("%f", &cidade->area);

print("digite o PIB:");
scanf("%f", &cidade->PIB);

printf("digite o numero de pontos turisticos:");
scanf("%d", &cidade->pontos_Turisticos);


if(cidade->area > 0){
   cidade->densidade_populacional=cidade->populacao / cidade->area;  
}
else{
    cidade->densidade_populacional= 0;
}
if(cidade->populacao > 0){
    cidade->PIB_percapita= cidade->PIB / cidade->populacao;
}
else{
    cidade->PIB_percapita= 0;
}
CalcularSuper_poder(cidade);
}

void exibirCidade(const cidade* cidade){

printf("\n --- dados da cidade --- \n", cidade->codigo);
printf("populacao: %d\n", cidade->populacao);
printf("area: %.2f\n",cidade->area);
printf("PIB: %.2f\n", cidade->PIB);
print("pontos turisticos: %d\n", cidade->pontos_Turisticos);
printf("densidade populacional: %.2f\n", cidade->densidade_populacional);
printf("PIB per capita: %.2f\n", cidade->PIB_percapita);
printf("super poder: %.2f\n", cidade->super_poder);
}

void compararCidades(const cidade* c1, const cidade* c2) {

    printf("\n=== comparacao entre %s e %s ===\n", c1->codigo, c2->codigo);

    if(c1->densidade_populacional< c2->densidade_populacional){
        printf("densidade populacional: %s vence\n", c1->codigo);
    }

    else if(c1->densidade_populacional > c2->densidade_populacional){
        printf("densidade populacional: %s vence\n", c2->codigo);
    }
    else{ 
        printf("densidade populacional: empate /n");
    }
    
    if(c1->PIB_percapita > c2->PIB_percapita){
        printf("PIB per capita: %s vence\n", c1->codigo);
    }
    else if(c1->PIB_percapita < c2->PIB_percapita){
        printf("PIB per capita: %s vence\n", c2->codigo);
    }
    else{
        printf("PIB per capita: empate\n");
    }

    if(c1->super_poder > c2->super_poder){
        printf("super poder: %s vence\n", c1->codigo);  
    }
    else if(c1->super_poder < c2->super_poder){
        printf("super poder: %s vence\n", c2->codigo);
    }
    else{
        printf("super poder: empate\n");
    }
}

int main(){
    int totalEstados=8;
    int cidadesPorEstado=4;
    int totalCidades= totalEstados* cidadesPorEstado;

    cidade* cidades=(cidade*)malloc(totalCidades* sizeof(cidade));
    if(cidades==NULL){
        printf("erro ao alocar memoria!"\n);
        return 1;
    }
    printf("escolha o metodo de cadastro:\n");
    printf("1-cadastro manual\n");
    printf("2-cadastro automatico\n");
    int escolha;
    scanf("%d", &escolha);

    if(escolha==1){
        for(int i= 0; i < totalCidades; i++){
            cadastrarCidade(&cidades[i]);
        }
    } else{
        printf("\n=== cadastro automatico de cidades ===\n");
        int populacoes[]={100000, 200000, 150000,180000, 120000, 300000, 250000,220000};
        float areas[]={50.5,120.7,80.3, 95.6, 60.8, 150.2, 130.4, 110.9};
        float PIBS[]={5000, 8000, 6000, 7500,5500, 9000, 8500, 7000};
        int pontosTuristicos[]={5, 8 , 7, 6 , 4, 10, 9 , 8};
    
    for(char estado='a'; estado <'a' +totalEstados; estado++){
        for(int i = 1; i <= cidadesPorEstado; i++){
            int index= (estado - 'a')* cidadesPorEstado +(i- 1);
            int dataIndex= (i - 1) % 8;
            preencherCidade(&cidades[index], estado, i, populacoes[dataIndex], areas[dataIndex], PIBS[dataIndex], pontosTuristicos[dataIndex]);

        }
    }



    }

    printf("\n=== dadoscadastrados ===\n");
    for(int i = 0; i < totalCidades; i++){
        exibirCidade(&cidades[i]);
    }

    printf("\n=== comparar cidades ===\n");
    int c1Index, c2Index;
    printf("digite o indice da primeira cidade:", totalCidades - 1);
    scanf("%d", &c1Index);

    printf("digite o indice da segunda cidade:", totalCidades - 1);
    scanf("%d", &c2Index);

    if(c1Index >= 0 && c1Index < totalCidades && c2Index >= 0 && c2Index < totalCidades){
        compararCidades(&cidades[c1Index], &cidades[c2Index]);
    }
    else{
        printf("indices invalidos!\n");  
    }
    free(cidades);

    return 0;

}





    
