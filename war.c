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
#define TOTAL_MISSOES 5

const char* missoes[TOTAL_MISSOES] = {
    "Conquistar 3 territorios seguidos",
    "Eliminar todas as tropas da cor vermelha",
    "Manter pelo menos 2 territorios vivos",
    "Conquistar um territorio de cada cor",
    "Eliminar completamente 1 territorio inimigo"
};

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct Territorio {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
};
// --- Protótipos das Funções ---
void exibirMenu ();
void cadastroTerritorio (struct Territorio *war, int *totalTerritorios);
void territoriosCadastrados (const struct Territorio *war, int totalTerritorios);
void liberarMemoria (struct Territorio *war);
void atribuirMissao(char** destino, const char* missoes[], int totalMissoes);
void menuDeAcoes ();
void atacar(struct Territorio* atacante, struct Territorio* defensor);
int verificarMissao(const char* missao, struct Territorio* mapa, int total);
void mostrarMapa(struct Territorio* mapa, int total);
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:


// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    struct Territorio *war;
        war = (struct Territorio *) calloc(MAX_TERRITORIOS, sizeof(struct Territorio));

    if (war == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1; 
    }

    int totalTerritorios = 0;
    int opcao;


    do {
        exibirMenu ();
        scanf("%d" , &opcao);

        switch (opcao) {
            case 1:
            cadastroTerritorio (war, &totalTerritorios);
            break;

            case 2:
            territoriosCadastrados (war, totalTerritorios);
            break;

            case 0:
            printf("Vamos para a batalha!!!\n");
            break;

            default:
            printf("Opção invalida, Pressione Enter para tentar novamente\n");
            getchar ();
            break;

        }
}
    while (opcao !=0);

     char* missaoJogador = NULL;

     atribuirMissao(&missaoJogador, missoes, TOTAL_MISSOES);
     
     printf("\nMissão atribuída ao jogador: %s\n", missaoJogador);


    int option;
    int atacante, defensor;

    do {
        menuDeAcoes ();
        scanf("%d" , &option);

        switch (option) {
            case 1:
            {
                while (1) {
                    printf("\n--- FASE DE ATAQUE ---\n");
                    mostrarMapa(war, totalTerritorios);
                    
                    printf("Escolha o territorio atacante (1 a %d, ou 0 para voltar): ", totalTerritorios);
                    scanf("%d", &atacante);
                    getchar(); // limpa buffer
                    
                    if (atacante == 0) {
                        printf("Voltando ao menu de ações...\n");
                        break; // sai do loop de ataques e volta ao menu
                        }
                        
                        if (atacante < 1 || atacante > totalTerritorios) {
                            printf("Atacante inválido.\n");
                            continue;
                        }
                        
                        printf("Escolha o territorio defensor (1 a %d): ", totalTerritorios);
                        scanf("%d", &defensor);
                        getchar(); // limpa buffer
                        
                        if (defensor < 1 || defensor > totalTerritorios) {
                            printf("Defensor inválido.\n");
                            continue;
                        }
                        if (atacante == defensor) {
                            printf("Atacante e defensor não podem ser o mesmo.\n");
                            continue;
                        }
                        
                        atacar(&war[atacante - 1], &war[defensor - 1]);
                        
                        mostrarMapa(war, totalTerritorios);
                        
                        // Verifica missão após cada ataque
                        if (verificarMissao(missaoJogador, war, totalTerritorios)) {
                            printf("\nParabéns! Missão concluída: %s\n", missaoJogador);
                        }
                    }
                    
                    break;
                }

           
             

            case 2:
            int completa = verificarMissao(missaoJogador, war, totalTerritorios);
            if (completa) {
                printf("Parabéns! Você completou a missão: %s\n", missaoJogador);
            } else {
                printf("Missão ainda não concluída: %s\n", missaoJogador);
            }
            break;

            case 0:
            printf("Sair...\n");
            break;

            default:
            printf("Opção invalida, Pressione Enter para tentar novamente\n");
            getchar ();
            break;

        }
}
    while (option !=0);
    
    mostrarMapa(war, MAX_TERRITORIOS);

    free(missaoJogador);
    liberarMemoria (war);

   return 0;
}

void exibirMenu () {
    printf("=========================================================\n");
    printf("         WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("=========================================================\n");
    printf("1 - cadastrar novo territorio\n");
    printf("2 - Territorios cadastrados\n");
    printf("0 - Batalhar\n");
    printf("=========================================================\n");
    printf("escolha uma opção: \n");
}

void cadastroTerritorio (struct Territorio *war, int *totalTerritorios) {

    int qtd = 5;

    for (int i = 0; i < qtd; i++) {
    
        printf("--- Cadastrando Territorio %d ---\n", i + 1);

        printf("Nome do Territorio: ");
         getchar();
        fgets(war[i].nome, TAM_NOME, stdin);
        war[i].nome[strcspn(war[i].nome, "\n")] = 0; // Remove \n do fgets

        printf("Cor do Exército : ");
        fgets(war[i].cor, TAM_COR, stdin);
        war[i].cor[strcspn(war[i].cor, "\n")] = 0;

        printf("Número de Tropas: ");
        scanf("%d", &war[i].tropas);
        getchar(); // Limpa o \n que sobra no buffer do scanf

        printf("\n");
    }
    *totalTerritorios = qtd;
    } 

void territoriosCadastrados (const struct Territorio *war, int totalTerritorios) {
    int i;
   
    printf("=========================================================\n");
    printf("         MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("=========================================================\n");
    // Mostrando os territórios cadastrados
    printf("Territorios cadastrados:\n");
    for (i = 0; i < MAX_TERRITORIOS; i++) {
        printf("%d. %s (Exercito: %s, Tropas: %d)\n", i + 1, war[i].nome, war[i].cor, war[i].tropas);
        
    }
}

void liberarMemoria (struct Territorio *war) {
     free(war);
    printf("\nMemória liberada com sucesso!\n");


}

void atribuirMissao(char** destino, const char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;  
    *destino = (char*) malloc((strlen(missoes[sorteio]) + 1) * sizeof(char));
    if (*destino != NULL) {
        strcpy(*destino, missoes[sorteio]);
    }
}

void menuDeAcoes () {
    printf("=========================================================\n");
    printf("         MENU DE AÇÕES\n");
    printf("=========================================================\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar missões\n");
    printf("0 - Sair.\n");
    printf("=========================================================\n");
    printf("escolha uma ação: \n");
}

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

int verificarMissao(const char* missao, struct Territorio* mapa, int total) {
    if (strcmp(missao, "Conquistar 3 territorios seguidos") == 0) {
        int conquistados = 0;
        for (int i = 0; i < total; i++) {
            if (mapa[i].tropas > 0) {
                conquistados++;
            }
        }
        return (conquistados >= 3);
    }

    // Outras missões podem ser implementadas depois
    return 0;
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
