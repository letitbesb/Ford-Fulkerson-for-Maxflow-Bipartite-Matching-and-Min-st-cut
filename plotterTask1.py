import networkx as nx
import matplotlib.pyplot as plt

# read data from file
with open("inputTask1.txt", "r") as f:
    n = int(f.readline())-1  # number of vertices
    edges = []
    f.readline()
    for line in f:
        u, v ,x= map(int, line.strip().split())
        edges.append((u, v))

# create graph
G = nx.DiGraph()
G.add_nodes_from(range(1, n+1))
G.add_edges_from(edges)

# draw graph
pos = nx.spring_layout(G)
nx.draw_networkx_nodes(G, pos, node_size=500)
nx.draw_networkx_edges(G, pos, edge_color='y')
nx.draw_networkx_labels(G, pos, font_size=10, font_family='sans-serif')
plt.axis('off')
plt.show()
