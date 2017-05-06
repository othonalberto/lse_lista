#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "listas.h"
/*

typedef int TipoChave;
typedef int TipoValor;
struct TipoListaSimples
{
  TipoChave chave;
  TipoValor valorQualquer;
  struct TipoListaSimples *prox;
};
typedef struct TipoListaSimples TipoListaSimples;

*/

TipoListaSimples *insereInicioListaSimples(TipoListaSimples **prim, TipoChave chave, TipoValor valor){
	assert(prim);

	TipoListaSimples *aux = malloc(sizeof(TipoListaSimples));
	if (aux == NULL) return NULL;

	aux->chave = chave;
	aux->valorQualquer = valor;
	aux->prox = *prim;

	*prim = aux;

	return aux;
}

void atualizaValor(TipoListaSimples *prim, TipoValor novoValor){
	if(prim == NULL) return;

	prim->valorQualquer = novoValor;
}

void removePrimeiroNo(TipoListaSimples **prim){
	assert(prim);

	if(*prim == NULL) return;

	TipoListaSimples *aux = *prim;
	(*prim) = (*prim)->prox;
	free(aux);
}

TipoListaSimples *pesquisaNo(TipoListaSimples *prim, TipoChave chave){
	while(prim != NULL){
		if(prim->chave == chave)
			return prim;
		else
			prim = prim->prox;
	}

	return NULL;
}

TipoListaSimples *insereFimListaSimples(TipoListaSimples **prim, TipoChave chave, TipoValor valor){
	assert(prim);

	TipoListaSimples *aux = *prim; //para percorrer

	TipoListaSimples *novo = malloc(sizeof(TipoListaSimples)); //novo nó a ser inserido
	novo->chave = chave;
	novo->valorQualquer = valor;
	novo->prox = NULL;
	
	if(aux == NULL){
		*prim = novo;

	} else{

		while(aux->prox != NULL){ //percorre até o último nó
			aux = aux->prox;
		}

		aux->prox = novo;
	}

	return novo;
}

void removeUltimoNo(TipoListaSimples **prim){
	assert(prim);

	if(*prim == NULL) return;

	TipoListaSimples *aux = *prim;

	while((aux->prox)->prox != NULL) 
		aux = aux->prox;

	//no momento, estamos no penúltimo elemento da lista

	free((aux->prox)->prox);
	aux->prox = NULL;
}

void removeNo(TipoListaSimples **prim, TipoChave chave){
	assert(prim);

	TipoListaSimples *aux = *prim;
	TipoListaSimples *aux2 = (*prim)->prox;

	//primeiro elemento
	if(aux->chave == chave){
		*prim = aux->prox;
		free(aux);
		return;
	}

	//do segundo para frente
	while(aux2->prox != NULL){
		if(aux2->chave == chave){
			aux->prox = aux2->prox;
			free(aux2);
			return; //nó removido
		} else{
			aux = aux->prox;
			aux2 = aux2->prox;
		}
	}
}

void liberaNos(TipoListaSimples **prim){
	assert(prim);

	while((*prim)->prox != NULL){
		liberaNos(&(*prim)->prox);
		free((*prim)->prox);
	}

	*prim = NULL;
}

TipoListaSimples *copiaListas(TipoListaSimples *prim){
	TipoListaSimples *lista2 = NULL;


	while((prim) != NULL){
		insereFimListaSimples(&lista2, (prim)->chave, (prim)->valorQualquer);
		prim = prim->prox;
	}

	return lista2;
}

TipoListaSimples *intersecaoListas(TipoListaSimples *prim1, TipoListaSimples *prim2){
	TipoListaSimples *aux = prim1;
	TipoListaSimples *aux2 = prim2;
	TipoListaSimples *lista3 = NULL;

	while(aux2 != NULL){
		while(aux != NULL){
			if(aux->chave == aux2->chave){
				insereInicioListaSimples(&lista3, aux->valorQualquer, aux->chave);
				aux = aux->prox;
			} else{
				aux = aux->prox;
			}
		}

		aux = prim2;
		aux2 = aux2->prox;
	}

	return lista3;
}

void insereRemove(TipoListaSimples **primLista1, TipoListaSimples **primLista2){
	assert(primLista1 && primLista2);

	TipoListaSimples *aux = *primLista2;


	if(aux == NULL) return; //lista vazia, nada a se fazer

	if((aux)->prox == NULL){ //só tem um nó
		insereFimListaSimples(primLista1, aux->chave, aux->valorQualquer);
		free(aux);
		*primLista2 = NULL;
	} else{ //mais de um nó
		while((aux)->prox->prox != NULL) //percorre até o penúltimo
			aux = aux->prox; 

		insereFimListaSimples(primLista1, aux->prox->chave, aux->prox->valorQualquer);

		free(aux->prox); //dá free no último
		(aux)->prox = NULL; //o campo prox do agora último é setado para NULL, caracterizando-o como último
	}
}

void transplantaNo(TipoListaSimples **primLista1, TipoListaSimples **primLista2){
	assert(primLista1 && primLista2);

	TipoListaSimples *aux1 = *primLista1;
	TipoListaSimples *aux2 = *primLista2;

	if(aux2 == NULL) return; //lista vazia, nada a fazer

	while(aux1->prox != NULL)
		aux1 = aux1->prox; //percorre até o último nó da lista1

	if((aux2)->prox == NULL){//só tem um nó
		aux1->prox = aux2;
		free(aux2);
		*primLista2 = NULL;
	} else{ //mais de um nó
		while((aux2)->prox->prox != NULL) //percorre até o penúltimo
			aux2 = aux2->prox; 

		aux1->prox = aux2->prox; 
		free(aux2->prox);

		(aux2)->prox = NULL; //o campo prox do agora último é setado para NULL, caracterizando-o como último
	}
}

void mostraInformacoes(TipoListaSimples *p){
	printf("=================================\n");

	if(p == NULL) printf("LISTA VAZIA.\n=================================\n");
	
	while(p != NULL){
		printf("Mora em: %p\nAponta para: %p\nChave: %d\nValor: %d\n", p, p->prox, p->chave, p->valorQualquer);
		printf("=================================\n");
		p = p->prox;
	}
}