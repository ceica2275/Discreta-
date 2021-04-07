#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

struct par{
	int x, y;
	struct par *prox;
};
typedef struct par parOrdenado;

struct elemento{
	int valor;
	struct elemento * prox; 
};
typedef struct elemento Elemento;

struct listaC{
	Elemento *head;
	int tam;
};
typedef struct listaC ListaC;

struct listaR{
	parOrdenado *head;
	int tam;
};
typedef struct listaR ListaR;

ListaC * criarlistaC(){
	ListaC * l = (ListaC*)malloc(sizeof(ListaC));
	l->tam=0;
	l->head = NULL;
	return l;
}

ListaR * criarlistaR(){
	ListaR * l = (ListaR*)malloc(sizeof(ListaR));
	l->tam=0;
	l->head = NULL;
	return l;
}

void appendR (ListaR *l, int x, int y){
	parOrdenado *aux = l->head;
	l->tam++;
	if(aux==NULL){
		parOrdenado *novo = (parOrdenado *)malloc(sizeof(parOrdenado));
		novo->x = x;
		novo->y = y;
		novo->prox = NULL;
		l->head = novo;
	}
	else{
		while(aux->prox!=NULL){
			aux = aux->prox;
		}
		parOrdenado *novo = (parOrdenado *)malloc(sizeof(parOrdenado));
		novo->x = x;
		novo->y = y;
		novo->prox = NULL;
		aux->prox = novo;
	}
}

void appendC (ListaC *l, int v){
	Elemento *aux = l->head;
	l->tam++;
	if(aux==NULL){
		Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
		novo->valor = v;
		novo->prox = NULL;
		l->head = novo;
	}
	else{
		while(aux->prox!=NULL){
			aux = aux->prox;
		}
		Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
		novo->valor = v;
		novo->prox = NULL;
		aux->prox = novo;
	}
}

bool buscar(ListaC *l, int valor){
	Elemento *aux = l->head;
	if(l->head!=NULL){
		while(aux!=NULL){
			if(aux->valor==valor){ 
				return true;
			}
			aux=aux->prox;
		}
		return false;
	}
	return false;	
}

bool buscarPar(ListaR *l, int x, int y){
	parOrdenado *aux = l->head;
	if(l->head!=NULL){
		while(aux!=NULL){
			if(aux->x==x && aux->y==y){ 
				return true;
			}
			aux=aux->prox;
		}
		return false;
	}
	return false;	
}

void imprimir (ListaC *l){
	Elemento *aux = l->head;
	do{
		printf("  %d   ", aux->valor);
		aux = aux->prox;
	}while(aux!=NULL);
}

void imprimir (ListaR *l){
	parOrdenado *aux = l->head;
	do{
		printf("\n x: %d   y:%d  ", aux->x, aux->y);
		aux = aux->prox;
	}while(aux!=NULL);
}

int reflexiva (ListaR *relacao, ListaC *conjuntoA, FILE *arq){
	Elemento *aux = conjuntoA->head;
	int status=1;
	while(aux!=NULL){
		if(!buscarPar(relacao, aux->valor, aux->valor)){
			status = 0;
		}
		aux = aux->prox;
	}
	if(status==1){
		fprintf(arq, "\n\n1. Reflexiva: V", "r");
		return 1;
	}
	else{
		fprintf(arq, "\n\n1. Reflexiva: F", "r");
		aux = conjuntoA->head;
		while(aux!=NULL){
			if(!buscarPar(relacao, aux->valor, aux->valor)){
				fprintf(arq, " \nO par (%d, %d) não pertence a relação", aux->valor, aux->valor );
			}
			aux = aux->prox;
		}
		return 0;
	}
}

