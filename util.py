import subprocess as sp
import os
import time
import sys
import pandas as pd

class Algorithm:
    def __init__(self, name, args):
        self.name = name
        self.args = args

algs = [Algorithm('Karger-Stein', ['./karger_stein', '']),
        Algorithm('Stoer-Wagner', ['./stoer_wagner', '']),
        Algorithm('Edmonds-Karp', ['./edmonds_karp', '']),
        Algorithm('Dinitz', ['./dinitz', ''])]


def sort(path):
    df = pd.read_csv(path)
    sorted_df = df.sort_values(by=["n"], ascending=True)
    sorted_df.to_csv(path, index=False)

def run(alg):
    result = sp.run(alg.args, capture_output=True, text=True)
    s = result.stdout.split(',')
    return float(s[0]), int(s[1])

def helper(alg, n):
    match alg.name:
        case 'Edmonds-Karp':
            if n <= 5000:
                return run(alg)
        case 'Dinitz':
            if n <= 15000:
                return run(alg)
        case 'Stoer-Wagner':
            if n <= 5000:
                return run(alg)
        case 'Karger-Stein':
            if n <= 5000:
                return run(alg)
    return float("inf"), float("inf")



def get_info(path):
    with open(path, 'r') as file:
        while True:
            line = file.readline()
            if line.startswith('#'):
                continue
            else:
                break
        str_list = line.split()
        n = int(str_list[0])
        m = int(str_list[1])
        return n, m

def print_info(path):
    with open(path, 'r') as file:
        while True:
            line = file.readline()
            if line.startswith('#'):
                continue
            else:
                break
        str_list = line.split()
        n = int(str_list[0])
        m = int(str_list[1])
        print(f"""
Input file: "{path}"

Running algorithms on graph, where |V|={n} |E|={m}...""")

def print_output(alg, result, time):
    print(f"""
        •{alg.name}'s Algorithm:
            -mincut value: {result.stdout.rstrip()}
            -time taken: {time:.2f} seconds""")
    