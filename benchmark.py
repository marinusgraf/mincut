import util as u

for dirpath, dirnames, filenames in u.os.walk("graphs/generated"):
    for filename in filenames:
        path = u.os.path.join(dirpath, filename)
        u.print_info(path)
        n, m = u.get_info(path)
        for alg in u.algs:
            alg.args[1] = path
            result = u.helper(alg, n)
            print(alg.name, result)