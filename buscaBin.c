#include <stdio.h>
#define MAX 100

void troca(int* a, int* b)
{
	int aux;
	aux=*a;
	*a=*b;
	*b=aux;
}
int busca_Binaria_Esq(int n, int v[MAX], int x, int ind)
{
	int esq, dir, meio;
	int cont;
	esq=-1;
	dir= n;
	cont=0;
	while(esq < dir -1)
	{
		meio=(esq + dir) / 2;
		if(v[ind] - v[meio] != x)
			esq = meio;
		if(v[ind] - v[meio] == x)
			cont++;	
	}
	return cont;
}
int busca_Binaria_Dir(int n, int v[MAX], int x, int ind)
{
	int esq, dir, meio;
	int cont;
	esq=-1;
	dir= n;
	cont=0;
	while(esq < dir -1)
	{
		meio=(esq + dir) / 2;
		if(v[ind] - v[meio] != x)
			dir = meio;
		if(v[ind] - v[meio] == x)
			cont++;	
	}
	return cont;
}
/*int busca_binaria_R(int esq, int dir, int v[MAX], int x)
{
		int meio;

		if(esq == dir - 1)
			return dir;
		else{
			meio=(esq + dir) / 2;
			if(v[meio] < v[x])
				return busca_binaria_R(meio, dir, v, x);
			else 
				return busca_binaria_R(esq, meio, v, x);
		}
	
}*/
//Heap
void subir(int indice, int h[MAX])
{
	int j, aux;
	if (indice > 0)//Se tem pai
	{
		j = (indice - 1) / 2;//Calcula índice do pai
		if (h[indice] > h[j])//Se é maior do que o pai
		{//Troca elementos
			aux = h[indice]; h[indice] = h[j]; h[j] = aux;
			subir(j, h);
		}
	}
}
void descer(int indice, int h[MAX], int numElementos)
{
	int j, aux;
	j = 2 * indice + 1;
	if (j < numElementos)//Se tem o filho da esquerda
	{
		if (j + 1 < numElementos)//Se tem o filho da direita também
		{//Verifica qual dos dois filhos é maior
			if (h[j + 1] > h[j])
				j++;
		}
		if (h[indice] < h[j])
		{//Troca elementos
			aux = h[indice]; h[indice] = h[j]; h[j] = aux;
			descer(j, h, numElementos);
		}
	}
}

void construirHeap(int h[MAX], int numElementos)
{
	int ultimo, i;
	ultimo = numElementos / 2 - 1;
		for (i = ultimo; i >= 0; i--)
			descer(i, h, numElementos);
}
void inserir(int novaChave, int h[MAX], int* numElementos)
{
	if (*numElementos < MAX)//Ainda há espaço
	{
		h[*numElementos] = novaChave;
		*numElementos = *numElementos + 1;
		subir(*numElementos - 1, h);
	}
		else
			printf("Overflow!\n");
}

int remover(int h[MAX], int* numElementos)
{
	int chave;
	
	if (*numElementos > 0)
	{
		chave = h[0];
		h[0] = h[*numElementos - 1];
		*numElementos = *numElementos - 1;
		descer(0, h, *numElementos);
	}
		else
			printf("Underflow!\n");
	return chave;
}

void heapsort(int vet[MAX], int tam)
{
	int i;
	construirHeap(vet, tam);
	for (i = tam - 1; i > 0; i--)
	{
		troca(&vet[0], &vet[i]);//Troca chaves da posição 0 e i
		tam--;//Decrementa o tamanho do heap
		descer(0, vet, tam);
	}
}

//Complexidade O(n log n)
int contaPares(int* V, int n, int k){
	int cont=0, i, soma;
	int dif, pos;
	
	heapsort(V, n);
	
	for(i=n;i>0;i--){
		
		dif=busca_Binaria_Esq(n, V, k, i);
		pos=busca_Binaria_Dir(n, V, k, i);
		
		soma= dif + pos;
		cont=cont + soma;
	}
	
	return cont;//retorna o contador
}

int main(void)
{
	int r, i, k;
	int vet[MAX];
	int res;
	scanf("%d", &r);//leitura do tamanho
	scanf("%d", &k);//leitura do indice k
	
	for(i=0;i<r;i++){
		scanf("%d", &vet[i]);//leitura dos elementos do vetor
	}
	res=contaPares(vet, r, k);//chama a funçao

	printf("%d", res);//imprime o qu retornou da funçao
	
	return 0;
}
