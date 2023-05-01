import networkx as nx
import matplotlib.pyplot as plt



uset=[]
vset=[]
# read data from file
with open("inputBipartite.txt", "r") as f:
    n = int(f.readline())-1  # number of vertices
    edges = []
    # f.readline()
    for line in f:
        u, v = map(int, line.strip().split())
        edges.append((u, v))
        uset.append(u)
        vset.append(v)

# create graph
G = nx.Graph()
G.add_nodes_from(uset, bipartite=0)  # nodes 1-4 belong to partition 0
G.add_nodes_from(vset, bipartite=1)    # nodes 5-7 belong to partition 1
G.add_edges_from(edges)

# create bipartite layout
pos = nx.bipartite_layout(G, uset)

# draw graph
nx.draw_networkx_nodes(G, pos, nodelist=uset, node_color='y', node_size=500)
nx.draw_networkx_nodes(G, pos, nodelist=vset, node_color='m', node_size=500)
nx.draw_networkx_edges(G, pos, edge_color='k')
nx.draw_networkx_labels(G, pos, font_size=20, font_family='sans-serif')
plt.axis('off')
plt.show()


# import networkx as nx
# import matplotlib.pyplot as plt

# # create bipartite graph
# G = nx.Graph()

# # G.add_edges_from([(1, 5), (1, 6), (2, 5), (3, 6), (4, 7)])  # add edges

# # get position of nodes in bipartite layout


# # draw nodes
# nx.draw_networkx_nodes(G, pos, nodelist=[1, 2, 3, 4], node_size=500)
# nx.draw_networkx_nodes(G, pos, nodelist=[5, 6, 7], node_color='b', node_size=500)

# # draw edges and labels
# nx.draw_networkx_edges(G, pos)
# nx.draw_networkx_labels(G, pos)

# # show plot
# plt.axis('off')
# plt.show()