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
- [ ] Prepare some example data (reasonable amount). Preferably with known answers to cross-check.
- [x] Implement the representation of graphs in a form of adjacency list.
- [x] Write a function to find a modular product of matrices.
- [ ] Test the product function against some example online.
- [x] Write a function to find maximal cliques of matrices (Bronn Kerbosch probably).
- [x] Write a function to find maximum common induced subgraph.
- [ ] It was also said that if the algorithm used is exponential then we should find a polynomial approximation algorithm also
- [ ] Run tests.
- [x] Add time measurments inside the program.
- [ ] Check and prepare for edge cases, such as empty graph description, vertex with no edges.
- [x] Support for multiple input files.
- [ ] Fix GH leak, and improper node removal.
