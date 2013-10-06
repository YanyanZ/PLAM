# include "Objectif.hpp"

void Objectif::add_var(Var v, double coeff)
{
  variables.push_back(std::make_pair(v, coeff));
}

double Objectif::get_var_coef(Var v)
{
  for (std::pair<Var, double>  tmp : variables)
  {
    if (tmp.first.get_name().compare(v.get_name()) == 0)
      return tmp.second;
  }
}

void Objectif::print()
{
  int cpt = 0;
  std::cout << "Max z=";
  for (std::pair<Var, double> tmp : variables)
  {
    std::cout << tmp.second << " * " << tmp.first.get_name();
    if (cpt < variables.size() - 1)
      std::cout << " + ";
    cpt++;
  }
  std::cout << std::endl;
}
