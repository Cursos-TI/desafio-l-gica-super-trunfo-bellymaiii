#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
char estado;
char nome [50];
char codigo[5];
int populacao;
float area;
float PIB;
int pontos_Turisticos;
float densidade_Populacional;
float PIB_Percapita;
float super_Poder;

} cidade;

static void LimparBufferDeEntrada();
static int obterInteiroPositivo(const char* mensagem);
static float obterFloatPositivo(const char* mensagem);
static unsigned long int obterUlongPositivo(const char* mensagem);
static void LimparTela();

void calcularAtributosDerivados(cidade* c){
    if (c->area >0.0f){
        c->densidade_Populacional = (float)c->populacao / c->area;
    } else {
        c->densidade_Populacional = 0.0f;
    }
    if (c->populacao > 0){
        c->PIB_Percapita = (c->PIB* 1000000000.0f) / (float)c->populacao;
    } else {
        c->PIB_Percapita = 0.0f;
    }

    c->super_Poder = ((float)c->populacao / 1000000000.0f) +
                      (c->area / 10.0f) +
                      (c->PIB * 100.0f) +
                      ((float)c->pontos_Turisticos * 50.0f);
    if (c->densidade_Populacional > 0.0f){
        c->super_Poder += (1.0f / c->densidade_Populacional) * 100.0f;
    }
    c->super_Poder += (c->PIB_Percapita / 1000.0f);
}

void preencherCidade (cidade* c, char estado_char, int numero_cidade, int populacao, float area, float PIB, int pontos_Turisticos, const char* nome_cidade){
    c->estado = toupper (estado_char);
    snprintf (c->codigo, 5, "%c%02d", c->estado, numero_cidade);
    strcpy(c->nome, nome_cidade);

    c->populacao = populacao;
    c->area = area;
    c->PIB = PIB;
    c->pontos_Turisticos = pontos_Turisticos;

    calcularAtributosDerivados(c);
}

void cadastrarCidade(cidade* c){
    printf("\n--- cadastro manual de cidade ---\n");

    printf("digite o estado (uma letra de A a Z):");
    scanf("%c", &c->estado);
    
    c->estado = toupper (c->estado);
    LimparBufferDeEntrada();

    printf("digite o codigo da cidade(ex: B01):");
    fgets(c->codigo, 5, stdin);
    c->codigo[strcspn(c->nome, "\n")] = '\0';

    c->populacao = obterUlongPositivo ("digite a populacao:");
    c->area = obterFloatPositivo ("digite a area (em km2):");
    c->PIB = obterFloatPositivo ("digite o PIB (em bilhoes de reais):");
    c->pontos_Turisticos = obterInteiroPositivo ("digite o numero de pontos turisticos:");

    calcularAtributosDerivados(c);
    printf("\n cidade %s cadastrada com sucesso! \n", c->nome);
}

void exibirCidade(const cidade* c1, const cidade* c2){
    
    printf("\n=== dados da cidade ===\n %s", c->codigo);
    printf("nome: %s \n", c->nome);
    printf("estado: %c \n", c->estado);
    printf("populacao: %lu habitantes \n", c->populacao);
    printf("area: %.2f km2 \n", c->area);
    printf("PIB: %.2f bilhoes \n", c->PIB);
    printf("pontos turisticos: %d \n", c->pontos_Turisticos);
    printf("densidade populacional: %.2f hab/km2 \n", c->densidade_Populacional);
    printf("PIB Percapita: %.2f \n", c->PIB_Percapita);
    printf("super poder: %.2f \n", c->super_Poder);
    printf("==============================\n");
}

void exibirCidade(const cidade* c1, const cidade* c2){
    
    printf("\n=== comparacao entre %s (%s) e %s (%s) ===\n", c1->codigo, c1->nome, c2->codigo, c2->nome);
    printf("%s (%s): %.2f hab/km2", c1->codigo, c1->nome, c1->densidade_Populacional);
    printf("%s (%s): %.2f hab/km2", c2->codigo, c2->nome, c2->densidade_Populacional);
    if (c1->densidade_Populacional < c2->densidade_Populacional){
        printf("resultado: %s (%s) vence! \n", c1->codigo, c1->nome);
    } else if (c1->densidade_Populacional > c2->densidade_Populacional){
        printf("resultado: %s (%s) vence! \n", c2->codigo, c2->nome);
    } else {
        printf("resultado: empate! \n");
    }
    printf("==============================\n");

    printf("PIB Percapita(maior vence): \n");
    printf("%s (%s): R$ %.2f \n", c1->codigo, c1->nome, c1->PIB_Percapita);
    printf("%s (%s): R$ %.2f \n", c2->codigo, c2->nome, c2->PIB_Percapita);
    if (c1->PIB_Percapita > c2->PIB_Percapita){
        printf("resultado: %s (%s) vence! \n", c1->codigo, c1->nome);
    } else if (c1->PIB_Percapita <c2->PIB_Percapita){
        printf("resultado: %s (%s) vence! \n", c2->codigo, c2->nome);
    } else {
        printf("resultado: empate! \n");
    }
    printf("==============================\n");

    printf("super poder(maior vence): \n");
    printf("%s (%s): %.2f pontos \n", c1->codigo, c1->nome, c1->super_Poder);
    printf("%s (%s): %.2f pontos \n", c2->codigo, c2->nome, c2->super_Poder);
    if (c1->super_Poder > c2->super_Poder){
        printf("resultado: %s (%s) vence! \n", c1->codigo, c1->nome);
    } else if (c1->super_Poder < c2->super_Poder){
        printf("resultado: %s (%s) vence! \n", c2->codigo, c2->nome);
    } else {
        printf("resultado: empate! \n");
    }
    printf("==============================\n");
}

