#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

arvore no_null;

void inicializar(arvore *raiz){
    *raiz = NULL;
    no_null = (arvore)malloc(sizeof(struct no));
    if (no_null == NULL) {
        printf("Falha ao alocar memória para no_null\n");
        exit(EXIT_FAILURE);
    }
    no_null->cor = DUPLO_PRETO;
    no_null->valor = 0;
    no_null->esq = NULL;
    no_null->dir = NULL;
    no_null->pai = NULL;
}

void adicionar (int valor, arvore *raiz){
    //1. inicializar ponteiros
    arvore posicao, pai, novo;
    posicao = *raiz;
    pai = NULL;

    //2. percorer a arvore para encontrar a posição e o pai do novo elemento
    while(posicao != NULL){
        pai = posicao;

        if (posicao->valor >= valor){
            posicao = posicao->esq;
        }else{
            posicao = posicao->dir;
        }
    }

    //3. inicializar o novo elemennto
    novo = (arvore)malloc(sizeof(struct no));
    novo->cor = VERMELHO;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = pai;
    novo->valor = valor;

    //4. att ponteiro do pai, ou da raíz
    if (eh_raiz(novo)){
        *raiz = novo;
    }else{

        if (valor <= pai->valor){
            pai->esq = novo;
        }else{
            pai->dir = novo;
        }

    }

    //5. chamar a função que verifica e realiza correções
    ajustar(raiz, novo);
}

void ajustar(arvore *raiz, arvore elemento){

    while(cor(elemento) == VERMELHO && cor(pai(elemento)) == VERMELHO){

        //caso 1: nó, pai e tio são vermelhos. trazer para baixo a cor  preta do avô
        if(cor(tio(elemento)) == VERMELHO){
            pai(elemento)->cor = PRETO;
            tio(elemento)->cor = PRETO;
            avo(elemento)->cor = VERMELHO;

            elemento = avo(elemento);
            continue;
        }

        //caso 2.a: nó e pai são vermelhos E ambos filhos esquerdos e o tio é preto
        //ROTAÇÃO SIMPLES DIREITA
        if (eh_filho_esquerdo(elemento) && eh_filho_esquerdo(pai(elemento))){
            
            rotacao_simples_direita(raiz, avo(elemento));

            pai(elemento)->cor = PRETO;
            irmao(elemento)->cor = VERMELHO;

            continue;
        }
        //caso 2.b: nó e pai são vermelhos E ambos filhos direitos e o tio é preto
        //ROTAÇÃO SIMPLES ESQUERDA
        if(!eh_filho_esquerdo(elemento) && !eh_filho_esquerdo(pai(elemento))){
            
            rotacao_simples_esquerda(raiz, avo(elemento));

            pai(elemento)->cor = PRETO;
            irmao(elemento)->cor = VERMELHO;

            continue;
            
        }

        //caso 3.a: nó e pai são vermelhos. pai é filho esquerdo. nó é filho direito.
        //ROTAÇÃO DUPLA DIREITA
        if(!eh_filho_esquerdo(elemento) && eh_filho_esquerdo(pai(elemento))){
            
            rotacao_dupla_direita(raiz, avo(elemento));
            elemento->cor = PRETO;
            elemento->dir->cor = VERMELHO;
            elemento->esq->cor = VERMELHO;

            continue;
        }

        //caso 3.b: nó e pai são vermelhos. pai é filho direito. nó é filho esquerdo.
        //ROTAÇÃO DUPLA ESQUERDA
        if(eh_filho_esquerdo(elemento) && !eh_filho_esquerdo(pai(elemento))){

            rotacao_dupla_esquerda(raiz, avo(elemento));

            elemento->cor = PRETO;
            elemento->dir->cor = VERMELHO;
            elemento->esq->cor = VERMELHO;

            continue;

        }
    }
    (*raiz)->cor = PRETO;
}
//correto
void rotacao_simples_direita(arvore *raiz, arvore pivo){
    //inicializar
    arvore p, u, t1;
    p = pivo;
    u = pivo->esq;
    t1 = u->dir;

    //Para fazer a ligação da raiz da sub-árvore resultante com o seu pai, 
    //é preciso saber se o pivo p era um filho esquerdo ou direito
	int posicao_pivo_esq = eh_filho_esquerdo(pivo);

    //att ponteiros
    p->esq = t1;
    if (t1 != NULL){
        t1->pai = p;
    }

    u->dir = p;
    u->pai = p->pai;
    p->pai = u;

    //Se não existir árvore acima de u, u passa a ser a raiz da árvore
    if (eh_raiz(u)){
        *raiz = u;
    }

    //Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante 
    else{
        if(posicao_pivo_esq){
            pai(u)->esq = u;
        }else{
            pai(u)->dir = u;
        }
    }
}