int irreflexiva (ListaR *relacao, ListaC *conjuntoA, FILE *arq){
	Elemento *aux = conjuntoA->head;
	int status=1;
	while(aux!=NULL){
		if(buscarPar(relacao, aux->valor, aux->valor)){
			status = 0;
		}
		aux = aux->prox;
	}
	if(status==1){
		fprintf(arq, "\n\n2. Irreflexiva: V", "r");
		return 1;
	}
	else{
		fprintf(arq, "\n\n2. Irreflexiva: F\n", "r");
		aux = conjuntoA->head;
		while(aux!=NULL){
			if(buscarPar(relacao, aux->valor, aux->valor)){
				fprintf(arq, " O par (%d, %d) pertence a relação\n", aux->valor, aux->valor );
				
			}
			aux = aux->prox;
		}
	}
}

int simetrica (ListaR *relacao, FILE *arq){
	parOrdenado *aux = relacao->head;
	int status=1;
	
	while(aux!=NULL){
		if(!(buscarPar(relacao, aux->x, aux->y) && buscarPar(relacao, aux->y, aux->x))){
			status = 0;
		}
		aux = aux->prox;
	}
	if(status==1){
		fprintf(arq, "\n\n3. Simétrica: V", "r");
		fprintf(arq, "\n\n4. Assimétrica: F", "r");
		return 1;
	}
	else{
		fprintf(arq, "\n\n3. Simétrica: F ", "r");

		aux = relacao->head;
		while(aux!=NULL){
			if(!(buscarPar(relacao, aux->x, aux->y) & buscarPar(relacao, aux->y, aux->x))){
				fprintf(arq, "\nO par (%d, %d) pertence a relação, mas (%d, %d) não pertence a relação",
				aux->x, aux->y, aux->y, aux->x);
					
			}
			aux = aux->prox;
		}
		fprintf(arq, "\n\n4. Assimétrica: V", "r");
		return 0;
	}
}

int transitiva (ListaR *relacao, FILE *arq){
	parOrdenado *aux1 = relacao->head;
	parOrdenado *aux2;
	int status = 1;
	
	while(aux1!=NULL){
		aux2 = relacao->head;
		while(aux2!=NULL){
			if(aux1->y==aux2->x){
				if(!buscarPar(relacao, aux1->x, aux2->y)){
					status=0;
				}
			}
			aux2 = aux2->prox;
		}
		aux1 = aux1->prox;
	}
	if(status==1){
		fprintf(arq, "\n\n6. Transitiva: V", "r");
		return 1;
	}
	else{
		fprintf(arq, "\n\n6. Transitiva: F", "r");
		aux1 = relacao->head;
		while(aux1!=NULL){
			aux2 = relacao->head;
			while(aux2!=NULL){
				if(aux1->y==aux2->x){
					if(!buscarPar(relacao, aux1->x, aux2->y)){
						fprintf(arq, "\nOs pares (%d, %d) e (%d, %d) pertencem a relação, mas o par (%d, %d) não pertence a relação.",
						 aux1->x, aux1->y, aux2->x, aux2->y, aux1->x, aux2->y);
					}
				}
				aux2 = aux2->prox;
			}
			aux1 = aux1->prox;
		}
		return 0;
	}
}

int anti_simetrica(ListaR *relacao, FILE *arq){
	parOrdenado *aux = relacao->head;
	int status=1;
	
	while(aux!=NULL){
		if(aux->x!=aux->y){
			if((buscarPar(relacao, aux->x, aux->y) && buscarPar(relacao, aux->y, aux->x))){
				status = 0;
			}
		}	
		aux = aux->prox;
	}
	if(status==1){
		fprintf(arq, "\n\n5. Anti-simétrica: V", "r");
		return 1;
	}
	else{
		fprintf(arq, "\n\n5. Anti-simétrica: F \n", "r");
		aux = relacao->head;
		ListaR *lc = criarlistaR();
		while(aux!=NULL){
			if(aux->x!=aux->y){
				int par1 = buscarPar(relacao, aux->x, aux->y);
				int par2 = buscarPar(relacao, aux->y, aux->x);
				if(par1 && par2){
					if(!buscarPar(lc, aux->y, aux->x)){
						appendR(lc, aux->x, aux->y);
					}	
				}
			}
			aux = aux->prox;
		}
		parOrdenado *x = lc->head;
		while(x!=NULL){
			fprintf(arq, " (%d, %d) e (%d, %d); ", x->x, x->y, x->y, x->x);
			x = x->prox;
		}
		return 0;	
	}
}

