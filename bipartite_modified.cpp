#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <fstream>
using namespace std;
 
struct Edge
{
    int u, v;     // Source and destination nodes
    int capacity; // Capacity of the edge
    int flow;     // Current flow on the edge
    // Edge* residual;        // Pointer to the residual edge in the residual graph
 
    // Constructor to initialize the edge
    Edge(int u, int v, int capacity) : u(u), v(v), capacity(capacity), flow(0) {}
};
 
struct ResidualEdge : Edge
{
    int forward_edge_idx;  // Index of the forward edge in the adjacency list
    int backward_edge_idx; // Index of the backward edge in the adjacency list
 
    // Constructor to initialize the residual edge
    ResidualEdge(int u, int v, int capacity, int forward_edge_idx, int backward_edge_idx) : Edge(u, v, capacity), forward_edge_idx(forward_edge_idx), backward_edge_idx(backward_edge_idx) {}
};
 
class Graph
{
public:
    int n;                                       // number of vertices in the graph
    vector<vector<Edge *>> adj;                  // adjacency matrix to store the edges in the graph
    vector<vector<ResidualEdge *>> residual_adj; // adjacency matrix to store the edges in the residual graph
    // vector<bool> visited;                        // to keep track of visited nodes while calculation the augmented path
 
    // constructor to initialize the graph
    Graph(int n);
 
    // method to add an edge to the graph
    void add_edge(int u, int v, int capacity);
 
    // method to create the residual graph from the original graph
    void create_residual_graph();
 
    // method to find an augmenting path in the residual graph using DFS
    bool dfs(int source, int sink, vector<ResidualEdge *> &parent, vector<bool> &visited);
    vector<ResidualEdge *> find_augmenting_path(int source, int sink);
 
    // method to run the Ford-Fulkerson algorithm on the graph
    int max_flow(int source, int sink);
 
    // method to implement st_cut
    vector<pair<int, int>> st_cut(int source, int sink);
 
    //helper function for the st_cut
    void dfs_cut(int u, int sink, vector<bool> &visited);
 
};
 
Graph::Graph(int n)
{
    this->n = n;
    adj.resize(n, vector<Edge *>(n, nullptr));
    residual_adj.resize(n, vector<ResidualEdge *>(n, nullptr));
    // visited.resize(n, false);
}
 
void Graph::add_edge(int u, int v, int capacity)
{
    Edge *e = new Edge(u, v, capacity);
    //    Edge* e_res = new Edge(v, u, 0);
    e->flow = 0;
    // e->residual = e_res;
    // e_res->residual = e;
    adj[u][v] = e;
}
 
void Graph::create_residual_graph()
{
    for (int u = 0; u < n; u++)
    {
        for (int v = 0; v < n; v++)
        {
            if (adj[u][v])
            {
                // Create forward edge in residual graph only if c(e)-f(e) is non zero
                if (adj[u][v]->capacity - adj[u][v]->flow > 0)
                {
 
                    ResidualEdge *forward_edge = new ResidualEdge(u, v, adj[u][v]->capacity - adj[u][v]->flow, adj[u].size() - 1, residual_adj[v].size());
                    residual_adj[u][v] = forward_edge;
                }
                else if (adj[u][v]->capacity - adj[u][v]->flow == 0)
                {
                    residual_adj[u][v] = nullptr;
                }
 
                // Create backward edge in residual graph only if the flow in the backward edge is non zero
                if (adj[u][v]->flow != 0)
                {
                    ResidualEdge *backward_edge = new ResidualEdge(v, u, adj[u][v]->flow, residual_adj[v].size(), adj[u].size() - 1);
                    residual_adj[v][u] = backward_edge;
                }
                else
                {
                    residual_adj[v][u] = nullptr;
                }
 
                // Set pointers to residual edges
                // forward_edge->residual = backward_edge;
                // backward_edge->residual = forward_edge;
            }
        }
    }
}
 
bool Graph::dfs(int s, int t, vector<ResidualEdge *> &parent, vector<bool> &visited)
{
    // Mark the current vertex as visited
    visited[s] = true;
 
    // If s is the sink, return true
    if (s == t)
    {
        return true;
    }
 
    // Loop through all adjacent vertices of s in the residual graph
    for (int v = 0; v < n; v++)
    {
        // If v is not visited and has positive residual capacity
        if (!visited[v] && residual_adj[s][v] != nullptr)
        {
            // Set v as the parent of s
            parent[v] = new ResidualEdge(s, v, residual_adj[s][v]->capacity, 0, 0);
 
            // Recursively do DFS from v to t
            if (dfs(v, t, parent, visited))
            {
                return true;
            }
        }
    }
 
    // If no augmenting path is found from s, return false
    return false;
}
vector<ResidualEdge *> Graph::find_augmenting_path(int source, int sink)
{
    vector<bool> visited(n, false);
    vector<ResidualEdge *> parent(n, nullptr);
 
    if (!dfs(source, sink, parent, visited))
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = nullptr;
        }
    }
    return parent;
}
 
