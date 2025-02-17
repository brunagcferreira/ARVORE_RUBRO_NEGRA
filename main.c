#include <stdio.h>
#include <stdlib.h>
#include "rb.h"
#include "rb.c"

int main() {

    int loop = 1;
	arvore a;
	int opcao;
	inicializar(&a);

	while(loop) {
		scanf("%d", &opcao);

		switch(opcao) {
				int valor;
                //1. altura de pretos
				case 1:
						printf("%d\n", altura(a));
						break;
                //2. add elemento
				case 2:
                        scanf("%d", &valor);
						adicionar(valor, &a);
						break;
                //3. maior elemento
				case 3:
						printf("%d\n", maior_elemento(a));
						break;
				//4. menor elemento
                case 4:
						printf("%d\n", menor_elemento(a));
						break;
				//5. pre order
                case 5:
						pre_order(a);
						printf("\n");
						break;
				//in order
                case 6:
						in_order(a);
						printf("\n");
						break;
				//pos order
                case 7:
						pos_order(a);
						printf("\n");
						break;
				//8. remover
                case 8:
						scanf("%d", &valor);
						//remover(valor, &a);
						break;
				//9. imprimir
                case 9:
						imprimir(a);
						printf("\n");
						break;
				//encerrar
                case 99:
						loop = 0;
                        break;
                default:
                    printf("Opcao Invalida");
                    break;
		}
	}
}