import networkx as nx
import matplotlib.pyplot as plt
from collections import defaultdict

nome = input("Informe o nome do arquivo: ")
pasta = "grafos/"+nome
f = open(pasta,"r")
a = f.readline()
print(type(a))
n = int(a)
print(n)
linha = 0
lin = defaultdict(list)
mat = f.read()
G=nx.Graph()
#print(mat)
for col in range(0,len(mat)):
    if mat[col] != " ":
        if mat[col] == "\n":
            linha = linha + 1
        else:
            lin[linha].append(int(mat[col]))

labels = {}
edge_labels = {}

for linha in range(0,n):
    print(lin[linha])
    G.add_node(linha)
    labels = linha
    for col in range(0,n):
        if lin[linha][col] != 0:
            G.add_edge(linha,col,weight=lin[linha][col])
            edge_labels = lin[linha][col]




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

plt.show()
    
f.close


