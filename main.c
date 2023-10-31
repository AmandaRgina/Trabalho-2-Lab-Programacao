#include <stdio.h>
#include <stdlib.h>

struct Node {
  int valor;
  struct Node *proximo;
};

struct EstruturaAuxiliar {
  int tamanhoAtual;
  int tamanhoTotal;
  struct Node *numeros;
};

struct EstruturaPrincipal {
  struct EstruturaAuxiliar *auxiliares;
  int tamanhoTotal;
};

struct EstruturaAuxiliar criarEstruturaAuxiliar(int tamanhoTotal) {
  struct EstruturaAuxiliar auxiliar;
  auxiliar.tamanhoAtual = 0;
  auxiliar.tamanhoTotal = tamanhoTotal;
  auxiliar.numeros = NULL;
  return auxiliar;
}

int inserirNumero(struct EstruturaAuxiliar *auxiliar, int numero) {
  if (auxiliar->tamanhoAtual < auxiliar->tamanhoTotal) {
    struct Node *novoNumero = (struct Node *)malloc(sizeof(struct Node));
    novoNumero->valor = numero;
    novoNumero->proximo = auxiliar->numeros;
    auxiliar->numeros = novoNumero;
    auxiliar->tamanhoAtual++;
    return 1;
  }
  return 0;
}

void listarNumeros(struct EstruturaAuxiliar auxiliar) {
  struct Node *atual = auxiliar.numeros;
  while (atual != NULL) {
    printf("%d ", atual->valor);
    atual = atual->proximo;
  }
}

void listarTodosNumeros(struct EstruturaPrincipal estruturaPrincipal) {
  for (int i = 0; i < estruturaPrincipal.tamanhoTotal; i++) {
    printf("Posição %d (%d/%d): ", i + 1,
           estruturaPrincipal.auxiliares[i].tamanhoAtual,
           estruturaPrincipal.auxiliares[i].tamanhoTotal);
    listarNumeros(estruturaPrincipal.auxiliares[i]);
    printf("\n");
  }
}

void ordenarNumeros(struct EstruturaAuxiliar *auxiliar) {
  int trocou;
  struct Node *atual;
  struct Node *proximo = NULL;

  do {
    trocou = 0;
    atual = auxiliar->numeros;

    while (atual->proximo != proximo) {
      if (atual->valor > atual->proximo->valor) {
        int temp = atual->valor;
        atual->valor = atual->proximo->valor;
        atual->proximo->valor = temp;
        trocou = 1;
      }
      atual = atual->proximo;
    }
    proximo = atual;
  } while (trocou);
}

void listarNumerosOrdenados(struct EstruturaAuxiliar auxiliar) {
  struct EstruturaAuxiliar auxiliarOrdenada = auxiliar;
  ordenarNumeros(&auxiliarOrdenada);
  listarNumeros(auxiliarOrdenada);
}

void excluirNumero(struct EstruturaAuxiliar *auxiliar, int numero) {
  struct Node *atual = auxiliar->numeros;
  struct Node *anterior = NULL;

  while (atual != NULL) {
    if (atual->valor == numero) {
      if (anterior == NULL) {
        auxiliar->numeros = atual->proximo;
      } else {
        anterior->proximo = atual->proximo;
      }
      free(atual);
      auxiliar->tamanhoAtual--;
      return;
    }
    anterior = atual;
    atual = atual->proximo;
  }
}

void aumentarTamanho(struct EstruturaAuxiliar *auxiliar, int tamanhoExtra) {
  auxiliar->tamanhoTotal += tamanhoExtra;
}

int main() {
  int opcao;
  struct EstruturaPrincipal estruturaPrincipal;
  estruturaPrincipal.tamanhoTotal = 10;
  estruturaPrincipal.auxiliares = (struct EstruturaAuxiliar *)malloc(
      estruturaPrincipal.tamanhoTotal * sizeof(struct EstruturaAuxiliar));

  for (int i = 0; i < estruturaPrincipal.tamanhoTotal; i++) {
    estruturaPrincipal.auxiliares[i] = criarEstruturaAuxiliar(0);
  }

  while (1) {
    printf("\nOpções:\n");
    printf("1. Inserir elemento\n");
    printf("2. Listar números das estruturas\n");
    printf("3. Listar números ordenados em uma estrutura\n");
    printf("4. Listar todos os números ordenados\n");
    printf("5. Excluir um elemento\n");
    printf("6. Aumentar o tamanho de uma estrutura auxiliar\n");
    printf("7. Sair\n");

    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
      int posicao, numero;
      printf("Informe a posição e o número: ");
      scanf("%d %d", &posicao, &numero);
      if (posicao >= 1 && posicao <= estruturaPrincipal.tamanhoTotal) {
        if (inserirNumero(&(estruturaPrincipal.auxiliares[posicao - 1]),
                          numero) == 0) {
          printf("Não há mais espaço para inserir números nesta estrutura.\n");
        }
      } else {
        printf("Posição inválida.\n");
      }
    } else if (opcao == 2) {
      listarTodosNumeros(estruturaPrincipal);
    } else if (opcao == 3) {
      int posicao;
      printf("Informe a posição: ");
      scanf("%d", &posicao);
      if (posicao >= 1 && posicao <= estruturaPrincipal.tamanhoTotal) {
        printf("Números ordenados na posição %d: ", posicao);
        listarNumerosOrdenados(estruturaPrincipal.auxiliares[posicao - 1]);
        printf("\n");
      } else {
        printf("Posição inválida.\n");
      }
    } else if (opcao == 4) {

      printf("Todos os números ordenados: ");
      for (int i = 0; i < estruturaPrincipal.tamanhoTotal; i++) {
        listarNumerosOrdenados(estruturaPrincipal.auxiliares[i]);
      }
      printf("\n");
    } else if (opcao == 5) {
      int posicao, numero;
      printf("Informe a posição e o número a ser excluído: ");
      scanf("%d %d", &posicao, &numero);
      if (posicao >= 1 && posicao <= estruturaPrincipal.tamanhoTotal) {
        excluirNumero(&(estruturaPrincipal.auxiliares[posicao - 1]), numero);
      } else {
        printf("Posição inválida.\n");
      }
    } else if (opcao == 6) {
      int posicao, tamanhoExtra;
      printf("Informe a posição e o tamanho extra: ");
      scanf("%d %d", &posicao, &tamanhoExtra);
      if (posicao >= 1 && posicao <= estruturaPrincipal.tamanhoTotal) {
        aumentarTamanho(&(estruturaPrincipal.auxiliares[posicao - 1]),
                        tamanhoExtra);
      } else {
        printf("Posição inválida.\n");
      }
    } else if (opcao == 7) {

      break;
    } else {
      printf("Opção inválida. Tente novamente.\n");
    }
  }

  for (int i = 0; i < estruturaPrincipal.tamanhoTotal; i++) {
    struct Node *atual = estruturaPrincipal.auxiliares[i].numeros;
    while (atual != NULL) {
      struct Node *proximo = atual->proximo;
      free(atual);
      atual = proximo;
    }
  }
  free(estruturaPrincipal.auxiliares);

  return 0;
}