//certo
void rotacao_simples_esquerda(arvore *raiz, arvore pivo){
    //inicializar ponteiros
    arvore p, u, t1;
    p = pivo;
    u = pivo->dir;
    t1 = u->esq;

    int posicao_pivo_esq = eh_filho_esquerdo(pivo);

    //att ponteiros
    p->dir = t1;
    if (t1 != NULL){
        t1->pai = p;
    }

    u->esq = p;
    u->pai = p->pai;
    p->pai = u;

    //amarrar a raiz relativa com o resto da árvore
    if (eh_raiz(u)){
        *raiz = u;
    }else{

        if(posicao_pivo_esq){
            pai(u)->esq = u;
        }else{
            pai(u)->dir = u;
        }
    }
}

void rotacao_dupla_direita(arvore *raiz, arvore pivo){
    //inicializar ponteiros
    arvore p, u, v, t2, t3;
    p = pivo;
    u = pivo->esq;
    v = u->dir;
    t2 = v->esq;
    t3 = v->dir;

    int posicao_pivo_esq = eh_filho_esquerdo(pivo);

    //att ponteiros
    p->esq = t3;
    if (t3 != NULL){
        t3->pai = p;
    }

    u->dir = t2;
    if (t2 != NULL){
        t2->pai = u;
    }

    v->dir = p;
    v->esq = u;

    u->pai = v;
    v->pai = p->pai;
    p->pai = v;

    //amarrar a raiz relativa com o resto da árvore
    if (eh_raiz(v)){
        *raiz = v;
    }else{
        if(posicao_pivo_esq){
            pai(v)->esq = v;
        }else{
            pai(v)->dir = v;
        }
    }
}

void rotacao_dupla_esquerda(arvore *raiz, arvore pivo){
    //inicializar ponteiros
    arvore p, v, u, t2, t3;
    p = pivo;
    u = pivo->dir;
    v = u->esq;
    t2 = v->esq;
    t3 = v->dir;

    int posicao_pivo_esq = eh_filho_esquerdo(pivo);

    //att ponteiros
    u->esq = t3;
    if(t3 != NULL){
        t3->pai = u;
    }

    p->dir = t2;
    if (t2 != NULL){
        t2->pai = p;
    }

    v->dir = u;
    u->pai = v;

    v->esq = p;
    v->pai = p->pai;
    p->pai = v;

    //amarrar a raiz relativa com o resto da árvore
    if(eh_raiz(v)){
        *raiz = v;
    }else{
        if(posicao_pivo_esq){
            pai(v)->esq = v;
        }else{
            pai(v)->dir = v;
        }
    }
}

enum cor cor(arvore elemento){
    if (elemento == NULL){
        return PRETO;
    }
    return elemento->cor;
}

int eh_raiz(arvore elemento){
    return(elemento->pai == NULL);
}

int eh_filho_esquerdo(arvore elemento){
    return (elemento->pai != NULL && elemento == pai(elemento)->esq);
}

arvore irmao(arvore elemento){
    if(eh_filho_esquerdo(elemento)){
        return elemento->pai->dir;
    }
    return elemento->pai->esq;
}

arvore pai(arvore elemento){
    
    return elemento->pai;
}

arvore tio(arvore elemento){
    if(elemento == NULL){
        return NULL;
    }
    return (irmao(pai(elemento)));
}

arvore avo(arvore elemento){
    return elemento->pai->pai;
}

//precisa ser a altura de pretos??
//arrumar para o caso em q a arvore esta vazia
int altura(arvore raiz){
    if (raiz == NULL) return 0;
    
    int altura = 0;
    arvore aux = raiz;
    while (aux != NULL){
        if(aux->cor == PRETO){
            altura++;
        }
        aux = aux->esq;
    }
    return altura;
}

//int maior(int a, int b);

int maior_elemento(arvore raiz){
    if(raiz == NULL){
        return -1;
    }
    if(raiz->dir == NULL){
        return raiz->valor;
    }
    else{
        return maior_elemento(raiz->dir);
    }
}


int menor_elemento(arvore raiz){
    if(raiz == NULL){
        return -1;
    }
    if(raiz->esq == NULL){
        return raiz->valor;
    }
    else{
        return menor_elemento(raiz->esq);
    }
}

void imprimir_elemento(arvore raiz) {
	switch(raiz->cor){
		case PRETO:
			printf("\x1b[30m[%d]\x1b[0m", raiz->valor);
			break;
		case VERMELHO:
			printf("\x1b[31m[%d]\x1b[0m", raiz->valor);
			break;
		case DUPLO_PRETO:
			printf("\x1b[32m[%d]\x1b[0m", raiz->valor);
			break;
	}
}

void imprimir(arvore raiz) {
	printf("(");
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		imprimir(raiz->esq);
		imprimir(raiz->dir);
	}
	printf(")");
}

void pre_order(arvore raiz) {
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		pre_order(raiz->esq);
		pre_order(raiz->dir);
	}
}

void pos_order(arvore raiz) {
	if(raiz != NULL) {
		pos_order(raiz->esq);
		pos_order(raiz->dir);
		imprimir_elemento(raiz);
	}
}

void in_order(arvore raiz) {
	if(raiz != NULL) {
		in_order(raiz->esq);
		imprimir_elemento(raiz);
		in_order(raiz->dir);
	}
}


