/*
#################################################################################
#	@author: Filipe Rodrigues Cardoso da Silva								    #
#	@copyrights: Faculdade de Educação Tecnológica do Estado do Rio de Janeiro  #
#	@title: Coloração ponderada com interceção minima						    #
#	@version: 0.2.0 											    			#
#   @date: 27/04/2018  												    		#
#################################################################################
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>


int lerN(char arq[]);
void lerGrafo(int** G, char arq[], int n);
int geraCor(int cor[], int n, int k, int ac[]);
int verificaCor(int cor[], int** G, int n, int* arestas);
void escreveResult(int n, int k, int min, int arestas, int cores[], char* nome);

int main(int argc, char *argv[ ]){
	int k, j, i;
	char arq[20] = "";
	char pasta[30] = "grafos/";
	
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
	
		int min, solmin = sizeof(int)-1, arestas = 0, aremin;
		int corMin[n];

		for(k=1;solmin>0;k++)
		{
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
			}while(geraCor(cores, n, k, cores)==0);
			escreveResult(n,k,solmin,aremin,corMin,arq);
		}
	}
	
}


int lerN(char nome[])
{
	int n = -1, b, c, d, g;
	FILE *arq;
	
	arq = fopen(nome, "r");
	if(arq == NULL)
	    printf("Erro, nao foi possivel abrir o arquivo\n");
	else
		fscanf(arq,"%d %d %d %d %d",&n, &b, &c, &d, &g);
	
	if(g==0)
		n = g;
		
	fclose(arq);
	return n;
}

void lerGrafo(int** G, char nome[], int n)
{
	int i, j, m, a, b, c, d, e;
	FILE *arq;
	
	arq = fopen(nome, "r");
	if(arq == NULL)
	    printf("Erro, nao foi possivel abrir o arquivo\n");
	
	fscanf(arq,"%d %d %d %d %d", &a, &b, &c, &d, &e);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			fscanf(arq,"%d",&m);
			G[i][j] = m;
		}
	}
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

void escreveResult(int n, int k, int min, int arestas, int cores[], char* nome)
{
	struct timeval tv;
	struct tm* ptm;
	char time_string[40];
	char pasta[40] = "grafos/";

	gettimeofday(&tv, NULL);
	ptm = localtime(&tv.tv_sec);

	strftime(time_string, sizeof(time_string), "%d/%m/%Y %H:%M:%S", ptm);

	strcat(pasta,nome);

	FILE *arq;
	arq = fopen(pasta, "a");
	fprintf(arq,"\n\n%s\n",time_string);
	fprintf(arq,"\n%3d  %3d  %3d\n", k, min, arestas);
	int i;

	for(i=0;i<n;i++)
		fprintf(arq,"%3d  ", cores[i]);

	fprintf(arq,"\n\n");

	for(i=0;i<45;i++)
		fprintf(arq,"-");
	fclose(arq);
	return;
}
