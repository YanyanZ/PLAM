# include "Bound.hpp"

Bound::Bound(double lvalue, double rvalue)
  : lv_ (lvalue), rv_ (rvalue)
{
}

double Bound::get_lvalue(void)
{
  return lv_;
}

double Bound::get_rvalue(void)
{
  return rv_;
}
