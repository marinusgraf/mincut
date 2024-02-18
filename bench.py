import util as u

#input = u.sys.argv[1]
output = "runtimes.csv"
u.print_info(input)
n, m = u.get_info(input)

with open(output, 'a') as file:
    dataname = input.removeprefix("graphs/netzschleuder/")
    file.write(f"{dataname},{n},{m},")
    for i, alg in enumerate(u.algs):
        alg.args[1] = input
        result = u.helper(alg, n)
        print(alg.name, result)
        if i == len(u.algs) - 1:
            file.write(f"{result[0]}\n")
        else:
            file.write(f"{result[0]},")
u.sort(output)