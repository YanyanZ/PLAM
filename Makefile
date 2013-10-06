all:
	g++ -std=c++11 src/main.cpp src/bound/Bound.cpp src/constraints/Constraint.cpp src/objectif/Objectif.cpp src/solver/Solver.cpp src/variables/Variable.cpp -o Solver -lglpk -lm