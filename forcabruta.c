#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int calcularDelta(int** G, int n);
int lerN(char arq[]);
void lerGrafo(int** G, char arq[], int n);
void geraCor(int cor[], int n, int k, long long int a);
int verificaCor(int cor[], int** G, int n);
void escreveResult(int min, int cor, int n, int k, int delta, char* nome);

int main(int argc, char *argv[ ]){
	int k, j;
	char arq[20] = "";
	char pasta[30] = "grafos/";
	
	if(!argv[1])
	{
		printf("Informe o nome do arquivo do Grafo: ");
		scanf("%s", arq);
	}
	else
	{
		strcpy(arq,argv[1]);
	}

	if(!argv[2])
	{
		printf("Informe o valor de K: ");
		scanf("%d",&k);
	}
	else
	{
		k = atoi(argv[2]);
	}
	
	strcat(pasta,arq);
	if(argc==0)
		printf("\n%s\n",pasta);
	
	int n = lerN(pasta);
	if(n<=0)
	{
		printf("Erro na leitura do N\n");
	}
	else
	{
		int **G = (int **) malloc(n*sizeof(int *));
		for(j=0;j<n;j++)
		{
			G[j]=(int *) malloc(n*sizeof(int));
		}
		int cores[n];
		
		lerGrafo(G, pasta, n);

		int delta = calcularDelta(G, n);

		if(argc==0)
			printf("Delta de G: %d\n",delta);

		long long int i, p = 1; 
		int min = -1, solmin = -1;
		int corMin;

	//	for(k=2;k<=delta;k++)
		{
			for(j=0;j<n;j++)
			{
				p = p*k;
			}
			
			for(i=0;i<p;i++)
			{
			//	printf("\n\nTeste numero: %lld",i);
				geraCor(cores, n, k, i);
			/*	printf("\nConjunto de Cores: ");
				for(j=0;j<n;j++)
				{
					printf("%d  ",cores[j]);
				}
				printf("\n\n");
			*/	min = verificaCor(cores, G, n);
				//printf("\nSomatorio: %d",min);
				if(i==0)
				{
					solmin = min;
				}
				else
					if(min<solmin)
					{	
						solmin = min;
						corMin = i;
						//printf("\nMenor: %d",solmin);
					}
			}
			escreveResult(solmin,corMin,n,k, delta,arq);
		}
	}
	
}

int calcularDelta(int** G, int n)
{
	int soma = 0, maior = 0;
	int i, j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(G[i][j] != 0)
			{
				soma++;
			}
		}
		if(soma>maior)
		{
			maior = soma;
		}
		soma = 0;
	}
	return maior;
}

int lerN(char nome[])
{
	int n = -1;
	FILE *arq;
	
	arq = fopen(nome, "r");
	if(arq == NULL)
	    printf("Erro, nao foi possivel abrir o arquivo\n");
	else
		fscanf(arq,"%d",&n);
		
	fclose(arq);
	return n;
}

void lerGrafo(int** G, char nome[], int n)
{
	int i, j, m;
	FILE *arq;
	
	arq = fopen(nome, "r");
	if(arq == NULL)
	    printf("Erro, nao foi possivel abrir o arquivo\n");
	
	fscanf(arq,"%d",&m);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			fscanf(arq,"%d",&m);
			G[i][j] = m;
		}
	}
}

void geraCor(int cor[], int n, int k, long long int a)
{
	long long int b = a;
	int quo, rest;
	int aux[n], i;
	for(i=0;i<n;i++){
		aux[i] = -1;
		cor[i] = 0;	
	}
		
	i = 0;
	
	do{
		quo = b/k;
		rest = b-(quo*k);
		aux[i] = rest;
		b = quo;
		i++;
	}while(b>0);
//	printf("\n%d\n",i);
	int j, l;
	
//	for(j=0;j<n;j++){
//		printf(" %d ",aux[j]);
//	}
	
	
	for(j=n-1, l=0; j>=0 ; j--, l++)
	{	
		
		if(aux[l] != -1)
		{
			cor[j] = aux[l]; 
		}
		else
		{
			cor[j] = 0;
		}
	}
}


int verificaCor(int cor[], int** G, int n)
{
	int soma = 0;
	int i, j;
	for(i=0;i<n-1;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(cor[i] == cor[j])
			{
				soma += G[i][j];
			}
		}
	}
	return soma;
}

void escreveResult(int min, int cor, int n, int k, int delta, char* nome)
{
	struct timeval tv;
	struct tm* ptm;
	char time_string[40];

	gettimeofday(&tv, NULL);
	ptm = localtime(&tv.tv_sec);

	strftime(time_string, sizeof(time_string), "%H:%M:%S", ptm);


	FILE *arq;
	arq = fopen("resultados/result.txt", "a");
	fprintf(arq,"\n\nData: %s\tHora: %s",__DATE__,time_string);
	fprintf(arq,"\n\nO grafo %s possui Delta = %d ", nome, delta);
	fprintf(arq,"\nUtilizando %d cores o menor somatório foi: %d\n", k, min);
	int i, cores[n];

	geraCor(cores,n, k, cor);

	for(i=0;i<n;i++)
		fprintf(arq,"%d  ", cores[i]);

	fprintf(arq,"\n\n");

	for(i=0;i<45;i++)
		fprintf(arq,"-");
	fclose(arq);
}
