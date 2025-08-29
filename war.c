#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_NOME 50
#define TAM_COR 20

typedef struct 
{
    char nome[TAM_NOME];
    char corExercito[TAM_COR];
    int quantidadeTropas;
} Territorio;

// Simulação de ataque entre dois territórios
void simularBatalha(Territorio *atacante, Territorio *defensor) 
{
    if (atacante->quantidadeTropas <= 1) 
    {
        printf("O território atacante não tem tropas suficientes para atacar. \n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1; 
    int dadoDefensor = rand() % 6 + 1;

    printf("Dado do atacante (%s): %d \n", atacante -> nome, dadoAtacante);
    printf("Dado do defensor (%s): %d \n", defensor -> nome, dadoDefensor);

    if (dadoAtacante >= dadoDefensor) 
        {
            printf("\n Atacante venceu a rodada! \n");
            defensor -> quantidadeTropas--;

                if (defensor->quantidadeTropas <= 0) 
                {
                    printf("O território %s foi conquistado por %s! \n", defensor -> nome, atacante -> corExercito);
                    defensor -> quantidadeTropas = atacante->quantidadeTropas - 1;
                    atacante -> quantidadeTropas = 1;
                    strcpy(defensor -> corExercito, atacante -> corExercito);
                }
        } else 
            {
                printf("Defensor resistiu ao ataque!\n");
                atacante -> quantidadeTropas --;
            }

        printf("Tropas restantes - %s: %d, %s: %d \n\n",
        atacante -> nome, atacante -> quantidadeTropas,
        defensor -> nome, defensor -> quantidadeTropas);
}

void exibirMapa(Territorio *territorios, int num) 
{
    printf("\n ------ ESTADO ATUAL DO MAPA ------ \n");
    for (int i = 0; i < num; i++) 
    {
        printf("Território %d: %s | Cor: %s | Tropas: %d\n", i, territorios[i].nome, territorios[i].corExercito, territorios[i].quantidadeTropas);
    }
    printf("----------------------------------- \n");
}

int main() 
{
    int numTerritorios = 5;
    Territorio *territorios = (Territorio *) calloc (numTerritorios, sizeof(Territorio));

    srand(time(NULL));

    printf("================================ \n");
    printf("    Cadastro de Territórios \n");
    printf("================================= \n");

    for (int i = 0; i < numTerritorios; i++) 
    {
        printf("\n --- TERRITÓRIO %d --- \n", i);

        printf("Nome do território: ");
        fgets(territorios[i].nome, TAM_NOME, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(territorios[i].corExercito, TAM_COR, stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].quantidadeTropas);
        getchar(); // limpar buffer
    }

    int continuar = 1;
    while (continuar) 
    {
        exibirMapa(territorios, numTerritorios);

        int iAtacante, iDefensor;
        printf("Escolha o território ATACANTE (0 a %d): ", numTerritorios - 1);
        scanf("%d", &iAtacante);
        printf("Escolha o território DEFENSOR (0 a %d): ", numTerritorios - 1);
        scanf("%d", &iDefensor);
        getchar();

        if (iAtacante == iDefensor || iAtacante < 0 || iAtacante >= numTerritorios || iDefensor < 0 || iDefensor >= numTerritorios) 
        {
            printf("Escolha inválida! \n");
            continue;
        }

        simularBatalha(&territorios[iAtacante], &territorios[iDefensor]);

        printf("Deseja realizar outra batalha? (1 - sim, 0 - não): ");
        scanf("%d", &continuar);
        getchar();
    }

    free(territorios);
    return 0;
}


// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
