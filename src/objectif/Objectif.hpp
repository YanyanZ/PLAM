#ifndef OBJECTIF_HPP
# define OBJECTIF_HPP

# include "../variables/Variable.hpp"

# include <vector>
# include <utility>

class Objectif
{
private:
  std::vector<std::pair<Var, double> > variables;

public:
  Objectif(){};
  ~Objectif(){};

public:
  void add_var(Var v, double coeff);

public:
  void print();
  double get_var_coef(Var v);

};

#endif
