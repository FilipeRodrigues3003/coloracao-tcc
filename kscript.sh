#! /bin/bash
#author: Filipe Rodrigues Cardoso da Silva
#organization: Faculdade de Educação Tecnológica do Estado Rio de Janeiro
if [ ! -e forcabruta ]
then
gcc -Wall -pedantic -std=c99 forcabruta.c -o forcabruta -lm
fi
if [ ! -e criaMatriz ]
then
gcc -Wall -pedantic -std=c99 criaMatriz.c -o criaMatriz -lm
fi
#Entrada 1: Quantidade de testes para realizar
#Entrada 2: A partir de quantos vertices

if test $1
then
if test $2
then
v=$2
else
v=3
fi
for((vertice=$v;vertice<($1+$v);vertice++))
do
for((delta=2;delta<vertice;delta++))
do
nome=grafo$vertice-$delta.txt
echo ${nome}
#./criaMatriz ${nome} $vertice $delta
for((k=2;k<=$delta;k++))
do
./forcabruta ${nome} $k
done
done
done
else
echo "Os programas foram compilados com sucesso!"
echo ""
tput bold; echo "Para executar os programas informe:" ; tput sgr0
echo ""
echo "	'O NÚMERO DE GRAFOS PARA SEREM TESTADOS' - Obrigatório" 
echo "	'NÚMERO MINIMO DE VÉRTICES PARA INICIAR' - Opcional (Default = 3)"
echo ""
fi 