int Graph::max_flow(int source, int sink)
{
    int max_flow = 0;
    while (true)
    {
        // cout << 0 << "//////" << endl;
        create_residual_graph();
        // for (int i = 0; i < residual_adj.size(); i++)
        // {
        //     for (int j = 0; j < residual_adj[i].size(); j++)
        //     {
        //         if (residual_adj[i][j] != nullptr)
        //             cout << residual_adj[i][j]->u << " " << residual_adj[i][j]->v << " " << residual_adj[i][j]->capacity << endl;
        //     }
        // }
        // cout << endl;
        vector<ResidualEdge *> augmenting_path = find_augmenting_path(source, sink);
        // for (int v = sink; v != source; v = augmenting_path[v]->u)
        // {
        //     cout << augmenting_path[v]->u << " ";
        // }
        // cout << endl;
        if (!augmenting_path[sink])
        {
            break;
        }
 
        int path_flow = INT_MAX;
        for (int v = sink; v != source; v = augmenting_path[v]->u)
        {
            path_flow = min(path_flow, augmenting_path[v]->capacity); // finding the bottleneck capacity
        }
        // for the particular augmented edge selected we change the flow of the edges in the acutal graph.
        // for (int v = sink; v != source; v = augmenting_path[v]->u)
        // {
        //     cout << augmenting_path[v]->u << " " << augmenting_path[v]->v << " " << augmenting_path[v]->capacity << endl;
        // }
        // cout << path_flow << endl;
        for (int v = sink; v != source; v = augmenting_path[v]->u)
        {
            if (!adj[augmenting_path[v]->u][v])
            {
                adj[v][augmenting_path[v]->u]->flow -= path_flow;
            }
            else
                adj[augmenting_path[v]->u][v]->flow += path_flow;
        }
        // for (int v = sink; v != source; v = augmenting_path[v]->u)
        // {
        //     ResidualEdge *forward_edge = augmenting_path[v];
        //     ResidualEdge *backward_edge = residual_adj[v][forward_edge->u];
 
        //     forward_edge->capacity -= path_flow;
        //     if (backward_edge)
        //     {
        //         backward_edge->capacity += path_flow;
        //     }
        //     else
        //     {
        //         ResidualEdge *new_backward_edge = new ResidualEdge(v, forward_edge->u, path_flow, residual_adj[v].size(), forward_edge->forward_edge_idx);
        //         residual_adj[v][forward_edge->u] = new_backward_edge;
        //     }
 
        //     adj[forward_edge->u][forward_edge->v]->flow += path_flow;
        // }
        max_flow += path_flow;
    }
 
    return max_flow;
}
 
vector<pair<int, int>> Graph::st_cut(int source, int sink) {
    // Run the Ford-Fulkerson algorithm to find the max flow
    max_flow(source, sink);
 
    // Perform a DFS on the residual graph to find the set of vertices reachable from the source
    vector<bool> visited(n, false);
    dfs_cut(source, sink, visited);
 
    // Find the edges crossing the cut (from the visited set to the unvisited set)
    vector<pair<int, int>> cut_edges;
    for (int u = 0; u < n; u++) {
        if (visited[u]) {
            for (int v = 0; v < n; v++) {
                if (!visited[v] && adj[u][v]) {
                    cut_edges.push_back(make_pair(u, v));
                }
            }
        }
    }
 
    return cut_edges;
}
 
// Helper method to perform DFS on the residual graph
void Graph::dfs_cut(int u, int sink, vector<bool> &visited) {
    visited[u] = true;
 
    for (int v = 0; v < n; v++) {
        if (!visited[v] && residual_adj[u][v] && residual_adj[u][v]->capacity > 0) {
            dfs_cut(v, sink, visited);
        }
    }
}
 
 
int main()
{
    ifstream infile("inputBipartite.txt");
 

    int n; infile>>n;
    
 
    Graph G(n+2);
    int source, sink;
    // infile >> source >> sink;
    source=n; sink=n+1;
    //user enters size of 
    //now user enters which nodes are in set U
    int u, v;
    while (infile >> u >> v )
    {
        // cout << u << " " << v << " " << capacity << endl;
        G.add_edge(u, v, 1);
        G.add_edge(source,u,1);
        G.add_edge(v,sink,1);
    }
    // G.create_residual_graph();
    // vector<ResidualEdge*> ans = G.find_augmenting_path(2,4);
    // (!ans[4])?cout << 1 << endl:cout << 0 << endl;
    // for(int v = 2;v != 4;v = ans[v]->u){
    //     cout << ans[v]->u << " " << ans[v]->v << endl;
    // }
    int a = G.max_flow(source, sink);
    // vector<pair<int,int>> st_cut_edges = G.st_cut(source,sink);
    // for(int i = 0;i < st_cut_edges.size();i++){
    //     cout << st_cut_edges[i].first << " " << st_cut_edges[i].second << endl;
    // } 
    cout << "maximum number of edges are :- "<< a << endl;
    string filename = "plotBipartite.py";
    string command = "python ";
    command += filename;
    system(command.c_str());
    return 0;
}