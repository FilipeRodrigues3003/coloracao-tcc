/*
#################################################################################
#	@author: Filipe Rodrigues Cardoso da Silva								    #
#	@copyrights: Faculdade de Educação Tecnológica do Estado do Rio de Janeiro  #
#	@title: Coloração ponderada com interseção minima						    #
#	@version: 0.3.0 											    			#
#   @date: 27/04/2018  												    		#
#   @update: 17/05/2018												    		#
#################################################################################
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

struct grafo{
	int q;
	int n;
	int d;
	int a;
	int de;
	int k;
	int m;
}typedef Graph;

int lerN(char arq[], Graph* no);
void lerGrafo(int** G, char arq[], int n, int l, Graph* no);
int geraCor(int cor[], int n, int k, int ac[]);
int verificaCor(int cor[], int** G, int n, int* arestas);
char* itoa(int val, int base);
int testeCor(int cores[], int n, int k);
void escreveResult(Graph no, int min, int arestas, int cores[], char* nome, double time_taken, int l);

int main(int argc, char *argv[ ]){
	int k, j, i, l;
	char arq[20] = "";
	char pasta[30] = "grafos/";
	clock_t begin;
	clock_t end;
	clock_t tempo;
	Graph no;
	if(argc>0)
	{
		strcpy(arq,argv[1]);
	}
	else
	{
		printf("Informe o nome do arquivo do Grafo: ");
		scanf("%s", arq);
	}

	
	strcat(pasta,arq);
	if(argc==0)
		printf("\n%s\n",pasta);
	
	int n = lerN(pasta, &no);
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
		
		
		for(l=0;l<no.q;l++)
		{
			int solmin = sizeof(int)-1;
			lerGrafo(G, pasta, n, l, &no);

			for(k=2;solmin>0;k++)
			{
				begin = clock();
				int min, arestas = 0, aremin;
				solmin = sizeof(int)-1;
				int corMin[n];

				for(j=0;j<n;j++)
				{
					cores[j] = 0;
				}

				do
				{	
					min = verificaCor(cores, G, n, &arestas);
					if(solmin==sizeof(int)-1)
					{
						solmin = min;
						for(i=0;i<n;i++)
						{
							corMin[i] = cores[i];
						}
						aremin = arestas;
					}
					else
					{
						if(min<solmin)
						{	
							solmin = min;
							
							for(i=0;i<n;i++)
							{
								corMin[i] = cores[i];
							}

							aremin = arestas;
						}
					}
				}while(geraCor(cores, n, k, cores)==0 && solmin>0);
				end = clock();
				tempo = end-begin;
				double time_taken = ((double)tempo)/CLOCKS_PER_SEC;
				no.k = k;
				escreveResult(no,solmin,aremin,corMin,arq,time_taken, l);
			}
		}
	}
}


int lerN(char nome[], Graph* no)
{
	int b, g;
	FILE *arq;
	
	arq = fopen(nome, "r");
	if(arq == NULL)
	    printf("Erro, nao foi possivel abrir o arquivo\n");
	else
	{
		fscanf(arq,"%d %d %d %d %d %d", &no->q, &no->n, &b, &no->d, &no->a, &g);
	}
	fclose(arq);
	return no->n;
}

void lerGrafo(int** G, char nome[], int n, int l, Graph* no)
{
	int i, j, m, a, c, d, aux, q;
	FILE *arq;
	
	arq = fopen(nome, "r");
	if(arq == NULL)
	{
	    printf("Erro, nao foi possivel abrir o arquivo\n");
		return;
	}

	fscanf(arq,"%d",&q);
	for(aux=0;aux<=l;aux++)
	{
		fscanf(arq,"%d %d %d %d %d", &a, &no->m, &c, &d, &no->de);
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				fscanf(arq,"%d",&m);
				G[i][j] = m;
			}
		}
	}	
	fclose(arq);
}

int geraCor(int cor[], int n, int k, int ac[])
{
	int i, j=0;
	for(i=n-1;i>=0;i--)
	{			
		if(ac[i]<k-1 && j==0)
		{
			cor[i] = ac[i] + 1; 
			j=1;
		}
		else
		{
			if(j==1)
			{
				cor[i] = ac[i];
			}
			else
			{
				cor[i] = 0;
				j = 0;
			}
		}
	}
	if(j==1)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}


int verificaCor(int cor[], int** G, int n, int* arestas)
{
	int soma = 0;
	int i, j, are = 0;
	for(i=0;i<n-1;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(cor[i] == cor[j])
			{
				soma += G[i][j];
				if(G[i][j]!=0)
					are++;
			}
		}
	}
	*arestas = are;
	return soma;
}

char* itoa(int val, int base){
	
	static char buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];
	
}

int testeCor(int cores[], int n, int k)
{
    int i, s = 0;
    int cont[k];
    for(i=0;i<k;i++)
    {
        cont[i] = 0;
    }

    for(i=0;i<n;i++)
    {
        cont[cores[i]]++;
    }

    for(i=0;i<k;i++)
    {
        if(cont[i]>0)
        {
            s++;
        }
    }
    return s;
}

void escreveResult(Graph no, int min, int arestas, int cores[], char* nome, double time_taken, int l)
{
	struct timeval tv;
	struct tm* ptm;
	char time_string[40];
	char pasta[40] = "resultados/";
	char pont[40] = "";
	char aux[30] = "_";

	gettimeofday(&tv, NULL);
	ptm = localtime(&tv.tv_sec);

	strftime(time_string, sizeof(time_string), "%d/%m/%Y %H:%M:%S", ptm);

	strcat(pasta,nome);
	strncat(pont,pasta,strlen(pasta)-4);
	strcat(aux,itoa(no.k,10));
	strcat(aux,".res");
	strcat(pont,aux);
	
	FILE *arq;
	arq = fopen(pont, "a");

	fseek(arq, 0, SEEK_END);
    int size = ftell(arq);
	if(size==0)
	{
		fprintf(arq,"%s\t",time_string);
		fprintf(arq,"%3d  %3d  %3d  %3d  %3d\n", no.q, no.n, no.d, no.a, no.k);

	}
	fprintf(arq,"\n%3d  %3d  %3d  %3d  %3d  %3d  ", l, no.m, testeCor(cores,no.n,no.k), no.de, min, arestas);
	fprintf(arq,"  %.6lf\t",time_taken);
	int i;

	for(i=0;i<no.n;i++)
		fprintf(arq,"%3d  ", cores[i]);


	fclose(arq);
	return;
}
