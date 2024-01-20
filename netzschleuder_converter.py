import graph_tool.all as gt
import sys
import os
path = sys.argv[1]

g = gt.collection.ns[path]
filename = os.path.join("../graphs/netzschleuder", path)
os.makedirs(os.path.dirname(filename), exist_ok=True)
with open(filename, "w") as file:
    file.write(f"{g.num_vertices()} {g.num_edges()}\n")
    edges = g.get_edges()
    if "weight" in g.edge_properties:
        dict = g.edge_properties["weight"]
        for e in edges:
            file.write(f"{e[0]} {e[1]} {dict[e]}\n")
    else:
        for e in edges:
            file.write(f"{e[0]} {e[1]}\n")
