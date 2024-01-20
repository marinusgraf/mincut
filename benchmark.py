import util as u

for dirpath, dirnames, filenames in u.os.walk("graphs/generated"):
    for filename in filenames:
        path = u.os.path.join(dirpath, filename)
        u.print_info(path)
        for alg in u.algs:
            alg.args[1] = path
            start = u.time.time()
            result = u.sp.run(alg.args, capture_output=True, text=True)
            end = u.time.time()
            elapsed = end - start
            u.print_output(alg, result, elapsed)
