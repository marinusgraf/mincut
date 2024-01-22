import subprocess as sp
import os
import time
import sys

class Algorithm:
    def __init__(self, name, args):
        self.name = name
        self.args = args

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

algs = [Algorithm('Karger', ['./karger', '']),
         Algorithm('Karger-Stein', ['./karger_stein', '']),
           Algorithm('Edmonds-Karp', ['./edmonds_karp', '']),
           Algorithm('Stoer-Wagner', ['./stoer_wagner', '']),
           Algorithm('Dinic', ['./dinic', ''])]