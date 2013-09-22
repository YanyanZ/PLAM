# include "Interface.hpp"

Interface::Interface(std::string path) : filepath (path)
{
  std::ifstream file(filepath.c_str(), std::ifstream::in);

  if (file)
  {
    std::string line;
    int id, x, y, c, m, n, cpt = 1;

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

	iss >> id >> x >> y >> c;

	std::cout << "Line : " << id << " " << x << " " << y << " " << c << std::endl;

	tmp.resize(4);
	tmp.push_back(id);
	tmp.push_back(x);
	tmp.push_back(y);
	tmp.push_back(c);

	map.push_back(tmp);
      }
    }
    file.close();
  }
  else
    std::cerr << "Cannot open file: " <<  filepath << std::endl;
}

Interface::~Interface()
{
}

int Interface::solve(void)
{
  return 0;
}
