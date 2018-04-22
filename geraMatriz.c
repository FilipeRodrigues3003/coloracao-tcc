#include <stdio.h>
#include <string.h>

int main()
{
    int n, i, j;

    printf("Informe o tamanho da matriz: ");
    scanf("%d",&n);

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