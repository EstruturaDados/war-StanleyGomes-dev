// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define MAX_TERRITORIOS 5
#define TAM_NOME 30
#define TAM_COR 10

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct Territorio {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
};
// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoAtacante);
    printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        // atacante vence
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

        // transfere cor
        strcpy(defensor->cor, atacante->cor);

        printf("VITÓRIA DO ATAQUE! %s conquistou %s e transferiu %d tropas.\n",
               atacante->nome, defensor->nome, tropasTransferidas);
    } else {
        // defensor vence
        atacante->tropas--;
        printf("DEFESA BEM-SUCEDIDA! %s perdeu 1 tropa.\n", atacante->nome);
    }

}
void mostrarMapa(struct Territorio* mapa, int total) {
    printf("\n========== MAPA DO MUNDO - ESTADO ATUAL ==========\n\n");
    for (int i = 0; i < total; i++) {
        printf("%d. %s (Exército %s, Tropas: %d)\n",
               i + 1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }
    printf("=================================================\n");
}

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    struct Territorio *war;
     int i = 0;

    war = (struct Territorio *) calloc(MAX_TERRITORIOS, sizeof(struct Territorio));

   

    printf("=========================================================\n");
    printf("         WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("=========================================================\n");

    do {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);

        printf("Nome do Territorio: ");
        fgets(war[i].nome, TAM_NOME, stdin);
        war[i].nome[strcspn(war[i].nome, "\n")] = 0; // Remove \n do fgets

        printf("Cor do Exército : ");
        fgets(war[i].cor, TAM_COR, stdin);
        war[i].cor[strcspn(war[i].cor, "\n")] = 0;

        printf("Número de Tropas: ");
        scanf("%d", &war[i].tropas);
        getchar(); // Limpa o \n que sobra no buffer do scanf

        printf("\n");
        i++;
    } while (i < MAX_TERRITORIOS);

    int atacante, defensor;
    
    printf("=========================================================\n");
    printf("         MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("=========================================================\n");
    // Mostrando os territórios cadastrados
    printf("Territorios cadastrados:\n");
    for (i = 0; i < MAX_TERRITORIOS; i++) {
        printf("%d. %s (Exercito: %s, Tropas: %d)\n", i + 1, war[i].nome, war[i].cor, war[i].tropas);
    }

    printf("\n--- FASE DE ATAQUE ---\n");
    printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", MAX_TERRITORIOS);
    scanf("%d", &atacante);

    if (atacante == 0) {
        printf("Saindo...\n");
        return 0;
    }

    printf("Escolha o territorio defensor (1 a %d): ", MAX_TERRITORIOS);
    scanf("%d", &defensor);

    atacar(&war[atacante - 1], &war[defensor - 1]);

    mostrarMapa(war, MAX_TERRITORIOS);
    free(war);
    printf("\nMemória liberada com sucesso!\n");




   
    return 0;
}

    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.


    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.


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
