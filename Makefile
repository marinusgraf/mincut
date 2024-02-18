CPP=clang++
FLAGS=-std=c++23 -Wall -O3 -g

karger_stein:
	$(CPP) $(FLAGS) -o karger_stein src/karger_stein.cpp
karger_stein_unionfind:
	$(CPP) $(FLAGS) -o karger_stein_unionfind src/karger_stein_unionfind.cpp
stoer_wagner:
	$(CPP) $(FLAGS) -o stoer_wagner src/stoer_wagner.cpp
edmonds_karp:
	$(CPP) $(FLAGS) -o edmonds_karp src/edmonds_karp.cpp
dinitz:
	$(CPP) $(FLAGS) -o dinitz src/dinitz.cpp
clean:
	rm -r dinitz edmonds_karp stoer_wagner karger_stein karger_stein_unionfind *.dSYM
graphs:
	rm graphs/generated/*
	python3 graph_generator.py
all:
	make -B karger_stein
	make -B karger_stein_unionfind
	make -B stoer_wagner
	make -B edmonds_karp
	make -B dinitz