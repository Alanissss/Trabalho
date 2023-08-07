#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Definir constantes para os valores das características
#define GENERO_MASCULINO "masculino"
#define GENERO_FEMININO "feminino"
#define GENERO_NAO_RESPONDEU "nao respondeu"

#define COR_OLHOS_AZUIS "azuis"
#define COR_OLHOS_VERDES "verdes"
#define COR_OLHOS_CASTANHOS "castanhos"
#define COR_OLHOS_PRETOS "pretos"

#define COR_CABELOS_LOURO "louro"
#define COR_CABELOS_CASTANHO "castanho"
#define COR_CABELOS_PRETO "preto"
#define COR_CABELOS_RUIVO "ruivo"

#define ESCOLARIDADE_FUNDAMENTAL "ensino fundamental"
#define ESCOLARIDADE_MEDIO "ensino medio"
#define ESCOLARIDADE_SUPERIOR "ensino superior"
#define ESCOLARIDADE_OUTROS "outros"

// função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// função para ler uma string de forma segura, removendo o caractere '\n' do final
void lerString(char *string, int tamanho) {
    fgets(string, tamanho, stdin);
    int i = 0;
    while (string[i] != '\0' && string[i] != '\n') {
        i++;
    }
    if (string[i] == '\n') {
        string[i] = '\0';
    } else {
        limparBuffer(); 
    }
}

// função para converter a altura de string para float
float converterAltura(char *altura_str) {
    for (int i = 0; i < strlen(altura_str); i++) {
        if (altura_str[i] == ',') {
            altura_str[i] = '.';
        }
    }
    float altura;
    sscanf(altura_str, "%f", &altura);
    return altura;
}

