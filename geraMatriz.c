#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

int main(int argc, char *argv[ ] )
{
    int n, i, j;
    if(!argv[1])
    {
        printf("Informe o tamanho da matriz: ");
        scanf("%d",&n);
    }
    else
    {
        n = atoi(argv[1]);
    }
    FILE *arq;

	arq = fopen("grafo-novo.txt", "w");
    fprintf(arq,"%d\n",n);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
		    fprintf(arq,"0  ");
        fprintf(arq,"\n");
    }
    fclose(arq);
}