void fechoSimetrico (ListaR *l, int v, FILE *arq){
	fprintf(arq, "\n\nFecho Simétrico: {", "r");
	if(v==1){
		parOrdenado *aux = l->head;
		while(aux!=NULL){
			fprintf(arq, " (%d, %d) ", aux->x, aux->y);
			aux = aux->prox;
		}
	}
	else{
		ListaR *lc = criarlistaR();
		parOrdenado *aux = l->head;
		while(aux!=NULL){
			if(aux->x!=aux->y){
				int par1 = buscarPar(l, aux->x, aux->y);
				int par2 = buscarPar(l, aux->y, aux->x);
				if(par1 && !par2){
					appendR(lc, aux->y, aux->x);
				}
			}
			aux = aux->prox;
		}
		
		aux = l->head;
		while(aux!=NULL){
			fprintf(arq, " (%d, %d) ", aux->x, aux->y);
			aux = aux->prox;
		}
		
		aux = lc->head;
		while(aux!=NULL){
			fprintf(arq, " (%d, %d) ", aux->x, aux->y);
			aux = aux->prox;
		}
		fprintf(arq, " } ", "r");
	}
}

void fechoReflexivo(ListaR *l, int v, ListaC *conjuntoA, FILE *arq){
	fprintf(arq, "\n\nFecho Reflexivo: {", "r");
	if(v==1){
		parOrdenado *aux = l->head;
		while(aux!=NULL){
			fprintf(arq, " (%d, %d)  ", aux->x, aux->y);
			aux = aux->prox;
		}
	}
	else{
		ListaR *Laux = criarlistaR();
		Elemento *aux = conjuntoA->head;
		while(aux!=NULL){
			if(!buscarPar(l, aux->valor, aux->valor)){
				appendR(Laux, aux->valor, aux->valor);
			}
			aux = aux->prox;
		}
		parOrdenado *aux2 = l->head;
		while(aux2!=NULL){
			fprintf(arq, " (%d, %d) ", aux2->x, aux2->y);
			aux2 = aux2->prox;
		}
		
		aux2 = Laux->head;
		while(aux2!=NULL){
			fprintf(arq, " (%d, %d) ", aux2->x, aux2->y);
			aux2 = aux2->prox;
		}
		fprintf(arq, " } ", "r");
	}
}

int verTrans (ListaR *l){
	parOrdenado *aux1 = l->head;
	parOrdenado *aux2;
	int status = 1;
	
	while(aux1!=NULL){
		aux2 = l->head;
		while(aux2!=NULL){
			if(aux1->y==aux2->x){
				if(!buscarPar(l, aux1->x, aux2->y)){
					status=0;
				}
			}
			aux2 = aux2->prox;
		}
		aux1 = aux1->prox;
	}
	if(status==1){
		return 1;
	}
	else{
		return 0;
	}
}

void fechoTransitivo(ListaR *l, int v, FILE *arq){
	
		if(v==1){
			fprintf(arq, "\n\nFecho Transitivo: {", "r");
			ListaR *lc = criarlistaR();
			parOrdenado *aux = l->head;
			while(aux!=NULL){
				if(!buscarPar(lc, aux->x, aux->y)){
					appendR(lc, aux->x, aux->y);
				}
				aux = aux->prox;
			}
			
			aux = lc->head;
			while(aux!=NULL){
				fprintf(arq, " (%d, %d) ", aux->x, aux->y);
				aux = aux->prox;
			}
		}
		else{
			parOrdenado *aux1 = l->head;
			parOrdenado *aux2;
			if(aux1!=NULL){
				parOrdenado *aux = l->head;
				ListaR *x = criarlistaR();
				while(aux!=NULL){
					appendR(x, aux->x, aux->y);
					aux = aux->prox;
				}
				
				while(aux1!=NULL){
					aux2 = l->head;
					while(aux2!=NULL){
						if(aux1->y==aux2->x){
							if(!buscarPar(l, aux1->x, aux2->y)){
								appendR(x, aux1->x, aux2->y);
							}
						}
						aux2 = aux2->prox;
					}
					aux1 = aux1->prox;
				}
				
				v = verTrans(x);
				fechoTransitivo(x, v, arq);
			}		
		}		
}

