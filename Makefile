CPP=clang++
FLAGS=-std=c++23 -Wall -O3 -g

main:
	clang++ -std=c++23 -Wall -O3 -o main src/main.cpp
karger:
	$(CPP) $(FLAGS) -o karger src/karger.cpp
karger_stein:
	$(CPP) $(FLAGS) -o karger_stein src/karger_stein.cpp
stoer_wagner:
	$(CPP) $(FLAGS) -o stoer_wagner src/stoer_wagner.cpp
edmonds_karp:
	$(CPP) $(FLAGS) -o edmonds_karp src/edmonds_karp.cpp
dinic:
	$(CPP) $(FLAGS) -o dinic src/dinic.cpp
graphs:
	rm graphs/generated/*
	python3 graph_generator.py
test: 
	clang++ -g -std=c++23 -Wall -O0 -o test src/test.cpp 
karg:
	clang++ -g -std=c++23 -Wall -O0 -o karg src/karg.cpp
kar:
	clang++ -g -std=c++23 -Wall -O3 -o kar src/kar.cpp 
all:
	make -B karger
	make -B karger_stein
	make -B stoer_wagner
	make -B edmonds_karp
	make -B dinic

clean:
	rm -r karger karger_stein stoer_wagner edmonds_karp dinic *.dSYM __pycache__
