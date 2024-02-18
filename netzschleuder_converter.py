import graph_tool.all as gt
import sys
import os
path = sys.argv[1]


g = gt.collection.ns[path]
g.set_directed(False)

weight_prop = g.new_edge_property("int")
weight_prop.set_value(1)
g.edge_properties["weight"] = weight_prop
gt.remove_self_loops(g)
gt.contract_parallel_edges(g, weight=g.edge_properties["weight"])
l = gt.label_largest_component(g)
nodes_to_remove = [v for v in g.vertices() if l[v] != 1]
for v in reversed(sorted(nodes_to_remove)):
    g.remove_vertex(v)

filename = os.path.join("graphs/netzschleuder", path)
os.makedirs(os.path.dirname(filename), exist_ok=True)
with open(filename, "w") as file:
    file.write(f"{g.num_vertices()} {g.num_edges()}\n")
    edges = g.get_edges()
    dict = g.edge_properties["weight"]
    for e in edges:
        file.write(f"{e[0]} {e[1]} {dict[e]}\n")