int menu(FILE * arq){
	ListaC *conjuntoA = criarlistaC();
	ListaR *relacao = criarlistaR();
	int n, x, y, pares;
	printf("\n Oi Lílian!! :)");
	printf("\nInforme a quantidade de elementos que terá o conjunto A: ");
	scanf("%d", &n);
	while(n<=0 || n>=50){
		printf("Quantidade Inválida! Tente novamente: ");
		scanf("%d", &n);
	}
	fprintf(arq, "O conjunto A possui %d elementos\nListagem do elementos: ", n);
	printf("\nAgora liste seus elementos: ");
	for(int i=1; i<=n; i++){
		printf("\nElemento %d: ", i);
		scanf("%d", &x);
		while(buscar(conjuntoA, x)){
			printf("\nEste elemento já existe no conjunto!! Tente novamente: ");
			scanf("%d", &x);
		}
		while(x<=1 || x>=50 ){
			printf("Número fora do intervalo!! Tente novamente: ");
			scanf("%d", &x);
		}
		appendC(conjuntoA, x);
		fprintf(arq, "  %i  ", x);	
	}
	
	fprintf(arq, "\nRelação: ", "r");
	
	system("cls");
	printf("\nConjunto A: ");
	imprimir(conjuntoA);
	printf("\nInforme quantos pares terá a relação: ");
	scanf("%d", &pares);
	printf("\nListe os pares da relação.  ");
	for(int i=1; i<=pares; i++){
		printf("\nPar %d ", i);
		printf("\nValor de x: ");
		scanf("%d", &x);
		while(!buscar(conjuntoA, x)){
			printf("\nInforme um x que pertença ao conjunto A: ");
			scanf("%d", &x);
		}
		printf("Valor de y: ");
		scanf("%d", &y);
		while(!buscar(conjuntoA, y)){
			printf("\nInforme um y que pertença ao conjunto A: ");
			scanf("%d", &y);
		}
		while(buscarPar(relacao, x, y)){
			printf("\nEste par já pertence a relação! Tente novamente.");
			printf("\nValor de x: ");
			scanf("%d", &x);
			printf("\nValor de y: ");
			scanf("%d", &y);
		}
		appendR(relacao, x, y);
		fprintf(arq, "\n(%d, %d)", x, y);
	}
	fprintf(arq, "\n\nPROPRIEDADES: ", "r");	
	int r = reflexiva(relacao, conjuntoA, arq);
	irreflexiva(relacao, conjuntoA, arq);
	int s = simetrica(relacao, arq);
	int as = anti_simetrica(relacao, arq);
	int t = transitiva(relacao, arq);
	
	if(r==1 && s==1 && t==1){
		fprintf(arq, " \n\n->Relação de Equivalência: V", "r");
	}
	else{
		fprintf(arq, " \n\n->Relação de Equivalência: F", "r");
	}
	
	if(r==1 && as==1 && t==1){
		fprintf(arq, "\n\n->Relação de Ordem Parcial: V", "r");
	}
	else{
		fprintf(arq, "\n\n->Relação de Ordem Parcial: F", "r");
	}
	
	fechoReflexivo(relacao, r, conjuntoA, arq);
	fechoSimetrico(relacao, s, arq);
	fechoTransitivo(relacao, t, arq);
	fprintf(arq, " } ", "r");
	printf("\n\nAgora, confere lá o arquivo. <3");
} 


int main (){
	setlocale(LC_ALL, "PORTUGUESE");
	FILE * arq;
	arq = fopen("TrabalhoDiscreta.txt", "w");
	menu(arq);
}
