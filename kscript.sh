#! /bin/bash
#author: Filipe Rodrigues Cardoso da Silva
#organization: Faculdade de Educação Tecnológica do Estado Rio de Janeiro
rm forcabruta
rm criaMatriz
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
v=4
fi
sum=$(($1+$v))
if [ $sum -gt 26 ]
then
echo $sum
echo ""
echo "Erro: quantidade de grafos pedido não pode ser executado."
echo ""
echo "Máximo de vertices permitidos: 26"
exit
fi
for((vertice=$v;vertice<($1+$v);vertice++))
do
if [ $vertice -gt 16 ]
then
d=$vertice-$($($($vertice-16)*2)+3)
else
d=vertice
fi
for((densidade=3;densidade<10;densidade=densidade+2))
do
den=$(($densidade*10))
nome=grafo$vertice-$den.txt

echo ${nome}
if [ ! -e grafos/${nome} ]
then
./criaMatriz ${nome} $vertice $den 9
fi

./forcabruta ${nome}

done
done
else
echo ""
tput bold; echo "Para executar os programas informe:" ; tput sgr0
echo ""
echo "	'O NÚMERO DE GRAFOS PARA SEREM TESTADOS' - Obrigatório" 
echo "	'NÚMERO MINIMO DE VÉRTICES PARA INICIAR' - Opcional (Default = 4)"
echo ""
fi 