import igraph as ig
import random
import os

def write_to_file(g, path):
    with open("tmp", 'a+') as tmp:
        with open(path, 'a') as file:
            file.write(f"{g.vcount()} {g.ecount()}\n")
            g.write_ncol("tmp", None)
            file.write(tmp.read())
    os.remove("tmp")

def assign_random_weights(g):
    for e in g.es:
        e["weight"] = random.randint(1, 10000)

path = "graphs/generated"
for i in range(1, 6):
    n = i * 60;
    full_path = os.path.join(path, f"full{n}")
    full = ig.Graph.Full(n)
    assign_random_weights(full)
    write_to_file(full, full_path)

    star_path = os.path.join(path, f"star{n}")
    star = ig.Graph.Star(n)
    assign_random_weights(star)
    write_to_file(star, star_path)

    ring_path = os.path.join(path, f"ring{n}")
    ring = ig.Graph.Ring(n)
    assign_random_weights(ring)
    write_to_file(ring, ring_path)

    children = random.randint(2, 50) #number of children of each node
    tree_path = os.path.join(path, f"tree{n},{children}")
    tree = ig.Graph.Tree(n, children)
    assign_random_weights(tree)
    write_to_file(tree, tree_path)


    m = random.randint(1, 50)
    barabasi_path = os.path.join(path, f"barabasi{n},{m}")
    barabasi = ig.Graph.Barabasi(n, m)
    assign_random_weights(barabasi)
    write_to_file(barabasi, barabasi_path)

    p = random.uniform(0.6, 0.9)
    erdos_renyi_path = os.path.join(path, f"erdos_renyi{n},{p:.1f}")
    erdos_renyi = ig.Graph.Erdos_Renyi(n, p)
    singletons = erdos_renyi.vs.select(lambda v: v.degree == 0)
    erdos_renyi.delete_vertices(singletons)
    assign_random_weights(erdos_renyi)
    write_to_file(erdos_renyi, erdos_renyi_path)

lattice10x10_path = os.path.join(path, f"lattice10x10")
lattice10x10 = ig.Graph.Lattice([10, 10])
assign_random_weights(lattice10x10)
write_to_file(lattice10x10, lattice10x10_path)
lattice15x15_path = os.path.join(path, f"lattice15x15")
lattice15x15 = ig.Graph.Lattice([15,15])
assign_random_weights(lattice15x15)
write_to_file(lattice15x15, lattice15x15_path)






