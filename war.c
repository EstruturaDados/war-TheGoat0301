#include <locale.h>
#include <stdio.h>
#include <string.h>

// Definição de constante para quantidade de territórios
#define TOTAL_TERRITORIOS 5

// ------------------------------
// Estrutura que representa um território
// ------------------------------
struct Territorio {
  char nome[30]; // Nome do território
  char cor[20];  // Cor do exército
  int tropas;    // Número de tropas
};

// Função para limpar o buffer de entrada
void limparBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

int main() {
  setlocale(LC_ALL, "Portuguese_Brazil");

  struct Territorio territorios[TOTAL_TERRITORIOS];

  printf("==== Cadastro de Territórios ====\n\n");

  for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
    printf("Território %d:\n", i + 1);

    // Leitura do nome com espaços
    printf("Digite o nome do território: ");
    fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
    territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // Remove \n

    // Leitura da cor com espaços
    printf("Digite a cor do exército: ");
    fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
    territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

    // Leitura da quantidade de tropas
    printf("Digite a quantidade de tropas: ");
    scanf("%d", &territorios[i].tropas);
    limparBuffer(); // Limpa \n que ficou no buffer

    printf("----------------------------\n");
  }

  printf("\n==== Territórios Registrados ====\n\n");

  for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
    printf("Território %d:\n", i + 1);
    printf("Nome: %s\n", territorios[i].nome);
    printf("Cor do exército: %s\n", territorios[i].cor);
    printf("Tropas: %d\n", territorios[i].tropas);
    printf("----------------------------\n");
  }

  return 0;
}
