#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Representa um território do jogo
// Armazena nome, cor do exército (representando o jogador/dono) e o número de
// tropas
struct Territorio {
  char nome[30];
  char cor[10];
  int tropas;
};

// Função usada após `scanf` para evitar problemas de leitura com `fgets`
void limparBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Cadastra os territórios no início do jogo
// Cada território recebe um nome, cor (dono) e número inicial de tropas
void cadastrarTerritorios(struct Territorio *mapa, int total) {
  for (int i = 0; i < total; i++) {
    printf("Território %d:\n", i + 1);

    printf("Digite o nome do território: ");
    fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
    mapa[i].nome[strcspn(mapa[i].nome, "\n")] =
        '\0'; // Remove o '\n' inserido pelo fgets

    printf("Digite a cor do exército: ");
    fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
    mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0'; // Remove o '\n'

    printf("Digite a quantidade de tropas: ");
    scanf("%d", &mapa[i].tropas);
    limparBuffer(); // Garante que o próximo fgets funcione c

    printf("----------------------------\n");
  }
}

// Exibe todos os territórios
void exibirTerritorios(struct Territorio *mapa, int total) {
  printf("\n==== Territórios Registrados ====\n\n");
  for (int i = 0; i < total; i++) {
    printf("Território %d:\n", i + 1);
    printf("Nome: %s\n", mapa[i].nome);
    printf("Cor do exército: %s\n", mapa[i].cor);
    printf("Tropas: %d\n", mapa[i].tropas);
    printf("----------------------------\n");
  }
}

// Simula um ataque entre dois territórios
// Considera a regra básica: só é possível atacar territórios de cores
// diferentes E o território atacante precisa de no mínimo 2 tropas (1 para
// ficar e pelo menos 1 para atacar)
void atacar(struct Territorio *atacante, struct Territorio *defensor) {
  if (strcmp(atacante->cor, defensor->cor) == 0) {
    // Impede ataque a um território aliado
    printf("\nErro: Você não pode atacar um território da mesma cor!\n");
    return;
  }

  if (atacante->tropas < 2) {
    // Impede ataque com tropas insuficientes
    printf("\nErro: O território atacante precisa de pelo menos 2 tropas para "
           "atacar!\n");
    return;
  }

  printf("\n== Iniciando Ataque ==\n");

  // Simula dados de ataque e defesa com números aleatórios de 1 a 6
  int dadoAtacante = rand() % 6 + 1;
  int dadoDefensor = rand() % 6 + 1;

  printf("Dado do atacante: %d\n", dadoAtacante);
  printf("Dado do defensor: %d\n", dadoDefensor);

  // Define o vencedor com base no valor dos dados
  if (dadoAtacante > dadoDefensor) {
    // Caso o atacante vença:
    printf("Resultado: Atacante venceu!\n");

    // O defensor perde o território — metade de suas tropas são transferidas ao
    // novo dono
    int tropasTransferidas = defensor->tropas / 2;
    defensor->tropas = tropasTransferidas;
    strcpy(defensor->cor, atacante->cor); // Muda o dono do território

    atacante->tropas -= 1; // O atacante perde 1 tropa pela batalha

    printf("O território %s foi conquistado!\n", defensor->nome);
  } else {
    // Caso o defensor vença ou empate, o atacante perde 1 tropa
    printf("Resultado: Defensor resistiu!\n");
    atacante->tropas -= 1;
  }
}

// Libera a memória alocada dinamicamente para o mapa
void liberarMemoria(struct Territorio *mapa) { free(mapa); }

int main() {
  setlocale(
      LC_ALL,
      "Portuguese_Brazil"); // Garante exibição correta de acentos no Windows
  srand(time(NULL)); // Inicializa a geração de números aleatórios com base no
                     // tempo atual

  int total;
  printf("Digite o número de territórios: ");
  scanf("%d", &total);
  limparBuffer();

  // Aloca memória para armazenar os territórios do jogo
  struct Territorio *mapa =
      (struct Territorio *)calloc(total, sizeof(struct Territorio));

  if (mapa == NULL) {
    // Valida se a alocação foi bem-sucedida
    printf("Erro ao alocar memória.\n");
    return 1;
  }

  printf("\n==== Cadastro de Territórios ====\n\n");
  cadastrarTerritorios(mapa, total); // Coleta os dados iniciais

  int opcao;

  // Loop principal do menu do jogo
  do {
    printf("\nMenu:\n");
    printf("1 - Atacar\n");
    printf("2 - Exibir territórios\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    limparBuffer();

    if (opcao == 1) {
      int idxAtacante, idxDefensor;

      // Mostra todos os territórios
      printf("\n== Territórios disponíveis ==\n");
      for (int i = 0; i < total; i++) {
        printf("%d - %s (%s, %d tropas)\n", i + 1, mapa[i].nome, mapa[i].cor,
               mapa[i].tropas);
      }

      // Pede ao jogador para escolher atacante e defensor
      printf("\nDigite o número do território atacante (1 a %d): ", total);
      scanf("%d", &idxAtacante);
      limparBuffer();

      printf("Digite o número do território defensor (1 a %d): ", total);
      scanf("%d", &idxDefensor);
      limparBuffer();

      // Validação dos índices inseridos
      if (idxAtacante < 1 || idxAtacante > total || idxDefensor < 1 ||
          idxDefensor > total) {
        printf("Índices inválidos.\n");
        continue;
      }

      // Realiza o ataque entre os territórios selecionados
      atacar(&mapa[idxAtacante - 1], &mapa[idxDefensor - 1]);
    } else if (opcao == 2) {
      // Exibe todos os territórios
      exibirTerritorios(mapa, total);
    }

  } while (opcao != 0); // Repete até o jogador optar por sair

  liberarMemoria(mapa); // Libera memória alocada ao final

  printf("Programa finalizado.\n");

  return 0;
}
