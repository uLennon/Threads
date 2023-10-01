
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 10
int numero_escolhido;
int vetor[MAX]={0,1,2,3,4,5,6,7,8,9}; 

typedef struct{
	int inicio;
	int final;
	int thread;
	
}Parametro;

void inicia_thread(pthread_t *,int );
void cria_thread(pthread_t *,int);
void *busca_vetor(void *);
int verifica_tamanho(int );


int main (int argc, char *argv[]){
	
	numero_escolhido = 8;
	int particao = 2;
	pthread_t th[particao];
	cria_thread(th,particao);
	inicia_thread(th,particao);

	return 0;
}

void cria_thread(pthread_t *th, int particao){
	
	Parametro *argumentos[particao];
	int i = 0;
	int inicia = 0;           
	int fim = MAX / particao; 
	int aux = fim;
	
	for(i = 0; i < particao; i++){
	 	argumentos[i] = malloc(sizeof(Parametro));
	 	argumentos[i]->inicio = inicia;
		argumentos[i]->final = fim;
		argumentos[i]->thread = i;
		pthread_create(&th[i], NULL, busca_vetor, argumentos[i]);
		inicia = fim;  
		fim = fim + aux;  
	}
	if(verifica_tamanho(particao) == 0){
	 	argumentos[i-1]->final = MAX;
	}
}

void inicia_thread(pthread_t * th, int particao){
	for(int i = 0; i < particao; i++){
		pthread_join(th[i],NULL);
	}
}

void *busca_vetor(void *argumento){
	Parametro *parametros = (Parametro *)argumento;
	for(int i = parametros->inicio; i < parametros->final; i++){
		if(vetor[i] == numero_escolhido){
			printf("A thread %d achou o numero  %d\n",parametros->thread, vet[i]);
		}
	}
}

int verifica_tamanho(int numero){
	int flag = 0;
	if(numero%2 == 0){
		flag = 1;
	}
	return flag;
}