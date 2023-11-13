# How to compile

`gcc main.c -o main`

# How to run with example file

` ./main input/example.txt`

# If You want to see debug information

Add `#define dbg` to the start of the main.c

# If You want to print the results of the program to the console.

Add `#define PRINTTOCMD` to the beginning of the main.c

# TODO

- [x] Write data parsing from file in agreed format.
- [x] Implement the representation of graphs in a form of adjacency list.
- [x] Write a function to find a modular product of matrices.
- [x] Write a function to find maximal cliques of matrices (Bronn Kerbosch probably).
- [x] Write a function to find maximum common induced subgraph.
- [x] Add time measurments inside the program.
- [x] Support for multiple input files.
- [x] Fix GH leak, and improper node removal.
- [x] Switch Bron Kerbosch to iterative approach instead (recursion causes stack overflow for large graphs)
- [ ] It was also said that if the algorithm used is exponential then we should find a polynomial approximation algorithm also
- [ ] Prepare some example data (reasonable amount). Preferably with known answers to cross-check.
- [x] OPTIONAL: Add pivoting to iterative Bron Kerbosch
- [ ] Run tests, time it to put something to docs.
- [ ] OPTIONAL: Check and prepare for edge cases, such as empty graph description, vertex with no edges.
- [ ] OPTIONAL: Test the product function against some example online.
