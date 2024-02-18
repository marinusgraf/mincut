CPP=clang++
FLAGS=-std=c++23 -Wall -O3 -g

karger:
	$(CPP) $(FLAGS) -o karger src/karger.cpp
karger_stein:
	$(CPP) $(FLAGS) -o karger_stein src/karger_stein.cpp
karger_uf:
	$(CPP) $(FLAGS) -o karger_uf src/karger_uf.cpp
stoer_wagner:
	$(CPP) $(FLAGS) -o stoer_wagner src/stoer_wagner.cpp
edmonds_karp:
	$(CPP) $(FLAGS) -o edmonds_karp src/edmonds_karp.cpp
dinitz:
	$(CPP) $(FLAGS) -o dinitz src/dinitz.cpp
graphs:
	rm graphs/generated/*
	python3 graph_generator.py
all:
	make -B karger
	make -B karger_stein
	make -B stoer_wagner
	make -B edmonds_karp
	make -B dinitz