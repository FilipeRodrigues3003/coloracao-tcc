import networkx as nx
import matplotlib.pyplot as plt
from collections import defaultdict

nome = input("Informe o nome do arquivo: ")
pasta = "grafos/"+nome
f = open(pasta,"r")
a = {} 
a = f.readline()
#print(type(a))
b = str(a[:3].strip(" "))
n = int(b)
#print(n)
linha = 0
lin = defaultdict(list)
color = []
mat = f.read()
G=nx.Graph()
#print(mat)

for col in range(0,n*(n*5)+n):
    if mat[col] != " ":
        if mat[col] == "\n":
            linha = linha + 1
        else:
            lin[linha].append(int(mat[col]))
           

for col in range(0,len(mat)-48):
    if col >= ((len(mat)-48)-n*5):
        if mat[col] != " " and mat[col] != "\n":
            color.append( int(mat[col]))

print(color)
labels = {}
edge_labels = {}
i = 0
cores = ["#000000", "#ff0000", "#0000ff", "#00ff00", "#fff000", "#727272", "#ff8800", "#aa00ff", "#ff00ff", "#914600", "#849100", "#00916a", "#881600", "#008888", "#6bf9b2", "#f9f96b", "#896bf9", "#ffa3a3", "#ffe1a3", "#f7ffa3", "#bbffa3"]


for linha in range(0,n):
    G.add_node(linha, cor='')
    labels = linha
    for col in range(0,n):
        if lin[linha][col] != 0:
            G.add_edge(linha,col,weight=lin[linha][col])
            edge_labels = lin[linha][col]


for linha in range(0,n):
    G.node[linha]['cor'] = cores[color[i]]
    #print("{} {}".format(cores[color[i]],linha))
    i = i + 1

cores=[]
for linha in G.node:
     cores.append(G.node[linha]['cor'])


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
nx.draw_networkx(G, pos, labels, node_color=cores, font_color="w")

plt.show()
    
f.close


