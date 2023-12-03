# Purpose

The program finds maximal clique of each input graph, plus a maximal common induced subgraph of all input graphs. More information available in the report.

# How to compile

## Adjacency matrix variant

`gcc main.c -o main`

## Adjacency list variant

`gcc adjlist.c -o main`

# How to run with example file

` ./main input/example.txt`

# If You want to see debug information

Add `#define dbg` to the start of the main.c

# If You want to print the results of the program to the console.

Add `#define PRINTTOCMD` to the beginning of the main.c. Regardless of that, program saves the output to output.txt file.

# TODO

- [x] Write data parsing from file in agreed format.
- [x] Implement the representation of graphs in a form of adjacency list.
- [x] Write a function to find a modular product of matrices.
- [x] Write a function to find maximal cliques of matrices (Bronn Kerbosch probably).
- [x] Write a function to find maximum common induced subgraph.
- [x] Add time measurments inside the program.
- [x] Support for multiple input files.
- [x] Fix GH leak, and improper node removal.
- [x] Switch Bron Kerbosch to iterative approach instead (recursion causes stack overflow for large graphs).
- [x] OPTIONAL: Test the product function against some example online.
- [x] OPTIONAL: Implement Adjacency Matrix implementation to improve time complexity at the cost of space complexity.
- [x] OPTIONAL: Add pivoting to iterative Bron Kerbosch.
- [x] It was also said that if the algorithm used is exponential then we should find a polynomial approximation algorithm also. It should be checked if the results are isomoprhpic to subgraphs in original graphs.
- [ ] The result of maximum common subgraph is not entirely correct I think. It whould be mapped to vertices of original graphs and for multigraphs it should be somehow checked if weights are the same.
- [ ] Add backtracking to current search for maximum common subgraph.
- [ ] Add isomorphism check for multigraphs.
- [ ] OPTIONAL: Do the above three steps for adjacency list also.
- [ ] Prepare some example data (reasonable amount). Preferably with known answers to cross-check.
- [ ] Run tests, time it to put something to docs.
- [x] OPTIONAL: Check and prepare for edge cases, such as empty graph description, vertex with no edges.
- [ ] OPTIONAL: Find a way to measure maximal memory usage.

# Possible improvements

- [ ] Add a progress bar in a form of a list.
- [ ] If let's say graphs can have the edge weight of no more than 256 then instead of using int we could use int8_t to cut down memory usage by around 40%.
- [ ] Improve size data type, size_t instead of int should be used and proper casting should be added.
