import graph_tool.all as gt
import sys
import os
import time

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

w = g.ep["weight"]
start = time.time()
print(gt.min_cut(g, w)[0])
end = time.time()
print(f"took time {end - start}")