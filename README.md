# Overview

C++23 implementations and tests of different algorithms for finding the global min-cut in weighted, undirected graphs.

1. Karger's and Karger-Stein's Algorithm (2 Implementations using Adjacency Matrix or Union-Find)
2. Stoer-Wagner's Algorithm
3. Edmonds-Karp's Algorithm
4. Dinitz' Algorithm

# Input Files

Input files are expected to be edgelists where the first non-comment 
line is `n m` where `n` corresponds to the graph size and `m` to the 
number of edges. Every other line has the form `source target weight`
where `source` and `target` are 0-indexed integers 
corresponding to nodes and `weight` is a non-negative integer.
Comments can be inserted using \# at the beginning of a line.

The files in `graph/netzschleuder` were
converted from https://networks.skewed.de/ using the graph-tool python library https://graph-tool.skewed.de/.
Details can be found in `netzschleuder_converter.py`

# Compilation
Running `make all` will compile all programs using clang version 17.0.6.

# Running the programs
Simply run `./algorithm path_to_graph_file` to run a mincut algorithm of 
choice on the graph corresponding to the input file. 

