# K-Core Decomposition in C++

After reading Dr. Bin Guo's papers on k-core decomposition and parallel core maintenance, I wanted to go beyond just understanding the theory, so I built this.

This is a from-scratch C++ implementation of k-core decomposition on undirected graphs, written without any external libraries. Given a graph as an edge list, it computes the core number of every node and reports the degeneracy of the graph.

## What is K-Core Decomposition?

A k-core is the largest subgraph where every node has at least k neighbours within that subgraph. Every node gets assigned a core number, the highest k it can survive in.

What I found most interesting reading Dr. Guo's work is how deceptively simple the definition is, yet how computationally expensive it becomes on dynamic graphs where edges are constantly being inserted or deleted. The static case (what this project implements) is the foundation. The hard problem is maintaining core numbers incrementally without recomputing everything from scratch, which is exactly what his research solves.

## How to Run

Compile:
```bash
g++ main.cpp -o kcore
```

Add your graph as an edge list in `graph.txt` (one edge per line: `u v`), then run:
```bash
./kcore
```

## Example

Input (`graph.txt`):
```
1 2
1 3
1 4
2 3
2 4
3 4
4 5
5 6
6 7
5 7
```

Output:
```
Loaded 7 nodes from graph.txt
Node -> Core Number
-------------------
Node 1 -> 3
Node 2 -> 3
Node 3 -> 3
Node 4 -> 3
Node 5 -> 2
Node 6 -> 2
Node 7 -> 2

=== Summary ===
Total nodes: 7
Max core number (degeneracy): 3
Core 2: 3 nodes -> 5 6 7
Core 3: 4 nodes -> 1 2 3 4
```

Nodes 1-4 form a clique where everyone knows everyone, core 3. Nodes 5-7 form a triangle at the periphery, core 2.

## What's Next

This static implementation is my starting point. The natural extension is core maintenance on dynamic graphs, handling edge insertions and deletions without full recomputation, which is the problem Dr. Guo's research directly addresses. That's what I'm working toward.

## References

- Guo, B. et al. (2022). Simplified Algorithms for Order-Based Core Maintenance. arXiv:2201.07103
- Guo, B. et al. (2022). Parallel Order-Based Core Maintenance in Dynamic Graphs. arXiv:2210.14290