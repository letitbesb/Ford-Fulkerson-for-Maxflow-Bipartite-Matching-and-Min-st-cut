# Ford-Fulkerson-for-Maxflow-Bipartite-Matching-and-Min-st-cut
Implementing the Ford Fulkerson Algorithm in C++ to solve for Maxflow. Solving the Bipartite Matching problem using FF. Also finding the min-cut for a given source &amp; sink in a graph using the Ford Fulkerson Algorithm.

## A General Discussion of the Algorithm : 


  The Ford-Fulkerson algorithm is a widely used algorithm for finding the maximum flow in a flow network. A flow network is a directed graph where each edge has a capacity that represents the maximum amount of flow that can pass through it. The goal of the algorithm is to find the maximum amount of flow that can be sent from a source vertex to a sink vertex in the graph.

  The Ford-Fulkerson algorithm is an iterative algorithm that works by incrementally finding augmenting paths from the source to the sink. An augmenting path is a path in the graph that has residual capacity, which is the difference between the capacity of the edge and the flow that is currently passing through it. The algorithm works by selecting an augmenting path from the source to the sink and increasing the flow along that path by the minimum residual capacity of the edges along the path. This process is repeated until no more augmenting paths can be found.


  One common implementation of the Ford-Fulkerson algorithm uses the breadth-first search algorithm to find augmenting paths from the source to the sink. This version of the algorithm is known as the Edmonds-Karp algorithm. The time complexity of the Edmonds-Karp algorithm is O(VE^2), where V is the number of vertices in the graph and E is the number of edges.


  The Ford-Fulkerson algorithm has several important applications, including in transportation planning, network routing, and resource allocation. However, it is worth noting that the algorithm may not always terminate or find the optimal solution in certain cases. In particular, the algorithm may get stuck in an infinite loop if there are negative weight edges in the graph, and it may not find the optimal solution if there are multiple paths from the source to the sink with the same capacity.
  
  
## Approach :
  The algorithm uses the following approach:

  * Initialize the flow on all edges to 0.
  
  * While there exists a path from the source to the sink in the residual graph:
      - Create residual graph
      - Find the path with the minimum capacity along the path (called bottleneck capacity).
      - Add the bottleneck flow to our ans: maxflow
      - Add the bottleneck capacity to the flow of each edge along the path.
      - Subtract the bottleneck capacity from the capacity of each edge along the path.
      - Create the respective forward backward edges in the residual edge after augmenting path is dealt with.
      - Adjust for new original graph after current augmenting path flow is calculated.
      - Repeat
      
  * Return the maximum flow.

The algorithm uses the residual graph to find the augmenting paths. The residual graph is a graph that represents the remaining capacity of each edge in the network. 

The algorithm uses the Depth First Search (DFS) algorithm to find the augmenting paths in the residual graph.


**The algorithm for augmenting procedure** :
```
Augment(f,P)
Let b = bottleneck(P,f)
For each edge (u,v) ∈ P
If e=(u,v) is a forward edge then increase f(e) in G by b.
Else((u,v) is a backward edge,  and let e=(v,u))
decrease f(e) in G by b.
Endif
Endfor
Return(f)
 ```
 
 **Ford Fulkerson Algorithm** :
  ```
Initially f(e) = 0 for all e in G.
While there is an s-t path in the residual graph Gf 
Let P be a simple s-t path in Gf
f’ = augment(f,P)
Update f to be f’
Update the residual graph Gf  to be Gf’ 
Endwhile
Return f.
  ```

## Bipartite Matching :
 * Problem statement :
 
      The maximum bipartite matching problem involves finding the largest set of non-overlapping edges between two disjoint sets of vertices.
 * Solution approach :
      - We use the ford fulkerson algorithm to find out the maximum flow in an artifical graph where the edges vertices remain as they are for the bipartite graph, but we create a new source and sink and connect all vertices of set A with edges from source to them with capacity as 1, and edges from all vertices of set B to sink with capacity 1 and rest all edges have capacity 1.
      - Now solve for maxflow in this graph. 
      - Resultant answer is the maximum size of set of non-overlapping edges in this bipartite graph.
      
      
     
## Min s-t cut problem :
 * Problem statement :
 
      In a flow network, an s-t cut is a cut that requires the source ‘s’ and the sink ‘t’ to be in different subsets, and it consists of edges going from the source’s side to the sink’s side. The capacity of an s-t cut is defined by the sum of the capacity of each edge in the cut-set. The problem discussed here is to find minimum capacity s-t cut of the given network. 
 * Solution approach :
      - Run Ford-Fulkerson algorithm and consider the final residual graph. 
      - Find the set of vertices that are reachable from the source in the residual graph. 
      - All edges which are from a reachable vertex to non-reachable vertex are minimum cut edges. Print all such edges. 
      
      
     
## **Results ( Maxflow ) :**  


* **1st Testcase :**

  ![image](https://user-images.githubusercontent.com/29221347/235519284-36a5c884-ff28-41aa-8086-5d9e1078466b.png)
  
  
  ![image](https://user-images.githubusercontent.com/29221347/235519745-f80096db-de14-4e70-a624-5ad86ec286e2.png)
  
  
* **2nd Testcase :**


  ![image](https://user-images.githubusercontent.com/29221347/235519905-bdae29b3-124d-40d1-a700-4f41aab3c09f.png)
  
  
  ![image](https://user-images.githubusercontent.com/29221347/235519963-fa9c7cbf-d0be-4633-9a30-741463278738.png)


* **Sample size effect :**


  ![image](https://user-images.githubusercontent.com/29221347/235520273-318c51c9-a4aa-4484-93ce-175685b50707.png)

* ### Result for bipartite matching :

  ![image](https://user-images.githubusercontent.com/29221347/235521901-8dbdeb80-4cdd-4e51-af44-07f4faa556b4.png)
  
  ![image](https://user-images.githubusercontent.com/29221347/235521939-b260e715-fb5e-4bfc-80eb-81788a622cc1.png)



