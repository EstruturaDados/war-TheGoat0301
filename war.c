#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 100
#define MAX_MISSOES 5

// Representa um território do jogo
struct Territorio {
  char nome[30];
  char cor[10];
  int tropas;
};

// Limpa o buffer de entrada
void limparBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Exibe os territórios
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

// Cadastra os territórios
void cadastrarTerritorios(struct Territorio *mapa, int total) {
  for (int i = 0; i < total; i++) {
    printf("Território %d:\n", i + 1);
    printf("Digite o nome do território: ");
    fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
    mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

    printf("Digite a cor do exército: ");
    fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
    mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

    printf("Digite a quantidade de tropas: ");
    scanf("%d", &mapa[i].tropas);
    limparBuffer();

    printf("----------------------------\n");
  }
}

// Atribui uma missão ao jogador
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
  int indice = rand() % totalMissoes;
  strcpy(destino, missoes[indice]);
}

// Exibe a missão do jogador
void exibirMissao(char *missao) {
  printf("\n==== Sua Missão ====\n");
  printf("%s\n", missao);
  printf("====================\n");
}

// Verifica se a missão foi cumprida
int verificarMissao(char *missao, struct Territorio *mapa, int total) {
  // Exemplo de lógica simples:
  if (strcmp(missao, "Conquistar 3 territórios com mais de 5 tropas") == 0) {
    int count = 0;
    for (int i = 0; i < total; i++) {
      if (mapa[i].tropas > 5)
        count++;
    }
    return count >= 3;
  } else if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
    for (int i = 0; i < total; i++) {
      if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0)
        return 0;
    }
    return 1;
  } else if (strcmp(missao, "Controlar todos os territórios") == 0) {
    char corInicial[10];
    strcpy(corInicial, mapa[0].cor);
    for (int i = 1; i < total; i++) {
      if (strcmp(mapa[i].cor, corInicial) != 0)
        return 0;
    }
    return 1;
  } else if (strcmp(missao, "Ter pelo menos 20 tropas no total") == 0) {
    int soma = 0;
    for (int i = 0; i < total; i++) {
      soma += mapa[i].tropas;
    }
    return soma >= 20;
  } else if (strcmp(missao, "Controlar pelo menos 2 territórios") == 0) {
    char corDoJogador[10];
    strcpy(corDoJogador, mapa[0].cor); // Simplificação: assume jogador 1
    int count = 0;
    for (int i = 0; i < total; i++) {
      if (strcmp(mapa[i].cor, corDoJogador) == 0)
        count++;
    }
    return count >= 2;
  }

  return 0;
}

// Simula um ataque
void atacar(struct Territorio *atacante, struct Territorio *defensor) {
  if (strcmp(atacante->cor, defensor->cor) == 0) {
    printf("\nErro: Você não pode atacar um território da mesma cor!\n");
    return;
  }

  if (atacante->tropas < 2) {
    printf("\nErro: O território atacante precisa de pelo menos 2 tropas para "
           "atacar!\n");
    return;
  }

  printf("\n== Iniciando Ataque ==\n");

  int dadoAtacante = rand() % 6 + 1;
  int dadoDefensor = rand() % 6 + 1;

  printf("Dado do atacante: %d\n", dadoAtacante);
  printf("Dado do defensor: %d\n", dadoDefensor);

  if (dadoAtacante > dadoDefensor) {
    printf("Resultado: Atacante venceu!\n");

    int tropasTransferidas = defensor->tropas / 2;
    defensor->tropas = tropasTransferidas;
    strcpy(defensor->cor, atacante->cor);

    atacante->tropas -= 1;

    printf("O território %s foi conquistado!\n", defensor->nome);
  } else {
    printf("Resultado: Defensor resistiu!\n");
    atacante->tropas -= 1;
  }
}

// Libera memória alocada
void liberarMemoria(struct Territorio *mapa, char *missaoJogador) {
  free(mapa);
  free(missaoJogador);
}

// Função principal
int main() {
  setlocale(LC_ALL, "Portuguese_Brazil");
  srand(time(NULL));

  // Vetor de missões
  char *missoes[MAX_MISSOES] = {"Conquistar 3 territórios com mais de 5 tropas",
                                "Eliminar todas as tropas da cor vermelha",
                                "Controlar todos os territórios",
                                "Ter pelo menos 20 tropas no total",
                                "Controlar pelo menos 2 territórios"};

  int total;
  printf("Digite o número de territórios: ");
  scanf("%d", &total);
  limparBuffer();

  struct Territorio *mapa =
      (struct Territorio *)calloc(total, sizeof(struct Territorio));
  if (mapa == NULL) {
    printf("Erro ao alocar memória.\n");
    return 1;
  }

  // Aloca memória para missão do jogador
  char *missaoJogador = (char *)malloc(200 * sizeof(char));
  if (missaoJogador == NULL) {
    printf("Erro ao alocar memória para missão.\n");
    free(mapa);
    return 1;
  }

  printf("\n==== Cadastro de Territórios ====\n\n");
  cadastrarTerritorios(mapa, total);

  // Atribui missão ao jogador
  atribuirMissao(missaoJogador, missoes, MAX_MISSOES);
  exibirMissao(missaoJogador);

  int opcao;

  // Loop do jogo
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

      printf("\n== Territórios disponíveis ==\n");
      for (int i = 0; i < total; i++) {
        printf("%d - %s (%s, %d tropas)\n", i + 1, mapa[i].nome, mapa[i].cor,
               mapa[i].tropas);
      }

      printf("\nDigite o número do território atacante (1 a %d): ", total);
      scanf("%d", &idxAtacante);
      limparBuffer();

      printf("Digite o número do território defensor (1 a %d): ", total);
      scanf("%d", &idxDefensor);
      limparBuffer();

      if (idxAtacante < 1 || idxAtacante > total || idxDefensor < 1 ||
          idxDefensor > total) {
        printf("Índices inválidos. Tente novamente.\n");
        continue;
      }

      atacar(&mapa[idxAtacante - 1], &mapa[idxDefensor - 1]);

      // Verificação silenciosa da missão após cada ataque
      if (verificarMissao(missaoJogador, mapa, total)) {
        printf("\n🎉 Parabéns! Você cumpriu sua missão:\n");
        printf("🔒 %s\n", missaoJogador);
        printf("🏆 Você venceu o jogo!\n");
        break;
      }

    } else if (opcao == 2) {
      exibirTerritorios(mapa, total);
    }

  } while (opcao != 0);

  liberarMemoria(mapa, missaoJogador);

  printf("Programa finalizado.\n");

  return 0;
}