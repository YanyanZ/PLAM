# include "Constraint.hpp"

Constraint::Constraint(std::string n, Bound b)
  : name (n), bnd (b)
{
}

void Constraint::add_var(Var v, double coeff)
{
  vars.push_back(std::make_pair(v, coeff));
}

Bound Constraint::get_bound()
{
  return bnd;
}

double Constraint::get_var_coef(Var v)
{
  for (std::pair<Var, double> tmp : vars)
  {
    if (tmp.first.get_name().compare(v.get_name()) == 0)
      return tmp.second;
  }
}

std::string Constraint::get_name()
{
  return name;
}
