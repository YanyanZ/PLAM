# include "Solver.hpp"
# include <algorithm>

Var Solver::get_var(std::string name)
{
  for (Var tmp : vars)
  {
    if (tmp.get_name().compare(name) == 0)
      return tmp;
  }
}

void Solver::print_constraints()
{
  
  for (Constraint tmp : constraints)
  {
    std::cout << tmp.get_name() << "\t";

    if (tmp.get_name().compare("Cons") != 0)
      std::cout << tmp.bnd.lv_ << " <= ";

    int cpt = 0;
    for (std::pair<Var, double> tmp2 : tmp.vars)
    {
      if (tmp2.second != 1)
	std::cout << tmp2.second << " * " << tmp2.first.get_name();
      else
	std::cout << tmp2.first.get_name();

      if (cpt < tmp.vars.size() - 1)
	std::cout << " + ";
      cpt++;
    }
    if (tmp.get_name().compare("Cons") != 0)
      std::cout << " <= " << tmp.bnd.rv_;
    else
      std::cout << " = " << tmp.bnd.rv_;
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

int distance(std::pair<int, int> A, std::pair<int, int> B)
{
  return (sqrt(pow(B.first - A.first, 2) + pow(B.second - A.second, 2)));
}

Solver::Solver(std::string path, std::string name)
{
  lp = glp_create_prob();
  glp_set_prob_name(lp, name.c_str());

  std::ifstream file (path.c_str(), std::ifstream::in);
  
  if (file.is_open())
  {
    std::string line;
    int id, x, y, c, cpt = 1;

    while (std::getline(file, line))
    {
      std::istringstream iss(line);

      if (line.compare("") == 0)
	continue;
      else if (cpt == 1)
      {
	cpt++;
	iss >> n >> m;
      }
      else
      {
	std::vector<int> tmp;
	std::ostringstream name;

	iss >> id >> x >> y >> c;
	name << "x" << id;

	tmp.push_back(id);
	tmp.push_back(x);
	tmp.push_back(y);
	tmp.push_back(c);
	file_data.push_back(tmp);

	vars.push_back(Var(name.str(), Bound(0, 1)));
	objectif.add_var(Var(name.str(), Bound(0, 1)), c);
      }
    }

    std::cout << "Nombre de candidat: " << n << std::endl;
    std::cout << "Nombre de batiment a construir: " << m << std::endl;

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
      {
	if (i >= j)
	  continue;

	int dist = distance(std::make_pair(file_data[i][1], file_data[i][2]),
			    std::make_pair(file_data[j][1], file_data[j][2]));
	    
	if (dist > 50)
	{
	  std::ostringstream name, si, sj;
	  name << "d_" << i + 1 << "_" << j + 1;
	  
	  Constraint cons = Constraint(name.str(), Bound(0, 1));
	  si << "x" << i + 1;
	  sj << "x" << j + 1;

	  cons.add_var(get_var(si.str()), 1);
	  cons.add_var(get_var(sj.str()), 1);

	  constraints.push_back(cons);

	}
      }

    Constraint cons = Constraint("Cons", Bound(0, m));
    for (int i = 0; i < n; i++)
    {
      	std::ostringstream name;
	
	name << "x" << (i + 1);
	cons.add_var(get_var(name.str()), 1);
    }
    constraints.push_back(cons);

    objectif.print();
    print_constraints();
  }
  else
  {
    std::cerr << "Error: unable to open file: " << path << std::endl;
    exit(-1);
  }
}

Solver::~Solver()
{
  glp_delete_prob(lp);
}

double Solver::to_result(Var v)
{
  int cpt = 0;
  
  for (Var tmp : vars)
  {
    if (v.get_name().compare(tmp.get_name()) == 0)
      break;
    else
      cpt++;
  }
  
  return glp_mip_col_val(lp, cpt + 1);
}


void Solver::solve()
{
  int nb_cells = vars.size() * constraints.size();

  int ia[1 + nb_cells];
  int ja[1 + nb_cells];
  double ar[1 + nb_cells];

  glp_set_obj_dir(lp, GLP_MAX);

  glp_add_rows(lp, constraints.size());
  glp_add_cols(lp, vars.size());

  for (int i = 0; i < constraints.size(); i++)
  {
    glp_set_row_name(lp, i + 1, constraints[i].get_name().c_str());

    if (constraints[i].get_name().compare("Cons") == 0)
      glp_set_row_bnds(lp, i + 1,
		       GLP_FX,
		       constraints[i].get_bound().get_lvalue(),
		       constraints[i].get_bound().get_rvalue());
    else
      glp_set_row_bnds(lp, i + 1,
		       GLP_UP,
		       constraints[i].get_bound().get_lvalue(),
		       constraints[i].get_bound().get_rvalue());
  }

  for (int i = 0; i < vars.size(); i++)
  {
    glp_set_col_name(lp, i + 1, vars[i].get_name().c_str());

    glp_set_col_bnds(lp, i + 1, GLP_BV,
		     vars[i].get_bound().get_lvalue(),
		     vars[i].get_bound().get_rvalue());

    glp_set_obj_coef(lp, i + 1, objectif.get_var_coef(vars[i]));
    glp_set_col_kind(lp, i + 1, GLP_IV);
  }

  for (int i = 0; i < constraints.size(); i++)
    for (int j = 0; j < vars.size(); j++)
    {
      ia[1 + i * vars.size() + j] = i + 1;
      ja[1 + i * vars.size() + j] = j + 1;
      ar[1 + i * vars.size() + j] = constraints[i].get_var_coef(vars[j]);
    }

  glp_load_matrix(lp, nb_cells, ia, ja, ar);
  glp_simplex(lp, NULL);
  glp_intopt(lp, NULL);

  std::vector<Var>::iterator it;

  std::cout << "result = {" << std::endl;
  std::cout << "z = " << glp_mip_obj_val(lp) << std::endl;
  for (it = vars.begin(); it != vars.end(); ++it)
    std::cout << it->get_name() << " = " << to_result(*it) << "," << std::endl;
  std::cout << "}" << std::endl;
}
