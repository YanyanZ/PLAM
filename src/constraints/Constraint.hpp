#ifndef CONSTRAINT_HPP
# define CONSTRAINT_HPP

# include "../variables/Variable.hpp"

# include <vector>
# include <utility>

class Constraint
{
public:
  std::string name;
  Bound bnd;

public:
  std::vector<std::pair<Var, double> > vars;

public:
  Constraint(std::string n, Bound b);
  ~Constraint(){};

public:
  void add_var(Var v, double coeff);

public:
  Bound get_bound();
  double get_var_coef(Var v);
  std::string get_name();
};

#endif