static void LimparBufferDeEntrada(){
    int c;
    while ((c= getchar())!= '\n' && c != EOF);
}

static void LimparTela(){
    #ifdef _WIN32
        system ("cls");
    #else
        system ("clear");
    #endif
}

static int obterInteiroPositivo(const char* mensagem){
    int valor;
    int leitura_ok;
    do{
        printf("%s", mensagem);
        leitura_ok = scanf("%d", &valor);
        if (leitura_ok != 1 || valor < 0){
            printf("erro: entrada invalida. Digite um numero inteiro nao negativo. Tente novamente. \n");
            LimparBufferDeEntrada();
        }
    } while (leitura_ok != 1 || valor < 0);
    LimparBufferDeEntrada();
    return valor;
}

static float obterFloatPositivo(const char* mensagem){
    float valor;
    int leitura_ok;
    do{
        printf("%s", mensagem);
        leitura_ok = scanf("%f", &valor);
        if (leitura_ok != 1 || valor < 0.0f){
            printf("erro: valor invalido. Insira um numero decimal positivo ou zero. Tente novamente. \n");
            LimparBufferDeEntrada();
        }
    } while (leitura_ok != 1 || valor <0.0f);
    LimparBufferDeEntrada();
    return valor;
}

static unsigned long int obterUlongPositivo(const char* mensagem){
    unsigned long int valor;
    int leitura_ok;
    do{
        printf("%s", mensagem);
        leitura_ok = scanf("%lu", &valor);
        if (leitura_ok != 1){
            printf("erro: entrada invalida. Digite um numero inteiro grande. Tente novamente. \n");
            LimparBufferDeEntrada();
        }
    } while (leitura_ok != 1);
    LimparBufferDeEntrada();
    return valor;
}

int main(){
    const int totalEstados = 8;
    const int cidadesPorEstado = 4;
    const int totalCidades = totalEstados * cidadesPorEstado;
    const int numCartasPadrao = 2;

    cidade* cidades = (cidade*)malloc(totalCidades * sizeof (cidade));
    if (cidades == NULL){
        printf("erro ao alocar memoria! \n");
        return 1;
    }

    LimparTela();
    printf("=== Super Trunfo de Cidades ===\n");
    printf("escolha o metodo de cadastro: \n");
    printf("1- cadastro manual \n");
    printf("2- cadastro automatico \n");
    int escolha = obterInteiroPositivo ("sua escolha:");

    if (escolha == 1){
        for (int i = 0; 1 < totalCidades; i++){
            cadastrarCidade(&cidades[i]);
            printf("pressione ENTER para continuar para a proxima cidade...\n");
            LimparBufferDeEntrada();
        }
    } else {
        printf("\n=== cadastro automatico de cidades ===\n");
        int populacoes[]={1333000, 347657, 224112, 78181, 265074, 325685, 227646, 463501};
        float areas[]={496.8f, 131.1f, 1.497f, 276.7f, 468.2f, 1.610f, 223.6f, 1.652f};
        float PIBS[]={81560.0f, 18466.0f, 3743.0f, 3749.0f, 10983.0f, 108000.0f, 10000.0f, 60506.0f};
        int pontosTuristicos[]={8, 5, 14, 8, 10, 7, 8, 8};
        const char* nomesCidades[]={"Porto Alegre", "Canoas", "Viamao", "Esteio", "Gravatai", "Pelotas", "Novo Hamburgo", "Caxias do Sul"};

        int nome_idx = 0;
        for (char estado = 'A'; estado < 'A' + totalEstados; estado++){
            for(int i = 1; i <= cidadesPorEstado; i++){
                int index = (estado - 'A') * cidadesPorEstado + (i - 1);
                int dataIndex = (i - 1) % 8; 
                preencherCidade(&cidades[index], estado, 1, populacoes[dataIndex], areas[dataIndex],PIBS[dataIndex],pontosTuristicos[dataIndex], nomesCidades[nome_idx %8]);
                nome_idx++;
            }
        }
        printf("\n todas as cidades foram preenchidas automaticamente! \n");
    }
    printf("\n pressione ENTER para exibir as cidades cadastradas...\n");
    LimparBufferDeEntrada();
    LimparTela();

    printf("\n=== dados cadastrados===\n");
    for(int i = 0; i < totalCidades; i++){
        exibirCidade(&cidades[i]);
    }

    printf("\n pressione ENTER para iniciar a comparacao de cidade...\n");
    LimparBufferDeEntrada();
    LimparTela();

    printf("\n=== comparar cidades ===\n");
    printf("existem %d cidades cadastradas (indices de 0 a %d).\n", totalCidades,totalCidades - 1);
    int c1Index, c2Index;

    c1Index = obterInteiroPositivo("digite o indice da primeira cidade para comparar:");
    c2Index = obterInteiroPositivo("digite o indice da segunda cidade para comparar:");

    if (c1Index >= 0 && c1Index < totalCidades && c2Index >= 0 && c2Index < totalCidades){
        cadastrarCiade(&cidades[c1Index], &cidades[c2Index]);
    } else {
        printf("indices invalidos! por favor, digite indices dentro do intervalo permitido.\n");
    }

    free(cidades);

    printf("\n programa finalizado. Pressione ENTER para sair. \n");
    LimparBufferDeEntrada();

    return 0;
}


