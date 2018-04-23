#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 0
#define FALSE 1


int main(int argc, char *argv[ ])
{
    int n, i, j, delta, num;
    char nome[20];
    char pasta[30] = "grafos/";

    if(!argv[1])
    {
        printf("Informe o nome do arquivo: ");
        scanf("%s",nome);
    }
    else
    {
        strcpy(nome,argv[1]);
    }
    
    if(!argv[2])
    {
        printf("Informe o tamanho da matriz: ");
        scanf("%d",&n);
    }
    else
    {
        n = atoi(argv[2]);
    }
    
    if(!argv[3])
    {
        printf("Informe o Delta Máximo do Grafo: ");
        scanf("%d",&delta);
    }
    else
    {
        delta = atoi(argv[3]);
    }


    srand( (unsigned)clock() );
    int cont[n];
    int G[n][n];

 
    for(i=0;i<n;i++)
        cont[i] = 0;

    for(i=0;i<n-1;i++){
        for(j=i+1;j<n;j++)
        {
            num = rand() % 10;
            if(cont[i]<delta && cont[j]<delta && num>2)
            {
                cont[i]++;
                cont[j]++;
                G[i][j] = num;
                G[j][i] = num;
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

    srand( (unsigned)clock() );
    
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if((cont[i] == 0 || cont[j] == 0) && i != j)
            {
                num = (rand() % 8)+2;
                cont[i]++;
                cont[j]++;
                G[i][j] = num;
                G[j][i] = num;
            }
            if(argc==0)
                printf("%d  ",G[i][j]);
        }
        if(argc==0)
            printf("\n");
    }

    
    FILE *arq;
    strcat(pasta,nome);

	arq = fopen(pasta, "w");
    fprintf(arq,"%d\n",n);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
		    fprintf(arq,"%d  ",G[i][j]);
        fprintf(arq,"\n");
    }
    
    if(argc==0)
        printf("\nMatriz criada com sucesso!\nUtilize \'python plotarGrafo.py\' para ve-lo.\n\n");
    fclose(arq);
}

