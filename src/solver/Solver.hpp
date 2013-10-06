#ifndef SOLVER_HPP
# define SOLVER_HPP

# include <glpk.h>

# include <vector>
# include <iostream>
#include <fstream>
#include <sstream>

# include "../variables/Variable.hpp"
# include "../constraints/Constraint.hpp"
# include "../objectif/Objectif.hpp"

class Solver
{
private:
  int n;
  int m;

private:
  std::vector<std::vector<int> > file_data;

private:
  glp_prob* lp;

private:
  Objectif objectif;

private:
  std::vector<Var> vars;
  std::vector<Constraint> constraints;

public:
  Var get_var(std::string);

private:
  double to_result(Var v);

public:
  Solver(std::string path, std::string name);
  ~Solver();

public:
  void print_constraints();
  void solve();
};

#endif
