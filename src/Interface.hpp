#ifndef INTERFACE_HPP
# define INTERFACE_HPP

# include <glpk.h>

# include <vector>
# include <utility>

# include <iostream>
# include <fstream>
# include <sstream>

class Interface
{
private:
  std::string filepath;

private:
  int m; // Nombre d'entrepot
  int n; // Nombre de site

private:
  std::vector<std::vector<int> > map; // Carte des site avec capacite + ref + coord

public:
  Interface(std::string path);
  ~Interface();

public:
  int solve(void);
};

#endif /* Interface_hpp */
