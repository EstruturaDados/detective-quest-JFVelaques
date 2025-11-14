#include <stdio.h>
#include <stdlib.h> // Necessário para malloc

// --- ESTRUTURA DO CÔMODO (SALA) ---
/**
 * @brief Estrutura para representar um cômodo da mansão (nó da Árvore Binária).
 * * Contém o nome da sala e ponteiros para os caminhos da esquerda e direita.
 */
struct Sala {
    char nome[30];
    struct Sala *esquerda; // Caminho para a sala à esquerda (filho esquerdo)
    struct Sala *direita;  // Caminho para a sala à direita (filho direito)
};

// --- PROTÓTIPOS DAS FUNÇÕES ---
struct Sala* criarSala(const char *nome);
void explorarSalas(struct Sala *raiz);

// =========================================================================
// FUNÇÕES DE MANIPULAÇÃO DA ÁRVORE (MAPA)
// =========================================================================

/**
 * @brief Cria e aloca dinamicamente um novo cômodo (nó) na árvore.
 * * Requisito: criarSala() - cria, de forma dinâmica, uma sala com nome.
 * @param nome O nome da sala a ser criada.
 * @return Retorna um ponteiro para a nova Sala criada.
 */
struct Sala* criarSala(const char *nome) {
    // Aloca memória para a nova struct Sala
    struct Sala* novaSala = (struct Sala*)malloc(sizeof(struct Sala));
    
    // Verifica se a alocação foi bem-sucedida
    if (novaSala == NULL) {
        perror("Erro ao alocar memória para a Sala");
        exit(EXIT_FAILURE);
    }
    
    // Copia o nome para o campo nome da struct
    snprintf(novaSala->nome, sizeof(novaSala->nome), "%s", nome);
    
    // Inicializa os ponteiros dos caminhos como nulos (sem caminhos inicialmente)
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

/**
 * @brief Permite a navegação interativa do jogador pela árvore.
 * * Requisito: explorarSalas() - permite a navegação do jogador pela árvore.
 * @param salaAtual O ponteiro para o nó (sala) onde o jogador está atualmente.
 */
void explorarSalas(struct Sala *salaAtual) {
    char escolha;
    
    if (salaAtual == NULL) {
        printf("\n🚫 ERRO: O mapa não foi montado corretamente. Fim da exploração.\n");
        return;
    }

    // Loop de exploração contínua
    while (salaAtual != NULL) {
        printf("\n------------------------------------------\n");
        printf("Você está em: **%s**\n", salaAtual->nome);

        // Verifica se é um nó-folha (fim da linha de exploração)
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("✨ Parabéns! Você chegou ao final deste caminho (nó-folha).\n");
            printf("Não há mais cômodos para explorar a partir daqui. Fim da jornada.\n");
            break; // Sai do loop
        }

        printf("Escolha o próximo caminho:\n");
        
        // Exibe as opções de caminhos disponíveis
        if (salaAtual->esquerda != NULL) {
            printf("  [E] Esquerda -> Próxima Sala: %s\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf("  [D] Direita  -> Próxima Sala: %s\n", salaAtual->direita->nome);
        }
        printf("  [S] Sair da Mansão\n");
        printf("Sua escolha (E/D/S): ");
        
        // Leitura da escolha do jogador
        if (scanf(" %c", &escolha) != 1) {
            printf("❌ Entrada inválida.\n");
            // Limpa o buffer de entrada
            while (getchar() != '\n'); 
            continue; // Repete a iteração do loop
        }

        // Converte a escolha para minúsculas para facilitar a comparação
        if (escolha >= 'A' && escolha <= 'Z') {
            escolha += 32;
        }

        // Lógica de navegação
        if (escolha == 'e') {
            if (salaAtual->esquerda != NULL) {
                salaAtual = salaAtual->esquerda; // Move para a sala da esquerda
            } else {
                printf("⚠️ Não há caminho para a Esquerda a partir desta sala. Tente outra opção.\n");
            }
        } else if (escolha == 'd') {
            if (salaAtual->direita != NULL) {
                salaAtual = salaAtual->direita; // Move para a sala da direita
            } else {
                printf("⚠️ Não há caminho para a Direita a partir desta sala. Tente outra opção.\n");
            }
        } else if (escolha == 's') {
            printf("\n🚪 Saindo da Mansão. Até a próxima investigação!\n");
            break; // Sai do loop
        } else {
            printf("❌ Opção não reconhecida. Use 'E', 'D' ou 'S'.\n");
        }
        
        // Limpa o buffer de entrada
        while (getchar() != '\n');
    }
}

/**
 * @brief Função que libera a memória alocada para a árvore (melhoria de boas práticas).
 * @param sala O nó (sala) a ser liberado.
 */
void liberarMapa(struct Sala* sala) {
    if (sala != NULL) {
        liberarMapa(sala->esquerda);
        liberarMapa(sala->direita);
        // printf("Liberando: %s\n", sala->nome); // Opcional: para debug
        free(sala);
    }
}

// =========================================================================
// FUNÇÃO PRINCIPAL (MAIN)
// =========================================================================

/**
 * @brief Monta o mapa inicial da mansão e inicia o processo de exploração.
 * * Requisito: main() - monta o mapa inicial e dá início à exploração.
 */
int main() {
    printf("==================================================\n");
    printf("   🕵️ DETECTIVE QUEST: EXPLORAÇÃO DA MANSÃO 🕵️\n");
    printf("==================================================\n");

    // --- MONTAGEM DO MAPA (ÁRVORE BINÁRIA) ---
    // A montagem é manual no código-fonte, usando alocação dinâmica.
    
    // Nível 0: Raiz (Hall de Entrada)
    struct Sala *hall = criarSala("Hall de Entrada");

    // Nível 1
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita  = criarSala("Biblioteca");

    // Nível 2
    hall->esquerda->esquerda = criarSala("Cozinha");
    hall->esquerda->direita  = criarSala("Quarto Principal");
    hall->direita->esquerda  = criarSala("Sala de Jantar");
    // hall->direita->direita = NULL (Não existe caminho para a direita na Biblioteca)

    // Nível 3
    hall->esquerda->esquerda->esquerda = criarSala("Dispensa"); // Folha
    // Cozinha -> Direita = NULL
    
    // Quarto Principal -> Esquerda
    hall->esquerda->direita->esquerda  = criarSala("Banheiro"); // Folha

    // Sala de Jantar -> Direita
    hall->direita->esquerda->direita  = criarSala("Jardim de Inverno"); // Folha
    
    // --- INÍCIO DA EXPLORAÇÃO ---
    printf("\nBem-vindo ao Detective Quest! Sua investigação começa no Hall de Entrada.\n");
    
    // Começa a exploração a partir do Hall
    explorarSalas(hall);
    
    // Boas Práticas: Libera a memória alocada dinamicamente
    liberarMapa(hall);

    return 0;
}