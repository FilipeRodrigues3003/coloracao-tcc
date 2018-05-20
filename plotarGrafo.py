import networkx as nx
import matplotlib.pyplot as plt
from collections import defaultdict
import sys

nome = str(sys.argv[1])
#input("Informe o nome do arquivo: ")
pasta = "grafos/"+nome

f = open(pasta,"r")
a = {} 
a = f.readline()
quant = int(a[:3].strip(" "))
a = f.readline()
b = str(a[:3].strip(" "))
n = int(b)
mat = f.read()
soma = 0
#print(n)
for ob in range(0,quant):
    result = "imagens/"+nome.strip(".dat")+"_"+str(ob)+".png"
    linha = 0
    lin = defaultdict(list)
    G=nx.Graph()
    #print(mat)
   
    init = (n*(n*5)+n) 
    print(init)
    if ob>0:
        soma = 24

    for coln in range(ob*init+(soma*ob),init+ob*init+(soma*ob)):
        if mat[coln] != " ":
            if mat[coln] == "\n":
                print(lin[linha])
                linha = linha + 1
            elif mat[coln-1] == " ":
                lin[linha].append(int(mat[coln:coln+2].strip(" ")))
    
    

   
    labels = {}
    edge_labels = {}

    for linha in range(0,n):
        #print(lin[linha])
        G.add_node(linha)
        labels = linha
        for col in range(0,n):
            if lin[linha][col] != 0:
                G.add_edge(linha,col,weight=lin[linha][col])
                edge_labels = lin[linha][col]


    lin.clear()

    aux= nx.shell_layout(G,scale=0.5)

    nnode=0
    labels = {}
    pos={}
    for turma in G.node:
        labels[nnode]=turma
        pos[nnode]=aux[turma]
        pos[nnode][1]=pos[nnode][1]+0.1
        nnode+=1

    label = nx.get_edge_attributes(G,'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=label, alpha=0.5)
    nx.draw_networkx(G, pos, node_color="k", font_color="w")
    plt.axis('off')
    plt.savefig(result)
    plt.close()
    G.clear()
    aux.clear()
    label.clear()
    pos.clear()
    labels.clear()
    #plt.show()
        
f.close
