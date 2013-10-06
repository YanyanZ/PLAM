#ifndef BOUND_HPP
# define BOUND_HPP

class Bound
{
public:
  double lv_;
  double rv_;

public:
  Bound(double lvalue, double rvalue);
  ~Bound(){};

public:
  double get_lvalue(void);
  double get_rvalue(void);
};

#endif
