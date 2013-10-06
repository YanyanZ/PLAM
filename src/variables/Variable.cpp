# include "Variable.hpp"

Var::Var(std::string n, Bound b)
  : name_ (n),  bnd_ (b)
{
}

std::string Var::get_name(void)
{
  return name_;
}

Bound Var::get_bound(void)
{
  return bnd_;
}
