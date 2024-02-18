import util as u
import csv


for dirpath, dirnames, filenames in u.os.walk("graphs/netzschleuder"):
    for filename in filenames:
        input = u.os.path.join(dirpath, filename)
        print(input)
        print(filename)
        if filename.startswith('.'):
            continue;
        n, m = u.get_info(input)
        with open("runtimes.csv", 'a') as file:
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
