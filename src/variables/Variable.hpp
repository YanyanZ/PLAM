#ifndef VARIABLE_HPP
# define VARIABLE_HPP

# include <iostream>

# include "../bound/Bound.hpp"

class Var
{
private:
  std::string name_;
  Bound bnd_;

public:
  Var(std::string n, Bound b);
  ~Var(){};

public:
  std::string get_name(void);
  Bound get_bound(void); 
};

#endif