int main() {
    // Variáveis e constantes para armazenar os dados da pesquisa
    int numeroEntrevistados = 0;
    int totalIdade = 0;
    int entrevistadosFemininos14a18 = 0;
    int entrevistadosMasculinos18ouMais = 0;
    int entrevistadosSemGenero = 0;
    int entrevistadosOlhosAzuis = 0;
    int entrevistadosCabelosRuivos = 0;
    int entrevistadosOlhosECabelosCastanhos = 0;
    float totalPeso = 0.0;
    float totalAltura = 0.0;
    int entrevistadosAcimaMediaAltura = 0;
    int entrevistadosEnsinoFundamental = 0;
    int entrevistadosEnsinoMedio = 0;
    int entrevistadosEnsinoSuperior = 0;
    int entrevistadosOutros = 0;

    // Variáveis temporárias para armazenar os dados de cada entrevistado
    char genero[20];
    char corOlhos[20];
    char corCabelos[20];
    float peso, altura;
    int idade;
    char escolaridade[50];

    printf("----- Pesquisa do IFRS Campus Canoas -----\n");

    // loop para coletar os dados dos entrevistados
    while (1) {
        printf("\nEntrevistado %d:\n", numeroEntrevistados + 1);

        printf("Genero (%s, %s, %s): ", GENERO_MASCULINO, GENERO_FEMININO, GENERO_NAO_RESPONDEU);
        lerString(genero, sizeof(genero));

        // verificação para sair do loop caso o usuário decida parar de coletar dados
        if (strcasecmp(genero, GENERO_NAO_RESPONDEU) == 0) {
            break;
        }

        printf("Cor dos olhos (%s, %s, %s, %s): ", COR_OLHOS_AZUIS, COR_OLHOS_VERDES, COR_OLHOS_CASTANHOS, COR_OLHOS_PRETOS);
        lerString(corOlhos, sizeof(corOlhos));

        printf("Cor dos cabelos (%s, %s, %s, %s): ", COR_CABELOS_LOURO, COR_CABELOS_CASTANHO, COR_CABELOS_PRETO, COR_CABELOS_RUIVO);
        lerString(corCabelos, sizeof(corCabelos));

        printf("Peso (kg): ");
        scanf("%f", &peso);

        limparBuffer();

        printf("Altura (metros, use virgula em vez de ponto): ");
        char altura_str[10];
        lerString(altura_str, sizeof(altura_str));
        altura = converterAltura(altura_str);

        printf("Idade em anos: ");
        scanf("%d", &idade);

        limparBuffer(); // limpa o buffer na próxima leitura

        printf("Escolaridade (%s, %s, %s, %s): ", ESCOLARIDADE_FUNDAMENTAL, ESCOLARIDADE_MEDIO, ESCOLARIDADE_SUPERIOR, ESCOLARIDADE_OUTROS);
        lerString(escolaridade, sizeof(escolaridade));

        // resumo da entrevista
        printf("\n*** Resumo da Entrevista ***\n");
        printf("Genero: %s\n", genero);
        printf("Cor dos olhos: %s\n", corOlhos);
        printf("Cor dos cabelos: %s\n", corCabelos);
        printf("Peso: %.2f kg\n", peso);
        printf("Altura: %.2f metros\n", altura);
        printf("Idade: %d anos\n", idade);
        printf("Escolaridade: %s\n", escolaridade);

        // atualiza as estatísticas com os dados da entrevista
        numeroEntrevistados++;
        totalIdade += idade;
        totalPeso += peso;
        totalAltura += altura;

        if (strcasecmp(genero, GENERO_FEMININO) == 0 && idade >= 14 && idade <= 18) {
            entrevistadosFemininos14a18++;
        }

        if (strcasecmp(genero, GENERO_MASCULINO) == 0 && idade >= 18) {
            entrevistadosMasculinos18ouMais++;
        }

        if (strcasecmp(genero, GENERO_NAO_RESPONDEU) == 0) {
            entrevistadosSemGenero++;
        }

        if (strcasecmp(corOlhos, COR_OLHOS_AZUIS) == 0) {
            entrevistadosOlhosAzuis++;
        }

        if (strcasecmp(corCabelos, COR_CABELOS_RUIVO) == 0) {
            entrevistadosCabelosRuivos++;
        }

        if (strcasecmp(corOlhos, COR_OLHOS_CASTANHOS) == 0 && strcasecmp(corCabelos, COR_CABELOS_CASTANHO) == 0) {
            entrevistadosOlhosECabelosCastanhos++;
        }

        if (altura > totalAltura / numeroEntrevistados) {
            entrevistadosAcimaMediaAltura++;
        }

        if (strcasecmp(escolaridade, ESCOLARIDADE_FUNDAMENTAL) == 0) {
            entrevistadosEnsinoFundamental++;
        } else if (strcasecmp(escolaridade, ESCOLARIDADE_MEDIO) == 0) {
            entrevistadosEnsinoMedio++;
        } else if (strcasecmp(escolaridade, ESCOLARIDADE_SUPERIOR) == 0) {
            entrevistadosEnsinoSuperior++;
        } else {
            entrevistadosOutros++;
        }
    }

    // Cálculos finais
    float mediaIdade = (float) totalIdade / numeroEntrevistados;
    float porcentagemOlhosAzuis = (float) entrevistadosOlhosAzuis / numeroEntrevistados * 100;
    float porcentagemCabelosRuivos = (float) entrevistadosCabelosRuivos / numeroEntrevistados * 100;
    float porcentagemEnsinoFundamental = (float) entrevistadosEnsinoFundamental / numeroEntrevistados * 100;
    float porcentagemEnsinoMedio = (float) entrevistadosEnsinoMedio / numeroEntrevistados * 100;
    float porcentagemEnsinoSuperior = (float) entrevistadosEnsinoSuperior / numeroEntrevistados * 100;
    float porcentagemOutros = (float) entrevistadosOutros / numeroEntrevistados * 100;
    float mediaPeso = totalPeso / numeroEntrevistados;
    float mediaAltura = totalAltura / numeroEntrevistados;

    // Resultados da pesquisa
    printf("\n----- Resultados da Pesquisa -----\n");
    printf("Numero de entrevistados: %d\n", numeroEntrevistados);
    printf("Media de idade dos entrevistados: %.2f anos\n", mediaIdade);
    printf("Quantidade de entrevistados do genero feminino entre 14 e 18 anos: %d\n", entrevistadosFemininos14a18);
    printf("Quantidade de entrevistados do genero masculino com 18 anos ou mais: %d\n", entrevistadosMasculinos18ouMais);
    printf("Quantidade de entrevistados que não forneceram o genero: %d\n", entrevistadosSemGenero);
    printf("Porcentagem de entrevistados de olhos azuis: %.2f%%\n", porcentagemOlhosAzuis);
    printf("Porcentagem de entrevistados de cabelos ruivos: %.2f%%\n", porcentagemCabelosRuivos);
    printf("Quantidade de entrevistados que tem olhos e cabelos castanhos: %d\n", entrevistadosOlhosECabelosCastanhos);
    printf("Media de peso dos entrevistados: %.2f kg\n", mediaPeso);
    printf("Media de altura dos entrevistados: %.2f metros\n", mediaAltura);
    printf("Quantidade de entrevistados com altura acima da media: %d\n", entrevistadosAcimaMediaAltura);
    printf("Porcentagem de entrevistados com ensino fundamental: %.2f%%\n", porcentagemEnsinoFundamental);
    printf("Porcentagem de entrevistados com ensino medio: %.2f%%\n", porcentagemEnsinoMedio);
    printf("Porcentagem de entrevistados com ensino superior: %.2f%%\n", porcentagemEnsinoSuperior);
    printf("Porcentagem de entrevistados com outras escolaridades: %.2f%%\n", porcentagemOutros);

    return 0;
}
