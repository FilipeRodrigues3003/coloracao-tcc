#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 0
#define FALSE 1


int main()
{
    int n, i, j, delta, num;
    char nome[20];
    char pasta[30] = "grafos/";
    int valido = TRUE;

    printf("Informe o nome do arquivo: ");
    scanf("%s",nome);
    printf("Informe o tamanho da matriz: ");
    scanf("%d",&n);
    printf("Informe o Delta Máximo do Grafo: ");
    scanf("%d",&delta);

    srand( (unsigned)time(NULL) );
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
            printf("%d  ",G[i][j]);
        }
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
    printf("\nMatriz criada com sucesso!\nUtilize \'python plotarGrafo.py\' para ve-lo.\n\n");
    fclose(arq);
}

