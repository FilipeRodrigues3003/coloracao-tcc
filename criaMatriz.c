/*
#################################################################################
#	@author: Filipe Rodrigues Cardoso da Silva								    #
#	@copyrights: Faculdade de Educação Tecnológica do Estado do Rio de Janeiro  #
#	@title: Coloração ponderada com interseção minima						    #
#	@version: 0.2.0 											    			#
#   @date: 27/04/2018  												    		#
#################################################################################
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 0
#define FALSE 1


int main(int argc, char *argv[ ])
{
    int n, i, j, d, p, g, num, m = 0;
    char nome[20];
    char pasta[30] = "grafos/";

    if(argc>0)
    {
        strcpy(nome,argv[1]);
        n = atoi(argv[2]);
        d = atoi(argv[3]);
        p = atoi(argv[4]);
    }
    else
    {
        printf("Informe o nome do arquivo: ");
        scanf("%s",nome);
       
        printf("Informe a quantidade de vertices: ");
        scanf("%d",&n);
   
        printf("Informe a densidade Máxima do Grafo: ");
        scanf("%d",&d);
   
        printf("Informe o peso Máximo do Grafo: ");
        scanf("%d",&p);
    }
   
    srand( (unsigned)clock() );
    int G[n][n];
    
    for(i=0;i<n-1;i++){
        for(j=i+1;j<n;j++)
        {
            num = rand() % 100;
            if(num+1<d)
            {
                num = (rand() % p) + 1;
                G[i][j] = num;
                G[j][i] = num;
                m++;
            }
            else
            {
                G[i][j] = 0;
                G[j][i] = 0;
            }
        // printf("%d  ",G[i][j]);
        }
    // printf("\n");
    }
    for(i=0;i<n;i++)
    {
        G[i][i] = 0;
    }
    
    int cont = 0, maior = 0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(G[i][j] != 0)
            {
                cont++;
            }
           
           // printf("%d  ",cont);
        }
        if(cont>maior)
        {
            maior = cont;
        }
        cont = 0;
        //if(argc==0)
        //    printf("\n");
    }

    g = maior;

    
    FILE *arq;
    strcat(pasta,nome);

	arq = fopen(pasta, "w");
    //Numero de vertices
    //Numero de arestas
    //Densidade do Grafo
    //Peso máximo do Grafo
    //Grau máximo do Grafo
    fprintf(arq,"%3d  %3d  %3d  %3d  %3d\n", n, m, d, p, g);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
		    fprintf(arq,"%3d  ",G[i][j]);
        fprintf(arq,"\n");
    }
    fprintf(arq,"\n\nK   Minimo   Arestas\nColoração\n\n");
    for(i=0;i<45;i++)
		fprintf(arq,"-");

    
    if(argc==0)
        printf("\nMatriz criada com sucesso!\nUtilize \'python plotarGrafo.py\' para ve-lo.\n\n");
    fclose(arq);
}

