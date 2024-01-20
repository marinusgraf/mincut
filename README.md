# Overview

C++23 implementations and tests of different algorithms for finding the global min-cut in weighted, undirected graphs.

1. Karger's and Karger-Stein's Algorithm
2. Stoer-Wagner's Algorithm
3. Edmonds-Karp Algorithm 

# Input Files

Input files are expected to be edgelists where the first non-comment 
line is `n m` where `n` corresponds to the graph size and `m` to the 
number of edges. Every other line has the form `source target weight`
where `source` and `target` are 0-indexed integers 
corresponding to nodes and `weight` is a non-negative integer.
Comments can be inserted using \# at the beginning of a line.

The files in `graph/generated` have been generated using the igraph python library https://igraph.org/.
Details can be seen in `graph_generator.py`. The files in `graph/netzschleuder` were
converted from https://networks.skewed.de/ using the graph-tool python library https://graph-tool.skewed.de/.
Details can be found in `netzschleuder_converter.py`

# Compilation
Running `make all` will compile all programs using clang version 17.0.6.

# Running the programs
Simply run `./algorithm path_to_graph_file` to run a mincut algorithm of 
choice on the graph corresponding to the input file. 
For example, to run the Edmonds-Karp Algorithm on 
a complete graph with 200 nodes and random integer weights, run
`./edmonds_karp graphs/generated/full200`.

To compare the algorithms runtime, run `python3 test.py path_to_graph_file`.
All programs will be executed and timed.

`python3 benchmark.py` will run all algorithms on all graphs in `graphs/generated` and 
output relevant information.
